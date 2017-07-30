
/* Local headers -------------------------------------------------------------*/
#include "UpdateModule.h"
#include "coap.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "version.h"
#include "LogModule.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint16_t hashes[HASHES_MAX];
uint32_t hashes_cnt = 0;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
char tok_update[7];
const char *tok_update_hash="updhsh";
const char *path_update_reqry="/REQUERY/UPDATE";
char path_update_clb[50]="/CALLBACK/UPDATE?type=0";
char path_update_hash_clb[50]="/CALLBACK/UPDATEHASH?type=0";
//const char *updateserver = "10.9.91.105";
char *updateserver = "10.10.30.40";
//const char *updateserver = "10.10.30.35";
bool techServerFound = true;
const char *updatefile = "Updater.sh";
char *version = "1.3";
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
    int i,ind_i = 0,end;
    const char *ip = updateserver;
    char path_update[50];
    int port = 5683;
    int repeat = 2;
    char requery[100];
    int rc;
    coap_buffer_t tokfb;
    int pktlen = sizeof(scratch_raw);
    int type=0;
    
    DBG_LOG_DEBUG("Into QueryUpdate.\n");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        //printf("Before parameters.");
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
//            if (!strcmp(TempParam->Params[i-1].strParam,"port"))
//            {
//                port = TempParam->Params[i].intParam;
//            }
            if (!strcmp(TempParam->Params[i-1].strParam,"repeat"))
            {
                repeat = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
            }
        }
        //printf("After parameters.");
        if (repeat <= 0)
        {
            printf("No more repeats.");
            return 0;
        }
        
        snprintf(path_update,50,"update?type=%d",type);
        snprintf(path_update_hash_clb,50,"/CALLBACK/UPDATEHASH?type=%d",type);  
        snprintf(path_update_clb,50,"/CALLBACK/UPDATE?type=%d",type);  
        
        pktlen = sizeof(scratch_raw);
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
        if (repeat > 0)
        {
            snprintf(requery,100,
            "/REQUERY/UPDATE?part=%d&end=%d&repeat=%d&ip=%s&port=%d&type=%d"
                            ,ind_i,end,repeat-1,ip,port,type);
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_clb, requery)))
            {
                //Transfer((uint8_t*)scratch_raw,pktlen,"/update");
                TransferUDP((uint8_t*)scratch_raw,pktlen,updateserver,port);
            }
        }
        else
        {
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_clb, NULL)))
            {
                //Transfer((uint8_t*)scratch_raw,pktlen,"/update");
                TransferUDP((uint8_t*)scratch_raw,pktlen,updateserver,port);
            }
        }
        #ifdef DEBUG
            DBG_LOG_DEBUG("Sending: ");
            coap_dump(scratch_raw, pktlen, true);
        #endif
        DBG_LOG_TRACE("Sended %d part query.\n",ind_i);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        DBG_LOG_WARNING("Invalid parametest.\n");
    }

    DBG_LOG_DEBUG("Into END of QueryUpdate.\n");
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
    int pktlen = sizeof(scratch_raw);
    char path_update_hash[50];
    char path_update_hash_clb[50];
    int type;
    
    DBG_LOG_DEBUG("Into QueryUpdateHash.\n");
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
            }
        }
        if (repeat <= 0)
        {
            DBG_LOG_CRITICAL("No more repeats.");
            return 0;
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
            //printf(requery,"/REQUERY/UPDATEHASH?repeat=%d&type=%d",repeat-1, type);
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_hash_clb, requery)))
            {
        //        Transfer((uint8_t*)scratch_raw,pktlen,"/updatehash");
                TransferUDP((uint8_t*)scratch_raw,pktlen,updateserver,5683);
            }
        }
        else
        {
            requery[0] = 0;
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_hash_clb, NULL)))
            {
        //        Transfer((uint8_t*)scratch_raw,pktlen,"/updatehash");
                TransferUDP((uint8_t*)scratch_raw,pktlen,updateserver,5683);
            }
        }
        #ifdef DEBUG
            DBG_LOG_DEBUG("Sending: ");
            coap_dump(scratch_raw, pktlen, true);
        #endif
        DBG_LOG_TRACE("--//internal//-- Sended parts hash query.\n");
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        DBG_LOG_WARNING("--//internal//--  Invalid parametest.\n");
    }

    DBG_LOG_DEBUG("--//internal//-- Into END of QueryUpdateHash.\n");
    return(ret_val);
}


