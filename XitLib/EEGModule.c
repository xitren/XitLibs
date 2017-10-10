/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//Client sends message asking to get a subscription for resource update
//Server sends confirmation and adds client to list of subscribers
//Client sets an observer state for messages from server
//Server sends massages on update periodicaly 

#include "EEGModule.h"
#include "coap.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "version.h"
#include "LogModule.h"

#include "../FunctionsDiscovery.h"
#include "array.h"
#include "common.h"
#include "cJSON.h"

uint16_t hashes[HASHES_MAX];
/*
uint32_t hashes_cnt = 0;
*/

const char *tok_eeg_obs="eegobs";

Array *subscribers; //array of subscribed id's
FILE *mf; //the file from which we are going to read EEG
/*
Array *data;
*/
int partSize = 5;
int EEGStatus = 0;      // 0 - haven't started
                        // 1 - start
                        // 2 - started

//Handle subscription request
int SubscribeEEGFile(ParameterList_t *TempParam)
{
    
    #ifdef DEBUG
        printf("--//internal//-- Into SubscribeEEGFile.\r\n\r");
    #endif
    int ret_val = 0;
    
    Array *array;
    
    int i = 0;
    char ip[20];
    char *line;
    char *token;
    
    ArrayIter ai;
    array_iter_init(&ai, subscribers);
    char *str;
    void *next;
    
    int port = 5683;
    
    
    
   
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {  
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            
            if (!strcmp(TempParam->Params[i-1].strParam,"ip"))
            {
                strcpy(ip,TempParam->Params[i].strParam);
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"port"))
            {
                port = TempParam->Params[i].intParam;
                printf("Port was sent.\n");
            }
        }
        printf("pkt.tok_p: %X port: %d ip: %s\n", pkt.tok_p, port, ip);
        
        content_type = COAP_CONTENTTYPE_TEXT_PLAIN;

        AddToTransmit("<SUBSCRIPTION RESPONSE>\r\n\r");
        if (subscribers==NULL) {
            enum cc_stat status = array_new(&subscribers);
            if (status != CC_ERR_ALLOC) {
                AddToTransmit("Subscription to EEG file update data confirmed. Added IP to subscribers:\n");
                AddToTransmit(ip);
                
                int i = strlen(ip)+1;
                line = (char*) malloc(sizeof(char)*i);
                strncpy(line, ip, i);
                
                
                Array *subscriber;
                array_new(&subscriber);
                array_add(subscriber,line);
                array_add(subscriber,port);
                
                i = strlen(pkt.tok_p)+1;

                //token = (char*) malloc(sizeof(char)*i);

                token = pkt.tok_p;
                strncpy(token, pkt.tok_p, i);
                
                //printf("pkt.tok_p: %s token: %s\n", pkt.tok_p, token);
                printf("pkt.tok_p: %X token: %X\n", pkt.tok_p, token);
                
                
                
                array_add(subscriber,token);
                
                array_add(subscribers, subscriber);
                printf("New list of subscribers:\r\n\r");
                PrintSubscribers();
            }
            else {
                AddToTransmit("Subscription to EEG file failed (can't create array)");
            }
        }
        else {
            int a=0;
            while (array_iter_next(&ai, &next) != CC_ITER_END) {
                //array_get_at(subscribers, next, (void*) &str);

                //printf("1\n");
                size_t iter = array_iter_index(&ai);
                //printf("2\n");
                array_get_at(subscribers, iter, (void*) &array);
                //printf("3\n");

                array_get_at(array, 0, (void*) &str);
                printf("\n\n\n\n %s \n\n\n\n", str);
                printf("Cheking:\n");
                a++;
                printf("a++ : %d str: %s ip: %s\n",a,str,ip);
                if (strcmp(str,ip)==0) {                  //if such an ip is already in the list do not add
                    AddToTransmit(ip);
                    AddToTransmit(" already subscribed.");
                }
                else { 
                    AddToTransmit("Subscription to EEG file update data confirmed. Added IP to subscribers:\n");
                    AddToTransmit(ip);
                    
                    int i = strlen(ip)+1;
                    line = (char*) malloc(sizeof(char)*i);
                    strncpy(line, ip, i);


                    Array *subscriber;
                    array_new(&subscriber);
                    array_add(subscriber,line);
                    array_add(subscriber,port);

                    i = strlen(pkt.tok_p)+1;

                    //token = (char*) malloc(sizeof(char)*i);

                    token = pkt.tok_p;
                    strncpy(token, pkt.tok_p, i);

                    //printf("pkt.tok_p: %s token: %s\n", pkt.tok_p, token);
                    printf("pkt.tok_p: %X token: %X\n", pkt.tok_p, token);



                    array_add(subscriber,token);

                    array_add(subscribers, subscriber);
                
                    printf("New list of subscribers:\r\n\r");
                    PrintSubscribers();
                }
                printf("%s\r\n\r", str);
            }
        }
        AddToTransmit("\r\n\r</SUBSCRIPTION RESPONSE>\r\n\r");  
    }
   return(ret_val);
}

