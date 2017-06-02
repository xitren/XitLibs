
/* Local headers -------------------------------------------------------------*/
#include "UpdateModule.h"
#include "../CoAP/coap.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "version.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint16_t hashes[HASHES_MAX];
uint32_t hashes_cnt = 0;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
char tok_update[7];
const char *tok_update_hash="updhsh";
//const char *path_update="update?type=2";
//const char *path_update_hash="updatehash?type=2";
const char *path_update_reqry="/REQUERY/UPDATE";
char path_update_clb[50]="/CALLBACK/UPDATE?type=0";
char path_update_hash_clb[50]="/CALLBACK/UPDATEHASH?type=0";
const char *updateserver = "10.10.30.35";
const char *updatefile = "Updater.sh";
char *version = VERSION;
/*============================================================================*/
uint32_t config_dev_type[CFG_SIZE];
char updatefilepath[200]="Updater.sh";
/*============================================================================*/


/* Functions declaration -----------------------------------------------------*/
inline void InitCfgDevType(void) {
    config_dev_type[BASESTATION] = 0;
    config_dev_type[EEG] = 1;
    config_dev_type[MOVEMENT] = 2;
    config_dev_type[CAMERA] = 3;
    config_dev_type[GENERATOR] = 4;
}

#ifdef CPU
int QueryUpdate(ParameterList_t *TempParam)
{
    int ret_val = 0;
    int i,ind_i,end;
    const char *ip = updateserver;
    char path_update[50];
    int port = 5683;
    int repeat = 2;
    char requery[100];
    int rc;
    coap_buffer_t tokfb;
    int pktlen = sizeof(buf);
    int type;

    #ifdef DEBUG
        printf("--//internal//-- Into QueryUpdate.\r\n\r");
    #endif
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"part"))
            {
                ind_i = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"end"))
            {
                end = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"ip"))
            {
                ip = TempParam->Params[i].strParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"port"))
            {
                port = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"repeat"))
            {
                repeat = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
                printf("type got***: %d\r\n\r", type);
            }
        }
        if (repeat <= 0)
        {
            printf("No more repeats.");
            return;
        }
        
        snprintf(path_update,50,"update?type=%d",type);
        snprintf(path_update_hash_clb,50,"/CALLBACK/UPDATEHASH?type=%d",type);  
        snprintf(path_update_clb,50,"/CALLBACK/UPDATE?type=%d",type);  
        
        pktlen = sizeof(buf);
        opt_path.num = COAP_OPTION_URI_PATH;
        opt_path.buf.len = strlen(path_update);
        opt_path.buf.p = (uint8_t*)path_update;
        make_part_option(&opt_part,ind_i,COAP_PART_SIZE_1024,end);
        pkt.tok_len = 6;
        snprintf(tok_update,7,"ud%04d",ind_i);
        memcpy(pkt.tok_p, tok_update, pkt.tok_len);
        coap_make_msg(&scratch_buf, &pkt, &opt_path, 0, &opt_part,
                           0, 0, 
                           0, id_out+=5, pkt.tok_p, pkt.tok_len, 
                           COAP_METHOD_GET, 
                           COAP_CONTENTTYPE_NONE);
        if (repeat <= 0)
        {
            snprintf(requery,100,
                    "/REQUERY/UPDATE?part=%d&end=%d&repeat=%d&ip=%s&port=%d&type=%d"
                                    ,ind_i,end,repeat-1,ip,port,type);
            if (!(rc = coap_build(buf, &pktlen, &pkt, path_update_clb, requery)))
            {
                //Transfer((uint8_t*)buf,pktlen,"/update");
                TransferUDP((uint8_t*)buf,pktlen,ip,port);
            }
        }
        else
        {
            if (!(rc = coap_build(buf, &pktlen, &pkt, path_update_clb, NULL)))
            {
                //Transfer((uint8_t*)buf,pktlen,"/update");
                TransferUDP((uint8_t*)buf,pktlen,ip,port);
            }
        }
        #ifdef DEBUG
            printf("Sending: ");
            coap_dump(buf, pktlen, true);
            printf("\r\n\r");
        #endif
        #ifdef DEBUG
            printf("--//internal//-- Sended %d part query.\r\n\r",ind_i);
        #endif
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }

    #ifdef DEBUG
        printf("--//internal//-- Into END of QueryUpdate.\r\n\r");
    #endif
    return(ret_val);
}
int QueryUpdateHash(ParameterList_t *TempParam)
{
    int ret_val = 0;
    int i,ind_i,end;
    const char *ip = updateserver;
    int port = 5683;
    int repeat = 0;
    char requery[100];
    int rc;
    int pktlen = sizeof(buf);
    char path_update_hash[50];
    char path_update_hash_clb[50];
    int type;
    
    #ifdef DEBUG
        printf("--//internal//-- Into QueryUpdateHash.\r\n\r");
    #endif
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"ip"))
            {
                ip = TempParam->Params[i].strParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"port"))
            {
                port = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"repeat"))
            {
                repeat = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
                printf("type got***: %d\r\n\r", type);
            }
        }
        if (repeat <= 0)
        {
            printf("No more repeats.");
            return;
        }
        snprintf(path_update_hash,50,"updatehash?type=%d",type);
        snprintf(path_update_hash_clb,50,"/CALLBACK/UPDATEHASH?type=%d",type);    
        memset((uint8_t*)hashes,0,sizeof(uint16_t)*HASHES_MAX);
        opt_path.num = COAP_OPTION_URI_PATH;
        opt_path.buf.len = strlen(path_update_hash);
        opt_path.buf.p = (uint8_t*)path_update_hash;
        pkt.tok_len = strlen(tok_update_hash);
        memcpy(pkt.tok_p, tok_update_hash, pkt.tok_len);
        coap_make_msg(&scratch_buf, &pkt, &opt_path, 0, 0,
                           0, 0, 
                           0, id_out+=5, pkt.tok_p, pkt.tok_len, 
                           COAP_METHOD_GET, 
                           COAP_CONTENTTYPE_NONE);
        if ((repeat-1) > 0)
        {
            snprintf(requery,100,"/REQUERY/UPDATEHASH?repeat=%d&type=%d",repeat-1, type);
            printf(requery,"/REQUERY/UPDATEHASH?repeat=%d&type=%d",repeat-1, type);
            if (!(rc = coap_build(buf, &pktlen, &pkt, path_update_hash_clb, requery)))
            {
        //        Transfer((uint8_t*)buf,pktlen,"/updatehash");
                TransferUDP((uint8_t*)buf,pktlen,updateserver,5683);
            }
        }
        else
        {
            requery[0] = 0;
            if (!(rc = coap_build(buf, &pktlen, &pkt, path_update_hash_clb, NULL)))
            {
        //        Transfer((uint8_t*)buf,pktlen,"/updatehash");
                TransferUDP((uint8_t*)buf,pktlen,updateserver,5683);
            }
        }
        #ifdef DEBUG
            printf("Sending: ");
            coap_dump(buf, pktlen, true);
            printf("\r\n\r");
        #endif
        #ifdef DEBUG
            printf("--//internal//-- Sended parts hash query.\r\n\r");
        #endif
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }

    #ifdef DEBUG
        printf("--//internal//-- Into END of QueryUpdateHash.\r\n\r");
    #endif
    return(ret_val);
}


