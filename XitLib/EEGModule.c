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

struct ips {
   char         ip[15];
   uint32_t     port;
   char         tok_p[6];
   uint8_t      tok_len;
}; 

//union ip_data {
//   ips          formal;
//   char         byte[25];
//};

const char *tok_eeg_obs="eegobs";

Array *subscribers = 0; //array of subscribed id's
FILE *mf; //the file from which we are going to read EEG
/*
Array *data;
*/
int partSize = 5;
int EEGStatus = 0;      // 0 - haven't started
                        // 1 - start
                        // 2 - started

//Handle subscription request
#ifndef MC
int SubscribeEEGFile(ParameterList_t *TempParam)
{
    #ifdef DEBUG
        printf("--//internal//-- Into SubscribeEEGFile.\r\n\r");
    #endif
    if (subscribers == 0)
        if (array_new(&subscribers) != 0)
            return;
    
    int ret_val = 0;
    int i = 0;
    struct ips *ip = (struct ips *) malloc(sizeof(struct ips));
    
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {  
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"ip"))
            {
                strcpy(ip->ip,TempParam->Params[i].strParam);
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"port"))
            {
                ip->port = TempParam->Params[i].intParam;
            }
        }
        ip->tok_len = pkt.tok_len;
        for (i = pkt.tok_len;i < 6;i++)
            pkt.tok_p[i] = 0;
        memcpy(ip->tok_p,pkt.tok_p,6);
        printf("pkt.tok_p: %02X%02X%02X%02X%02X%02X port: %d ip: %s\n",  
        (uint8_t)ip->tok_p[0], (uint8_t)ip->tok_p[1], (uint8_t)ip->tok_p[2],
        (uint8_t)ip->tok_p[3], (uint8_t)ip->tok_p[4], (uint8_t)ip->tok_p[5],
        ip->port, ip->ip);
        
        content_type = COAP_CONTENTTYPE_TEXT_PLAIN;

        AddToTransmit("<SUBSCRIPTION RESPONSE>\r\n\r");
        //check
                                                       
        int Index;
        for(Index=0;Index < array_size(subscribers);Index++)
        {
            struct ips *element;
            array_get_at(subscribers, Index, (void**)&element);
            if(     (memcmp(element->ip, ip->ip, 15) == 0) 
                    && (element->port == ip->port) 
                    && (memcmp(element->tok_p, ip->tok_p, 6) == 0))
                break;
        }
        if (Index >= array_size(subscribers)) 
        {
            AddToTransmit("Subscription to EEG file update data confirmed. Added IP to subscribers:\n");
            AddToTransmit(ip);
            array_add(subscribers,ip);
            printf("New list of subscribers:\r\n\r");
            PrintSubscribers();
        }
        else
        {
            AddToTransmit(" already subscribed.");
        }
        AddToTransmit("\r\n\r</SUBSCRIPTION RESPONSE>\r\n\r");  
    }
    return(ret_val);
}
#endif

void PrintSubscribers() {
    if (subscribers != 0) {                                  
        int Index;
        for(Index=0;Index < array_size(subscribers);Index++)
        {
            struct ips *element;
            array_get_at(subscribers, Index, (void**)&element);
            printf("pkt.tok_p: %02X%02X%02X%02X%02X%02X port: %d ip: %s\n", 
                    (uint8_t)element->tok_p[0], (uint8_t)element->tok_p[1], (uint8_t)element->tok_p[2],
                    (uint8_t)element->tok_p[3], (uint8_t)element->tok_p[4], (uint8_t)element->tok_p[5],
                    element->port, element->ip);
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
        int Index;
        for(Index=0;Index < array_size(subscribers);Index++)
        {
            struct ips *element;
            array_get_at(subscribers, Index, (void**)&element);
            printf("pkt.tok_p: %02X%02X%02X%02X%02X%02X port: %d ip: %s\n", 
                    (uint8_t)element->tok_p[0], (uint8_t)element->tok_p[1], (uint8_t)element->tok_p[2],
                    (uint8_t)element->tok_p[3], (uint8_t)element->tok_p[4], (uint8_t)element->tok_p[5],
                    element->port, element->ip);
            sendEEGNews(element->port, element->ip, element->tok_p, element->tok_len, 
                                                            data, data_len);
        }
    }
}

void sendEEGNews(int port, char *address, char *token, uint8_t token_len, 
                                            uint8_t *data, size_t data_len) {
    int rc;
    uint8_t observer_data[3];
    
    printf("Message id: %s token: %02X%02X%02X%02X%02X%02X port=%d \n", address,
    (uint8_t)token[0], (uint8_t)token[1], (uint8_t)token[2],
    (uint8_t)token[3], (uint8_t)token[4], (uint8_t)token[5], port);
    
    pkt.tok_len = token_len;
    memcpy(pkt.tok_p, token, 6);
    
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

    coap_dumpPacket(&pkt);
    if (!(rc = coap_build(scratch_buf.p, &scratch_buf.len, &pkt, NULL, NULL)))
    {
        printf("Transfering.\n");
        TransferUDP((uint8_t*)scratch_buf.p,scratch_buf.len,address,port);
    }
    else { 
        printf("Don't want to build message.\n");
        printf("returned %d \n", rc); 
    }
    #ifdef DEBUG
        DBG_LOG_DEBUG("Sending: ");
        coap_dump(scratch_buf.p, scratch_buf.len, true);
    #endif
    return;
}