void PrintSubscribers() {
    ArrayIter ai;
    array_iter_init(&ai, subscribers);
    size_t size;
    
    Array *array;
    
    char *str;
    void *next;
    //printf("0\n");
    if (subscribers!=NULL) {
        while (array_iter_next(&ai, &next) != CC_ITER_END) {
            //array_get_at(subscribers, next, (void*) &str);
            
            //printf("1\n");
            size_t iter = array_iter_index(&ai);
            //printf("2\n");
            array_get_at(subscribers, iter, (void*) &array);
            //printf("3\n");
            
            array_get_at(array, 0, (void*) &str);
            printf("ip: %s ", str);
            array_get_at(array, 1, (void*) &size);
            printf("port: %d ", size);
            array_get_at(array, 2, (void*) &str);
            printf("token: %X\r\n\r", str);
        }
    }
}


//A function to read a line from the EEG file
void ReadFileEEG() {
/*
    char str[150];
    char *estr;
    
    char* line;
    
    printf("In ReadFileEEG. Status: %d\r\n\r", EEGStatus);
    if (EEGStatus == 1) {
        EEGStatus = 2;
        enum cc_stat status = array_new(&data);
        if (status != CC_ERR_ALLOC) {
            mf = fopen ("stream_rec.json","r");

            if (mf == NULL) {printf ("Error reading the file.\n"); return -1;}
            else printf ("Reading EEG file: \n");

            while (1)
            {
                estr = fgets (str,sizeof(str),mf);
                if (estr == NULL)
                {
                    if ( feof (mf) != 0)
                    {  
                        printf ("\nEnd of EEG file.\n");
                        break;
                    }
                    else
                    {
                        printf ("\nError while reading the EEG file.\n");
                        break;
                    }
                }
*/
/*
                printf ("     %s",str);
*/
/*
                int i = strlen(str)+1;
                line = (char*) malloc(sizeof(char)*i);
                strncpy(line, str, i);
                //array_add(data, line);
            }
            printf ("Closing EEG file: ");
            if ( fclose (mf) == EOF) printf ("Error closing the file.\n");
            else printf ("Finished\n");
        }
        else {
            AddToTransmit("Error creating EEG data. Failed to create data array");
        }
    }
*/
}