int Version(ParameterList_t *TempParam)
{
   int ret_val =0;
   
   #ifdef DEBUG
      printf("--//internal//-- Into Version.\r\n\r");
   #endif
   content_type = COAP_CONTENTTYPE_TEXT_PLAIN;
   AddToTransmit("<VERSION>\r\n\r");
   //здесь код программы
   AddToTransmit(version);
   AddToTransmit("\r\n\r</VERSION>\r\n\r");

   return(ret_val);
}


   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int CallbackUpdate(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i = 0,end,rsize;
    char namepart[100];
    char command[100];
    char systemcommand[100];
    char filename[50];
    FILE *fp,*fpo;
    int type;
    
    #ifdef DEBUG
        printf("--//internal//-- Into CallbackUpdate.\r\n\r");
    #endif
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"part"))
            {
                ind_i = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"end"))
            {
                end = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
                printf("type got***: %d\r\n\r", type);
            }
        }
        //save to file
        if (type==0) { //Updater.sh
            strcpy(filename, "Updater.sh");
        }
        else if (type==1) { //iotbaseserverlinux.sh
            strcpy(filename, "iotbaseserverlinux.sh");
        }
        else if (type==2) { //iotdeviceeegserverlinux.sh
            strcpy(filename, "iotdeviceeegserverlinux.sh");
        }
        else if (type==3) { 
            strcpy(filename, "iotdevicemovementlinux.sh");
        }
        else if (type==4) {
            strcpy(filename, "iotdevicecameralinux.sh");
        }
        else if (type==5) {
            strcpy(filename, "iotdevicegeneratorlinux.sh");
        }
        else strcpy(filename, "Updater.sh"); //Wrong type? Updater.sh then
        
        snprintf(namepart,100,"%s.p%02d",filename,ind_i);
        fp = fopen(namepart,"w"); // read mode
        #ifdef DEBUG
            printf("--//internal//-- Create file %s.\r\n\r",namepart);
        #endif

        if( fp == NULL )
        {
           printf("Error while opening update the file callback_update.\r\n\r");
        }
        fwrite(scratch_buf.p,sizeof(uint8_t),scratch_buf.len,fp);
        fclose(fp);
        //if endone then pack into monolite
        if (end)
        {
            snprintf(command,100,"/REQUERY/UPDATE?part=%d&end=%d&repeat=3&type=%d"
                                                                ,ind_i+1,end,type);
            CommandLineInterpreter(command);
            #ifdef DEBUG
                printf("--//internal//-- %s.\r\n\r",command);
            #endif
        }
        else
        {
            snprintf(namepart,100,"%s",filename);
            sprintf(systemcommand, "sudo cp %s old_%s", filename, filename);
            system(systemcommand);
            fp = fopen(namepart,"w"); // read mode
            #ifdef DEBUG
                printf("--//internal//-- Create file %s.\r\n\r",namepart);
            #endif
            for(i=0;i<=ind_i;i++)
            {
                snprintf(namepart,100,"%s.p%02d",filename,i);
                fpo = fopen(namepart,"r"); // read mode
                
                rsize = fread(scratch_buf.p,sizeof(uint8_t),1024,fpo);
                fwrite(scratch_buf.p,sizeof(uint8_t),rsize,fp);
                
                fclose(fpo);
                remove(namepart);
            }
            fclose(fp);
            
            //собрали. теперь выполним

            //usleep(30000000);
            if (type==0) { //Updater.sh
                sprintf(systemcommand, "sudo sh %s", filename);
                printf("Command: [%s]\r\n\r", systemcommand);
                system(systemcommand);
                printf("Command: sudo ~/iotserverdaemon/iotservdaemon 0\r\n\r");
                system("sudo ~/iotserverdaemon/iotservdaemon 0");
                //system("sudo sh Updater.sh");
            }
            else {
                sprintf(systemcommand, "sudo sh %s", filename);
                printf("Command: [%s]\r\n\r", systemcommand);
                system(systemcommand);
                if (type==1) {
                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 1]\r\n\r");
                    system("sudo ~/iotserverdaemon/iotservdaemon 1");
                }
                else if (type==2) {
                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 2]\r\n\r");
                    system("sudo ~/iotserverdaemon/iotservdaemon 2");
                }
                else if (type==3) {
                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 3]\r\n\r");
                    system("sudo ~/iotserverdaemon/iotservdaemon 3");
                }
                else if (type==4) {
                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 4]\r\n\r");
                    system("sudo ~/iotserverdaemon/iotservdaemon 4");
                }
                else if (type==5) {
                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 5]\r\n\r");
                    system("sudo ~/iotserverdaemon/iotservdaemon 5");
                }
            }
            
            //usleep(30000000);
            exit(0);
  
          