int Version(ParameterList_t *TempParam)
{
   int ret_val = 0;
   
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

int SetVersion(char *value)
{
   int ret_val = 0;
   version = value; 
   printf("VERSION: %s\n", VERSION);
   return(ret_val);
}

int SetUpdateServer(char *value)
{
   int ret_val = 0;
   updateserver = value;
   printf("updateserver ip: %s\n", updateserver);
   techServerFound = true;
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
    uint16_t allhash = 0;
    
    DBG_LOG_DEBUG("--//internal//-- Into CallbackUpdate.\n");
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
            }
        }
        //save to file
        if (type==0) { //Updater.sh
            strcpy(filename, "Updater.sh");
        }
        else if (type==1) { //iotbaseserverlinux.sh
            strcpy(filename, "iotbaseserverlinux_upd.sh");
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
        fp = fopen(namepart,"wb"); // write mode
        DBG_LOG_DEBUG("Create file %s\n",namepart);

        if( fp == NULL )
        {
           DBG_LOG_ERROR("Error while opening update the file callback_update.\n");
        }
        fwrite(scratch_buf.p,sizeof(uint8_t),scratch_buf.len,fp);
        
        allhash += CRC16ANSI(scratch_buf.p,scratch_buf.len);
        printf("allhash: %X\n",allhash);
        fclose(fp);
        //if endone then pack into monolite
        if (end)
        {
            snprintf(command,100,"/REQUERY/UPDATE?part=%d&end=%d&repeat=3&type=%d"
                                                                ,ind_i+1,end,type);
            CommandLineInterpreter(command);
        }
        else
        {
            snprintf(namepart,100,"%s",filename);
            sprintf(systemcommand, "sudo cp %s old_%s", filename, filename);
//            system(systemcommand);
            fp = fopen(namepart,"wb"); // read mode
            DBG_LOG_DEBUG("Create file %s\n",namepart);
            for(i=0;i<=ind_i;i++)
            {
                snprintf(namepart,100,"%s.p%02d",filename,i);
                fpo = fopen(namepart,"rb"); // read mode
                
                rsize = fread(scratch_buf.p,sizeof(uint8_t),1024,fpo);
                fwrite(scratch_buf.p,sizeof(uint8_t),rsize,fp);
                
                fclose(fpo);
                remove(namepart);
            }
            fclose(fp);
            
            //собрали. теперь выполним

            if (type==0) { //Updater.sh
                DBG_LOG_DEBUG("Execute file\n");
//                sprintf(systemcommand, "sudo sh %s", filename);
//                printf("Command: [%s]\r\n\r", systemcommand);
//                system(systemcommand);
//                printf("Command: sudo ~/iotserverdaemon/iotservdaemon 0\r\n\r");
//                system("sudo ~/iotserverdaemon/iotservdaemon 0");
                //system("sudo sh Updater.sh");
            }
            else {
//                sprintf(systemcommand, "sudo sh %s", filename);
//                printf("Command: [%s]\r\n\r", systemcommand);
//                system(systemcommand);
//                if (type==1) {
//                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 1]\r\n\r");
//                    system("sudo ~/iotserverdaemon/iotservdaemon 1");
//                }
//                else if (type==2) {
//                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 2]\r\n\r");
//                    system("sudo ~/iotserverdaemon/iotservdaemon 2");
//                }
//                else if (type==3) {
//                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 3]\r\n\r");
//                    system("sudo ~/iotserverdaemon/iotservdaemon 3");
//                }
//                else if (type==4) {
//                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 4]\r\n\r");
//                    system("sudo ~/iotserverdaemon/iotservdaemon 4");
//                }
//                else if (type==5) {
//                    printf("Command: [sudo ~/iotserverdaemon/iotservdaemon 5]\r\n\r");
//                    system("sudo ~/iotserverdaemon/iotservdaemon 5");
//                }
            }
            
            DBG_LOG_INFO("Shut down server\n");
//            exit(0);
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        DBG_LOG_WARNING("Invalid parametest.\n");
    }

    DBG_LOG_DEBUG("Into END of CallbackUpdate.\n");
    return(ret_val);
}
   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int CallbackUpdateHash(ParameterList_t *TempParam)
{
    int rc;
    coap_buffer_t tokfb;
    int pktlen = sizeof(scratch_raw);
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
    
    DBG_LOG_DEBUG("Into CallbackUpdateHash.\n");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
            }
        }
        
        //прочитать хэш нужного файла
        //если раздаёт BaseStation, читаем из update
        DBG_LOG_DEBUG("Device type***: %d\n", DEVICE);
        if (DEVICE == 0) {
            if (type==0) { //Updater.sh
                strcpy(filename, "Updater.sh");
            }
            else if (type==1) { //iotbaseserverlinux.sh
                strcpy(filename, "./update/iotbaseserverlinux2.sh");
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
        
        DBG_LOG_DEBUG("THE FILE NAME IS***: %s\n", filename);
        
        fp = fopen(filename,"rb"); // read mode

        if( fp != NULL )
        {
            end = 0;
            while (end == 0)
            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                DBG_LOG_DEBUG("%d readed from file.\n",sizefp);
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);

                allhash += CRC16ANSI(bufsa,sizefp);
                
                if (sizefp != size_parts)
                {
                    end = 1;
                }
            } 
            ptr = strstr(scratch_buf.p,"0x");
            //printf("ptr[6] %s \n", ptr[6]);
            if(ptr) {
            ptr[6] = 0;
            allhashserver = StringToUnsignedInteger(ptr);
            scratch_buf.p = ptr+1;
            fclose(fp); 
            DBG_LOG_DEBUG("%X <> %X.\n",allhashserver,allhash);
            if (allhashserver != allhash && allhash > 0)
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
                DBG_LOG_INFO("Updates already implemented.\n");
                //exit(0);
            }
            }
            else {
                printf("Pointer was null. Skipped\n");
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
        DBG_LOG_WARNING("Invalid parametest.\n");
    }

    DBG_LOG_DEBUG("Into END of CallbackUpdateHash.\n");
    return(ret_val);
}