int ReadLineEEG() {
    int ret_val = 0;
    char str[150];
    char *estr;
    if (EEGStatus!=3) {
    if (EEGStatus<2) {
        EEGStatus=2; //set to "file opened"
        mf = fopen ("stream_rec.json","r");
        if (mf == NULL) {printf ("Error reading the file.\n"); return -1;}
        estr = fgets (str,sizeof(str),mf);
        if (estr == NULL)
        {
            if ( feof (mf) != 0)
            {  
                printf ("\nEnd of EEG file.\n");
                ret_val=1;
                printf ("Closing EEG file: ");
                if ( fclose (mf) == EOF) printf ("Error closing the file.\n");
                else printf ("Finished\n");
            }
            else
            {
                printf ("\nError while reading the EEG file.\n");
                
            }
            
        }
        else {
            if (strstr(str,"sample")!=NULL) {
                printf ("     %s",str);
            }
        }
    }
    else {
        
        estr = fgets (str,sizeof(str),mf);
        if (estr == NULL)
        {
            if ( feof (mf) != 0)
            {  
                printf ("\nEnd of EEG file.\n");
                ret_val=1;
                printf ("Closing EEG file: ");
                if ( fclose (mf) == EOF) printf ("Error closing the file.\n");
                else printf ("Finished\n");
                EEGStatus=3;
                
                WriteMem(REG_ADC_CH1,0);
                WriteMem(REG_ADC_CH2,0);
                WriteMem(REG_ADC_CH3,0);
                WriteMem(REG_ADC_CH4,0);
                WriteMem(REG_ADC_CH5,0);
                WriteMem(REG_ADC_CH6,0);
                WriteMem(REG_ADC_CH7,0);
                
            }
            else
            {
                printf ("\nError while reading the EEG file.\n");
                
            }
        }
        else {
            if (strstr(str,"sample")!=NULL) {
                printf ("     %s",str);
                cJSON * root = cJSON_Parse(str);
                cJSON *jdata = cJSON_GetObjectItemCaseSensitive(root, "data");
                int channels[7] = {0};
                
                channels[0] = cJSON_GetArrayItem(jdata,1)->valueint;
                channels[1] = cJSON_GetArrayItem(jdata,2)->valueint;
                channels[2] = cJSON_GetArrayItem(jdata,3)->valueint;
                channels[3] = cJSON_GetArrayItem(jdata,4)->valueint;
                channels[4] = cJSON_GetArrayItem(jdata,5)->valueint;
                channels[5] = cJSON_GetArrayItem(jdata,6)->valueint;
                channels[6] = cJSON_GetArrayItem(jdata,7)->valueint;
                
                WriteMem(REG_ADC_CH1,channels[0]);
                WriteMem(REG_ADC_CH2,channels[1]);
                WriteMem(REG_ADC_CH3,channels[2]);
                WriteMem(REG_ADC_CH4,channels[3]);
                WriteMem(REG_ADC_CH5,channels[4]);
                WriteMem(REG_ADC_CH6,channels[5]);
                WriteMem(REG_ADC_CH7,channels[6]);
                
                cJSON_Delete(root);
            }
        }
    }
    }
    return ret_val;
}


void SendEEGSamples() {
/*
    printf("In samples\n");
*/
    int l = 0, k = 0; //size
    
    char *buffer[10];
    char buffer2[1024]="";
    char message[4096]="";
    size_t data_len=0;
    
    if(subscribers!=NULL) {
    
//    printf("ReadMem(REG_EEG_PocketSize): %d ReadMem(REG_EEG_Auto_Band): %d\n", ReadMem(REG_EEG_PocketSize), ReadMem(REG_EEG_Auto_Band));
//    if ((ReadMem(REG_EEG_PocketSize) <= l) && (ReadMem(REG_EEG_Auto_Band) > 0)) {
        
        l = GetDataReadyCnt(ReadMem(REG_EEG_PocketSize), (int*) scratch_raw);
        if (l > 0) {
            
            cJSON *root;
            cJSON *datablock;
            cJSON *sample;
            
            root = cJSON_CreateObject();
            datablock = cJSON_CreateArray();
            data_len += snprintf(buffer2,STRING_SIZE,"{\"DATABLOCK\": [\n");
            strcat(message,buffer2);
            int n;
            for (n =0; n<(l/8); n++) {
                
                
                data_len += snprintf(buffer2,STRING_SIZE,"   {\"sample\": %d, \"data\": [%d, %d, %d, %d, %d, %d, %d]}",n,((int*)scratch_raw)[n*8+0],((int*)scratch_raw)[n*8+1],((int*)scratch_raw)[n*8+2],((int*)scratch_raw)[n*8+3],((int*)scratch_raw)[n*8+4],((int*)scratch_raw)[n*8+5],((int*)scratch_raw)[n*8+6]);
                //printf("buffer2 %s\n", buffer2);
                strcat(message,buffer2);
                if (n!=(l/8)-1) {
                   data_len += snprintf(buffer2,STRING_SIZE,",\n");
                   strcat(message,buffer2);
                }
                else {
                   data_len += snprintf(buffer2,STRING_SIZE,"\n ]\n}");
                   strcat(message,buffer2);
                }
 
                cJSON *array;
                
                cJSON *fmt;

            }

            SendToSubsribers(message, data_len);
            
        }
            

        }
    
 //   }
}