//            system("sudo sh Updater.sh");
            
            #ifdef PLATFORM_WINDOWS
                system("chmod 777 update.sh");
                system("start sh update.sh");
                exit(0);
            #endif
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }

    #ifdef DEBUG
        printf("--//internal//-- Into END of CallbackUpdate.\r\n\r");
    #endif
    return(ret_val);
}
   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int CallbackUpdateHash(ParameterList_t *TempParam)
{
    int rc;
    coap_buffer_t tokfb;
    int pktlen = sizeof(buf);
    int ret_val = 0;
    int i,ind_i;
    char command[100];
    FILE *fp;
    int num;
    int sizefp;
    int end;
    char *ptr;
    uint16_t allhash = 0;
    uint16_t allhashserver = 0;
    char filename[50];
    int type;
    
    #ifdef DEBUG
        printf("--//internal//-- Into CallbackUpdateHash.\r\n\r");
    #endif
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
        if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
                printf("type got***: %d\r\n\r", type);
            }

        }
        
        //прочитать хэш нужного файла
        //если раздаёт BaseStation, читаем из update
        printf("Device type***: %d\r\n\r", DEVICE);
        if (DEVICE == 0) {
            if (type==0) { //Updater.sh
                strcpy(filename, "Updater.sh");
            }
            else if (type==1) { //iotbaseserverlinux.sh
                strcpy(filename, "./update/iotbaseserverlinux.sh");
            }
            else if (type==2) { //iotdeviceeegserverlinux.sh
                strcpy(filename, "./update/iotdeviceeegserverlinux.sh");
            }
            else if (type==3) { 
                strcpy(filename, "./update/iotdevicemovementlinux.sh");
            }
            else if (type==4) {
                strcpy(filename, "./update/iotdevicecameralinux.sh");
            }
            else if (type==5) {
                strcpy(filename, "./update/iotdevicegeneratorlinux.sh");
            }
            else strcpy(filename, "Updater.sh"); //Wrong type? Updater.sh then
        }
        //иначе читаем из локальной папки
        else {
            if (type==0) { //Updater.sh
                strcpy(filename, "Updater.sh");
            }
            else if (type==1) { //iotbaseserverlinux.sh
                strcpy(filename, "iotbaseserverlinux.sh");
            }
            else if (type==2) { //iotdeviceeegserverlinux.sh
                strcpy(filename, "iotdeviceeegserverlinux.sh");
            }
            else if (type==3) { 
                strcpy(filename, "iotdevicemovementlinux.sh");
            }
            else if (type==4) {
                strcpy(filename, "iotdevicecameralinux.sh");
            }
            else if (type==5) {
                strcpy(filename, "iotdevicegeneratorlinux.sh");
            }
            else strcpy(filename, "Updater.sh"); //Wrong type? Updater.sh then
        }
        
        printf("THE FILE NAME IS***: %s\r\n\r", filename);
        
        fp = fopen(filename,"r"); // read mode

        if( fp != NULL )
        {
            end = 0;
            while (end == 0)
            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                #ifdef DEBUG
                    printf("--//internal//-- %d readed from file.\r\n\r",sizefp);
                #endif
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);

                allhash += CRC16ANSI(bufsa,sizefp);
                
                if (sizefp != size_parts)
                {
                    end = 1;
                }
            } 
            ptr = strstr(scratch_buf.p,"0x");
            ptr[6] = 0;
            allhashserver = StringToUnsignedInteger(ptr);
            scratch_buf.p = ptr+1;
            fclose(fp);
            #ifdef DEBUG
                printf("--//internal//-- %X <> %X.\r\n\r",allhashserver,
                                                        allhash);
            #endif
            if (allhashserver != allhash)
            {
                //system("sudo rm Complexmedsh");
//                system("sudo cp Complexmed.sh Complexmed_old.sh");
//                system("sudo wget http://188.64.170.71:80/Complexmed.sh");
//                system("sudo chmod 777 Complexmed.sh");
//                system("sh Complexmed.sh"); 
                snprintf(command,100,"/REQUERY/UPDATE?part=0&repeat=3&type=%d",type);
                CommandLineInterpreter(command);
                //usleep(1000000);
                //system("sudo sh Updater.sh");
                //usleep(1000000);
                //exit(0);
            }
            else
            {
                printf("--//internal//-- Updates already implemented.\r\n\r");
                //exit(0);
            }
        }
        else
        {
                snprintf(command,100,"/REQUERY/UPDATE?part=0&repeat=3&type=%d",type);
                CommandLineInterpreter(command);
                //usleep(1000000);
                //system("sudo sh Updater.sh");
                //system("sudo ~/pi/iotdevicedaemon/iotdevicedaemon");
                //usleep(1000000);
                //exit(0);
//            system("sudo wget http://188.64.170.71:80/Complexmed.sh");
//            system("sudo chmod 777 Complexmed.sh");
//            system("sh Complexmed.sh"); 
            //exit(0);
        }

    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }

    #ifdef DEBUG
        printf("--//internal//-- Into END of CallbackUpdateHash.\r\n\r");
    #endif
    return(ret_val);
}