int TechUpdate(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int i;
    char command[100];
    
    DBG_LOG_DEBUG("Into TechUpdate.\n");
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
        DBG_LOG_WARNING("Invalid parametest.\n");
    }
    DBG_LOG_DEBUG("Into END of TechUpdate.\n");
    return(ret_val);
}

void sendQueryNode(int type)
{
    char command[100];
    #ifdef CPU
    
    
    DBG_LOG_DEBUG("Into sendQueryNode.\n");
    snprintf(command,100,"/GET/QUERYNODES?part=0");
    CommandLineInterpreter(command);
    #endif
    return;
}

void function_update(int type)
{
    int rc;
    int pktlen = sizeof(scratch_raw);
    char command[100];
    char path_update_hash[100];
    sprintf(updatefilepath,"Updater.sh");
    //int type = 0;     // 0 - Updater.sh
                        // 1 - iotbaseserverlinux.sh
                        // 2 - iotdeviceeegserverlinux.sh
                        // other - Updater.sh
    
    DBG_LOG_DEBUG("Into function_update2.\n");
//    find_update_server();
    if (techServerFound==true) {
        //FindUpdateServer();
        if (type==0) {
            snprintf(path_update_hash,100,"updatehash?type=%d?filepath=%s",type,updatefilepath);
        }   
        else {
            snprintf(path_update_hash,50,"updatehash?type=%d",type);
        }
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
        snprintf(command,100,"/REQUERY/UPDATEHASH?repeat=3&type=%d",type);
        if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_hash_clb, command)))
        {
    //        Transfer((uint8_t*)scratch_raw,pktlen,"/updatehash");
            TransferUDP((uint8_t*)scratch_raw,pktlen,updateserver,5683);
        }
        #ifdef DEBUG
            DBG_LOG_DEBUG("Sending: ");
            coap_dump(scratch_raw, pktlen, true);
        #endif
        }
    else {
        printf("TechUpdateServer not found. Skipping update");
    }
    DBG_LOG_DEBUG("Into END of function_update.\n");
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
   
    DBG_LOG_DEBUG("Into UpdateHash.\n");
    printf("Into UpdateHash.\n");
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
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"filepath"))
            {
                strcpy(updatefilepath, TempParam->Params[i].strParam);
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
        else 
            strcpy(filename, "Updater.sh"); //Wrong type? Updater.sh then
        DBG_LOG_DEBUG("THE FILE NAME IS***: %s\n", filename);

        fp = fopen(filename,"rb"); // read mode
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
            sizefp = fread(scratch_raw,sizeof(uint8_t),size_parts,fp);
            printf("--//internal//-- %d readed from file.\r\n\r",sizefp);
                
            allhash += CRC16ANSI(scratch_raw,sizefp);
//            snprintf(buffer,STRING_SIZE,"{\"part\":%d,\"hash\":",num);
//            AddToTransmit(buffer);
//            snprintf(buffer,STRING_SIZE,"0x%04X}",CRC16ANSI(scratch_raw,sizefp));
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
/*
        if( fp == NULL )
        {
           DBG_LOG_ERROR("Error while opening update the file up_hash.\n");
           AddToTransmit("{\n\"UPDATEHASH\": [\n");
           snprintf(buffer,STRING_SIZE,"{\"hash\":0x%04X}",0);
           AddToTransmit(buffer);
           AddToTransmit("\n]\n}\n");
        }
        else 
        {
        end = 0;
        num = 0;
        AddToTransmit("{\n\"UPDATEHASH\": [\n");
        while (end == 0)
        {
            sizefp = fread(scratch_raw,sizeof(uint8_t),size_parts,fp);
            DBG_LOG_TRACE("%d readed from file.\n",sizefp);
            printf("%d readed from file.\n",sizefp);

            allhash += CRC16ANSI(scratch_raw,sizefp);
//            snprintf(buffer,STRING_SIZE,"{\"part\":%d,\"hash\":",num);
//            AddToTransmit(buffer);
//            snprintf(buffer,STRING_SIZE,"0x%04X}",CRC16ANSI(scratch_raw,sizefp));
//            AddToTransmit(buffer);

            if (sizefp == 0)
                return(INVALID_PARAMETERS_ERROR);
            if (sizefp != size_parts)
            {
                end = 1;
                snprintf(buffer,STRING_SIZE,"{\"hash\":0x%04X}",allhash);
                AddToTransmit(buffer);
            }
            num++;
        } 
        size_parts_cur = sizefp;
        AddToTransmit("\n]\n}\n");

        fclose(fp);
        }
*/
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        DBG_LOG_WARNING("Invalid parametest.\n");
    }
    DBG_LOG_DEBUG("Into END of UpdateHash.\n");
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
    uint16_t allhash = 0;
    
    #ifdef DEBUG
        DBG_LOG_DEBUG("--//internal//-- Into Update.\r\n\r");
    #endif
    AddToTransmit("<UPDATE>\r\n\r");
    
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
        else 
            strcpy(filename, "Updater.sh");
        DBG_LOG_DEBUG("THE FILE NAME IS***: %s\n", filename);

        fp = fopen(filename,"rb"); // read mode
        content_type = COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;

        if( fp == NULL )
        {
           printf("Error while opening update the file update.\r\n\r");
        }
        else 
        {
            end = 0;
            num = 0;
            DBG_LOG_DEBUG("Part %d .\r\n\r",ind_i);
            if (ind_i == -1)
            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                DBG_LOG_DEBUG("%d readed from file.\n",sizefp);
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);
                if (sizefp != size_parts)
                    end = 1;
                allhash += CRC16ANSI(&opt_part,sizefp);
                printf("allhash: %X\n",allhash);
                make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
                size_parts_cur = sizefp;
                printf("size_parts_cur: %X\n",size_parts_cur);
                num++;
            }
            else
            {
                while (num <= ind_i)
                {
                    sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                    DBG_LOG_DEBUG("%d readed from file.\n",sizefp);
                    if (sizefp == 0)
                        return(INVALID_PARAMETERS_ERROR);
                    if (sizefp != size_parts)
                    {
                        end = 1;
                    }
                    num++;
                } 
                num--;
                allhash += CRC16ANSI(&opt_part,sizefp);
                printf("allhash: %X\n",allhash);
                make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
                size_parts_cur = sizefp;
                printf("size_parts_cur: %X\n",size_parts_cur);
            }
            fclose(fp);
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        DBG_LOG_WARNING("Invalid parametest.\n");
    }

    AddToTransmit("</UPDATE>\r\n\r");
    DBG_LOG_DEBUG("Into END of Update.\n");
    return(ret_val);
}
#endif
/*============================================================================*/