int CheckEEGStatus() {
    if (EEGStatus<2 && subscribers!=NULL) {
        EEGStatus=1;
    }
/*
    printf("EEGStatus: %d\n", EEGStatus);
*/
    return EEGStatus;
}
    

void SendToSubsribers(char *data,size_t data_len) {
    ArrayIter ai;
    array_iter_init(&ai, subscribers);
    size_t size;
    
    Array *array;
    void *next;
    
    int port;  //port
    char *str; //ip
    char *token; //token
    
    //for each subscriber send new part
    if (subscribers!=NULL) {
        while (array_iter_next(&ai, &next) != CC_ITER_END) {
            size_t iter = array_iter_index(&ai);
            array_get_at(subscribers, iter, (void*) &array);
            array_get_at(array, 0, (void*) &str);
            array_get_at(array, 1, (void*) &port);
            array_get_at(array, 2, (void*) &token);
            sendEEGNews(port, str, token, data, data_len);
        }
    }
}

void sendEEGNews(int port, char *address, char *token, uint8_t *data,size_t data_len) {
    int rc;
    uint8_t observer_data[3];
    //char message[1000];
    
    //printf("Sending message to 40\n");
    //snprintf(message,1000,data);
    
    
/*
    char *token;
*/
    size_t tok_len;
    
    ArrayIter ai;
    array_iter_init(&ai, subscribers);
    int size;
    
    Array *array;
    
    char *str;
    void *next;
/*
    //printf("0\n");
    if (subscribers!=NULL) {
        while (array_iter_next(&ai, &next) != CC_ITER_END) {
            //array_get_at(subscribers, next, (void*) &str);
            
            //printf("1\n");
            size_t iter = array_iter_index(&ai);
            //printf("2\n");
            array_get_at(subscribers, iter, (void*) &array);
            //printf("3\n");
            
            array_get_at(array, 0, (void*) &str);
            //printf("%s\r\n\r", str);
            array_get_at(array, 1, (void*) &size);
            //printf("%d\r\n\r", size);
            port = size;
            array_get_at(array, 2, (void*) &str);
            //printf("%X\r\n\r", str);
            token = str;
        }
    }
*/
    
    printf("Message id: %s token: %X port=%d \n", address, token, port);
    
    pkt.tok_len = 2;
    memcpy(pkt.tok_p, token, pkt.tok_len);
    
    coap_option_t opt_obs;
    ((uint16_t*)observer_data)[0] = GetClock();
    opt_obs.num = 6;
    opt_obs.buf.p = (uint8_t *)observer_data;
    opt_obs.buf.len = 2;
            
    coap_make_response(&scratch_buf, &pkt,
        &opt_obs,  (uint8_t*)data, data_len, 
        0, id_out+=5, pkt.tok_p, pkt.tok_len, 
        COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_APPLICATION_JSON);
    
    pktlen = 4096;
    scratch_buf.len = 4096;

/*
    printf("patlen= %d\n",pktlen);
*/

    if (!(rc = coap_build(scratch_raw, &scratch_buf.len, &pkt, NULL, NULL)))
    {
        printf("Transfering.\n");
        TransferUDP((uint8_t*)scratch_raw,scratch_buf.len,address,port);
    }
    else { 
        printf("Don't want to build message.\n");
        printf("returned %d \n", rc); 
    }
        
        
//        printf();
    #ifdef DEBUG
        DBG_LOG_DEBUG("Sending: ");
        coap_dump(scratch_raw, scratch_buf.len, true);
    #endif
    //updateStatus = 2;
    return;
}