/*
int FindUpdateServer()
{   
    int ret_val = 0;
    char* ServerIP[50];
    

    if (serverIP(ServerIP)) {
        //printf("SERRRRVERRRR FOUND!!*****\n");
        return 1;
    }
    //else printf("NOT FOUND!!*****");

    return ret_val;
    
}
*/

int TechUpdate(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int i;
    char command[100];
    
    #ifdef DEBUG
        printf("--//internal//-- Into TechUpdate.\r\n\r");
    #endif
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"filepath"))
            {
                strcpy(updatefilepath,TempParam->Params[i].strParam);
            }
        }
        AddToTransmit("<TECHUPDATE>\r\n\r");
        AddToTransmit("Update request recieved!\r\n\r");
        AddToTransmit("</TECHUPDATE>\r\n\r");
        //printf("updatefilepath: %s", updatefilepath);
        WriteMem(REG_UPD_File,1);
        //function_update();
        //snprintf(command,100,"/GET/TECHSTART");
        //CommandLineInterpreter(command);

    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }
    #ifdef DEBUG
        printf("--//internal//-- Into END of TechUpdate.\r\n\r");
    #endif
    return(ret_val);
}


void function_update(int type)
{
    int rc;
    int pktlen = sizeof(buf);
    char command[100];
    char path_update_hash[100];
    sprintf(updatefilepath,"Updater.sh");
    //int type = 0;     // 0 - Updater.sh
                        // 1 - iotbaseserverlinux.sh
                        // 2 - iotdeviceeegserverlinux.sh
                        // other - Updater.sh
    
    #ifdef DEBUG
        printf("--//internal//-- Into function_update2.\r\n\r");
    #endif

    //FindUpdateServer();
    if (type==0) {
        printf("Sending1: ");
        snprintf(path_update_hash,100,"updatehash?type=%d?filepath=%s",type,updatefilepath);
    }   
    else {
        printf("Sending:2 ");
        snprintf(path_update_hash,50,"updatehash?type=%d",type);
    }
    snprintf(path_update_hash_clb,50,"/CALLBACK/UPDATEHASH?type=%d",type);    
    printf("Sending:3 ");
    memset((uint8_t*)hashes,0,sizeof(uint16_t)*HASHES_MAX);
    opt_path.num = COAP_OPTION_URI_PATH;
    opt_path.buf.len = strlen(path_update_hash);
    opt_path.buf.p = (uint8_t*)path_update_hash;
    pkt.tok_len = strlen(tok_update_hash);
    memcpy(pkt.tok_p, tok_update_hash, pkt.tok_len);
    printf("Sending: ");
    coap_make_msg(&scratch_buf, &pkt, &opt_path, 0, 0,
                       0, 0, 
                       0, id_out+=5, pkt.tok_p, pkt.tok_len, 
                       COAP_METHOD_GET, 
                       COAP_CONTENTTYPE_NONE);
    snprintf(command,100,"/REQUERY/UPDATEHASH?repeat=3&type=%s",type);
    printf("coap: ");
    if (!(rc = coap_build(buf, &pktlen, &pkt, path_update_hash_clb, command)))
    {
        printf("after coap: ");
//        Transfer((uint8_t*)buf,pktlen,"/updatehash");
        TransferUDP((uint8_t*)buf,pktlen,updateserver,5683);
    }
    #ifdef DEBUG
        printf("Sending: ");
        coap_dump(buf, pktlen, true);
        printf("\r\n\r");
    #endif
    #ifdef DEBUG
        printf("--//internal//-- Sended parts hash query.\r\n\r");
    #endif
    #ifdef DEBUG
        printf("--//internal//-- Into END of function_update.\r\n\r");
    #endif
    return;
}
int UpdateHash(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i = -1;
    FILE *fp;
    char filename[50];
    int num;
    uint16_t allhash = 0;
    int sizefp;
    int end;
    char buffer[STRING_SIZE];
    int type;
   
    #ifdef DEBUG
        printf("--//internal//-- Into UpdateHash.\r\n\r");
    #endif
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"size"))
            {
                size_parts = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
                printf("type got: %d\r\n\r", type);
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"filepath"))
            {
                strcpy(updatefilepath, TempParam->Params[i].strParam);
                printf("filepath got: %s\r\n\r", updatefilepath);
            }

        }
        
        //прочитать хэш нужного файла
        if (type==0) { //Updater.sh
            strcpy(filename, updatefilepath);
        }
        else if (type==1) { //iotbaseserverlinux.sh
            strcpy(filename, "./update/iotbaseserverlinux.sh");
        }
        else if (type==2) { //iotdeviceeegserverlinux.sh
            strcpy(filename, "./update/iotdeviceeegserverlinux.sh");
        }
        else if (type==3) { 
            strcpy(filename, "./update/iotdevicemovementlinux.sh");
        }
        else if (type==4) {
            strcpy(filename, "./update/iotdevicecameralinux.sh");
        }
        else if (type==5) {
            strcpy(filename, "./update/iotdevicegeneratorlinux.sh");
        }
        else strcpy(filename, "Updater.sh"); //Wrong type? Updater.sh then
        printf("THE FILE NAME IS***: %s\r\n\r", filename);

        fp = fopen(filename,"r"); // read mode

        if( fp == NULL )
        {
           printf("Error while opening update the file up_hash.\r\n\r");
           AddToTransmit("{\n\"UPDATEHASH\": [\n");
           snprintf(buffer,STRING_SIZE,"{\"hash\":0x%04X}",0);
           AddToTransmit(buffer);
           AddToTransmit("\n]\n}\n");
        }
        else {
        end = 0;
        num = 0;
        AddToTransmit("{\n\"UPDATEHASH\": [\n");
        while (end == 0)
        {
            sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
            #ifdef DEBUG
                printf("--//internal//-- %d readed from file.\r\n\r",sizefp);
            #endif

            allhash += CRC16ANSI(bufsa,sizefp);
//            snprintf(buffer,STRING_SIZE,"{\"part\":%d,\"hash\":",num);
//            AddToTransmit(buffer);
//            snprintf(buffer,STRING_SIZE,"0x%04X}",CRC16ANSI(bufsa,sizefp));
//            AddToTransmit(buffer);
            
            if (sizefp == 0)
                return(INVALID_PARAMETERS_ERROR);
            if (sizefp != size_parts)
            {
                end = 1;
                snprintf(buffer,STRING_SIZE,"{\"hash\":0x%04X}",allhash);
                AddToTransmit(buffer);
            }
//            else
//                AddToTransmit(",\n");
            num++;
        } 
        size_parts_cur = sizefp;
        AddToTransmit("\n]\n}\n");
        
        fclose(fp);
    }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }
    #ifdef DEBUG
        printf("--//internal//-- Into END of UpdateHash.\r\n\r");
    #endif
    return(ret_val);
}

int Update(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i = -1;
    FILE *fp;
    int num;
    int sizefp;
    int end;
    char filename[50];
    int type;
    
    #ifdef DEBUG
        printf("--//internal//-- Into Update.\r\n\r");
    #endif
    AddToTransmit("<UPDATE>\r\n\r");
    //AddToTransmit("<CALLBACKWELLKNOWN>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"part"))
            {
                ind_i = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"size"))
            {
                size_parts = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
                printf("type got: %d\r\n\r", type);
            }
        }
        
        if (type==0) {
            strcpy(filename, updatefilepath);
        }
        else if (type==1) {
            strcpy(filename, "./update/iotbaseserverlinux.sh");
        }
        else if (type==2) {
            strcpy(filename, "./update/iotdeviceeegserverlinux.sh");
        }
        else if (type==3) { 
            strcpy(filename, "./update/iotdevicemovementlinux.sh");
        }
        else if (type==4) {
            strcpy(filename, "./update/iotdevicecameralinux.sh");
        }
        else if (type==5) {
            strcpy(filename, "./update/iotdevicegeneratorlinux.sh");
        }
        else strcpy(filename, "Updater.sh");
        printf("THE FILE NAME IS***: %s\r\n\r", filename);

        fp = fopen(filename,"r"); // read mode
        content_type = COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;

        if( fp == NULL )
        {
           printf("Error while opening update the file update.\r\n\r");
           
        }
        else {

        end = 0;
        num = 0;
        #ifdef DEBUG
            printf("--//internal//-- Part %d .\r\n\r",ind_i);
        #endif
        if (ind_i == -1)
        {
            sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
            #ifdef DEBUG
                printf("--//internal//-- %d readed from file.\r\n\r",sizefp);
            #endif
            if (sizefp == 0)
                return(INVALID_PARAMETERS_ERROR);
            if (sizefp != size_parts)
                end = 1;
            make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
            size_parts_cur = sizefp;
            num++;
        }
        else
        {
            while (num <= ind_i)
            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                #ifdef DEBUG
                    printf("--//internal//-- %d readed from file.\r\n\r",sizefp);
                #endif
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);
                if (sizefp != size_parts)
                {
                    end = 1;
                }
                num++;
            } 
            num--;
            make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
            size_parts_cur = sizefp;
        }
        fclose(fp);
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }
    //AddToTransmit("</CALLBACKWELLKNOWN>\r\n\r");

    AddToTransmit("</UPDATE>\r\n\r");
    #ifdef DEBUG
        printf("--//internal//-- Into END of Update.\r\n\r");
    #endif
    return(ret_val);
}
#endif
/*============================================================================*/
