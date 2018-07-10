// ----------------------------------------------------------------------------
//
// UpdateModule.c - API to download update file, check and implement data.
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include "coap.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "version.h"
#include "LogModule.h"
#include "CRC16ANSI.h"
#include "UpdateModule.h"
#include "hashtable.h"
#include "common.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint16_t hashes[HASHES_MAX];
uint32_t hashes_cnt = 0;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
char tok_update[7];
const char *tok_update_hash="updhsh";
const char *path_update_reqry="/REQUERY/UPDATE";
char path_update_clb[STRING_SIZE]="/CALLBACK/UPDATE?type=0";
char path_update_hash_clb[STRING_SIZE]="/CALLBACK/UPDATEHASH?type=0";
char *updateserver = "10.10.30.35";
bool techServerFound = true;
bool fileHashMatched = true;
bool requeryFailed = false;
bool sentFirst = false;
int timeCounter = 0;
const char *updatefile = "Updater.sh";
char *version = "1.3";
/*============================================================================*/
uint32_t config_dev_type[CFG_SIZE];
char updatefilepath[STRING_SIZE]="./update/iotbaseserverlinux2.sh";
/*============================================================================*/
HashTable *table = NULL;

int updateStatus = -1;  // -1 - not started
                        //  1 - started
                        //  2 - in progress
//  3 - finished
/*============================================================================*/
const char *filename_0_1 = "Updater.sh";
const char *filename_1_1 = "iotbaseserverlinux.sh";
const char *filename_2_1 = "iotdeviceeegserverlinux.sh";
const char *filename_3_1 = "iotdevicemovementlinux.sh";
const char *filename_4_1 = "iotdevicecameralinux.sh";
const char *filename_5_1 = "iotdevicegeneratorlinux.sh";
const char *filename_1_2 = "./update/iotbaseserverlinux.sh";
const char *filename_2_2 = "./update/iotdeviceeegserverlinux.sh";
const char *filename_3_2 = "./update/iotdevicemovementlinux.sh";
const char *filename_4_2 = "./update/iotdevicecameralinux.sh";
const char *filename_5_2 = "./update/iotdevicegeneratorlinux.sh";
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
const char* GetFileName(uint32_t func);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
inline void InitCfgDevType(void) {
    config_dev_type[BASESTATION] = 0;
    config_dev_type[EEG] = 1;
    config_dev_type[MOVEMENT] = 2;
    config_dev_type[CAMERA] = 3;
    config_dev_type[GENERATOR] = 4;
}

//1 Local
//2 Update
inline const char* GetFileName(uint32_t func) {
    switch (func)
    {
        case 1:
            switch (DEVICE)
            {
                case 0:
                    return filename_0_1;
                    break;
                case 1:
                    return filename_1_1;
                    break;
                case 2:
                    return filename_2_1;
                    break;
                case 3:
                    return filename_3_1;
                    break;
                case 4:
                    return filename_4_1;
                    break;
                case 5:
                    return filename_5_1;
                    break;
                default:
                    return filename_0_1;
                    break;
            }
            break;
        case 2:
            switch (DEVICE)
            {
                case 0:
                    //return updatefilepath;
                    return filename_1_2;
                    break;
                case 1:
                    return filename_1_2;
                    break;
                case 2:
                    return filename_2_2;
                    break;
                case 3:
                    return filename_3_2;
                    break;
                case 4:
                    return filename_4_2;
                    break;
                case 5:
                    return filename_5_2;
                    break;
                default:
                    return filename_0_1;
                    break;
            }
            break;
        default:
            return NULL;
            break;
    }
    return NULL;
}

//#ifdef CPU
int QueryUpdate(ParameterList_t *TempParam)
{
    int ret_val = 0;
    int i,ind_i = 0;
    char path_update[STRING_SIZE];
    char requery[STRING_SIZE];
    char *ip;
    int port = 5683;
    int repeat = 2;
    int rc;
    size_t pktlen = sizeof(scratch_raw);
    int type=0;

    DBG_LOG_DEBUG("Into QueryUpdate.\n");
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
            if (!strcmp(TempParam->Params[i-1].strParam,"ip"))
            {
                ip = TempParam->Params[i].strParam;
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
            DBG_LOG_INFO("No more repeats.\n");
            requeryFailed = true;
            return 0;
        }
        
        snprintf(path_update,STRING_SIZE,"update?type=%d",type);
        snprintf(path_update_hash_clb,STRING_SIZE,"/CALLBACK/UPDATEHASH?type=%d",type);  
        snprintf(path_update_clb,STRING_SIZE,"/CALLBACK/UPDATE?type=%d",type);  
        
        pktlen = sizeof(scratch_raw);
        opt_path.num = COAP_OPTION_URI_PATH;
        opt_path.buf.len = strlen(path_update);
        opt_path.buf.p = (uint8_t*)path_update;
        make_part_option(&opt_part,ind_i,COAP_PART_SIZE_1024,0);
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
            snprintf(requery,STRING_SIZE,
                "/REQUERY/UPDATE?part=%d&repeat=%d&ip=%s&port=%d&type=%d"
                                    ,ind_i,repeat-1,ip,port,type);
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, 
                                                    path_update_clb, requery)))
            {
                TransferTo((uint8_t*)scratch_raw,pktlen,updateserver,port);
            }
        }
        else
        {
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_clb, NULL)))
            {
                TransferTo((uint8_t*)scratch_raw,pktlen,updateserver,port);
            }
        }
        #ifdef DEBUG
            DBG_LOG_DEBUG("Sending: ");
            //coap_dump(scratch_raw, pktlen, true);
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
    int i;
    int port = 5683;
    int repeat = 0;
    char requery[STRING_SIZE];
    int rc;
    size_t pktlen = sizeof(scratch_raw);
    char path_update_hash[STRING_SIZE];
    char path_update_hash_clb[STRING_SIZE];
    int type;
    
    DBG_LOG_DEBUG("Into QueryUpdateHash.\n");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
//            if (!strcmp(TempParam->Params[i-1].strParam,"ip"))
//            {
//                ip = TempParam->Params[i].strParam;
//            }
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
        snprintf(path_update_hash,STRING_SIZE,"updatehash?type=%d",type);
        snprintf(path_update_hash_clb,STRING_SIZE,"/CALLBACK/UPDATEHASH?type=%d",type);    
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
            snprintf(requery,STRING_SIZE,"/REQUERY/UPDATEHASH?repeat=%d&type=%d"
                                                            ,repeat-1, type);
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, 
                                            path_update_hash_clb, requery)))
            {
                TransferTo((uint8_t*)scratch_raw,pktlen,updateserver,5683);
            }
        }
        else
        {
            requery[0] = 0;
            if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, 
                                                path_update_hash_clb, NULL)))
            {
                TransferTo((uint8_t*)scratch_raw,pktlen,updateserver,5683);
            }
        }
        #ifdef DEBUG
            DBG_LOG_DEBUG("Sending: ");
            //coap_dump(scratch_raw, pktlen, true);
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
char* GetVersion()
{
    return(version);
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
    char namepart[STRING_SIZE];
    char command[STRING_SIZE];
    char systemcommand[STRING_SIZE];
    const char *filename;
    FILE *fpo;
    Array *value;
    int type;
    uint16_t allhash = 0;
    uint16_t hash = 0;
    int rc;
    
    char path_part_hash[STRING_SIZE];
    char path_part_hash_clb[STRING_SIZE];
    
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
        char *str;
        filename = GetFileName(1);       
        snprintf(namepart,STRING_SIZE,"%s.p%02d",filename,ind_i);
        if (hashtable_get(table, namepart, &value) != CC_OK) 
        {
            printf("NEW ANSWER: \n");
            
            WriteBlock(namepart);
            allhash = CRC16ANSI(scratch_buf.p,scratch_buf.len);
            printf("%04X CRC16ANSI(%d)\n",allhash,scratch_buf.len);
            //add line to table!
            enum cc_stat status = array_new(&value);
            char* filename2;
            char s[STRING_SIZE];
            int k = strlen(namepart)+1;
            filename2 = (char*) malloc(sizeof(char)*k); //should we free that prev malloc?
            strncpy(filename2, namepart , k+1);
            array_add(value, (void*) allhash);
            array_add(value, 0);
            array_add(value, ind_i);
            hashtable_add(table, filename2, (void*) value);

            PrintHashTable();
            askPartHash(type,ind_i);        
            if (!end)
            {
                updateStatus=4;
            }
        }
        else 
        {
            array_get_at(value, 1, (void*) &str);
            if (str != 1) {
                
                printf("FILE STATUS IS: %d\n", str);
                WriteBlock(namepart);
                allhash = CRC16ANSI(scratch_buf.p,scratch_buf.len);
                printf("%04X CRC16ANSI(%d)\n",allhash,scratch_buf.len);
                
                //add line to table!
                enum cc_stat status = array_new(&value);
                char* filename2;
                char s[STRING_SIZE];
                int k = strlen(namepart)+1;
                filename2 = (char*) malloc(sizeof(char)*k); //should we free that prev malloc?
                strncpy(filename2, namepart , k+1);
                array_add(value, (void*) allhash);
                array_add(value, 0);
                array_add(value, ind_i);
                //hash=CRC16ANSI(namepart,100);
                hashtable_add(table, filename2, (void*) value);

                PrintHashTable();
                
                askPartHash(type,ind_i); 
            }
            else 
            {
                DBG_LOG_WARNING("Got this answer already. Skipping!\n");
            }
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
    int ret_val = 0;
    int i;
    const char *filename;
    char command[STRING_SIZE];
    char systemcommand[STRING_SIZE];
    char *ptr;
    FILE *fp;
    int num;
    int sizefp;
    int end;
    Array *value;
    uint16_t allhash = 0;
    uint16_t allhashserver = 0;
    uint32_t type;
    
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
        
        DBG_LOG_DEBUG("Device type***: %d\n", DEVICE);
        
//        if (DEVICE == 0) 
//        {
//            filename = GetFileName(2);
//        }
//        else 
//        {
            filename = GetFileName(1);
//        }
        
        DBG_LOG_DEBUG("THE FILE NAME IS***: %s\n", filename);
        
        fp = fopen(filename,"rb"); // read mode

        if( fp != NULL )
        {
            end = 0;
            while (end == 0)
            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                DBG_LOG_DEBUG("%d readed from file.\n",sizefp);
                if (sizefp == 0) {
                    //jist delete the file (it is empty)
                    snprintf(systemcommand,STRING_SIZE,"sudo rm %s",filename);
                    DBG_LOG_DEBUG("system: %s\n",systemcommand);
                    system(systemcommand);
                    return(INVALID_PARAMETERS_ERROR);
                }

                allhash += CRC16ANSI(bufsa,sizefp);
                
                if (sizefp != size_parts)
                {
                    end = 1;
                }
            } 
            ptr = strstr(scratch_buf.p,"0x");
            if(ptr) 
            {
                ptr[6] = 0;
                //ok... now we need to rewrite that hash for the file. 
                //That means we need to destroy and then to recreate 
                //the only line we have
                DBG_LOG_DEBUG("trying to allocate memory\n");
                enum cc_stat status = array_new(&value);
                char* filename2;
                const char* s = GetFileName(1);
                uint32_t i = strlen(s);
                filename2 = (char*) malloc(sizeof(char)*i); 
                strncpy(filename2, s , i+1);

                array_add(value, (void*) allhash);
                array_add(value, 0);
                array_add(value, -1);
                hashtable_add(table, filename2, (void*) value);
                PrintHashTable();
                //line changed!

                allhashserver = StringToUnsignedInteger(ptr);
                fclose(fp); 
                DBG_LOG_DEBUG("%X <> %X.\n",allhashserver,allhash);
                if (allhashserver != allhash && allhash > 0)
                {
                    fileHashMatched = false;
                }
                else
                {
                    DBG_LOG_INFO("Updates already implemented.\n");
                    updateStatus = -1;
                }
            }
            else {
                DBG_LOG_DEBUG("Pointer was null. Skipped\n");
            }
        }
        else
        {
            DBG_LOG_DEBUG("No file on this side. Need update!\n");
            //ok... now we need to rewrite that hash for the file. 
            //That means we need to destroy and then to recreate 
            //the only line we have
            DBG_LOG_DEBUG("trying to allocate memory\n");
            enum cc_stat status = array_new(&value);
            char* filename2;
            const char* s = GetFileName(1);
            uint32_t i = strlen(s);
            filename2 = (char*) malloc(sizeof(char)*i); 
            strncpy(filename2, s , i+1);
            PrintHashTable();
            array_add(value, -1);
            array_add(value, 0); 
            array_add(value, -1);
            hashtable_add(table, filename2, (void*) value);
            PrintHashTable();
            //line changed!
            fileHashMatched = false;
            //updateStatus=1;
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        DBG_LOG_WARNING("Invalid parameters.\n");
    }

    DBG_LOG_DEBUG("Into END of CallbackUpdateHash.\n");
    return(ret_val);
}
int PartHash(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i = -1;
    FILE *fp;
    int num;
    int sizefp;
    int end;
    const char *filename;
    int type;
    uint16_t allhash = 0;
    uint8_t partBuffer[4096];
    char buffer[STRING_SIZE];
    
    #ifdef DEBUG
        DBG_LOG_DEBUG("--//internal//-- Into PartHash.\r\n\r");
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
            if (!strcmp(TempParam->Params[i-1].strParam,"size"))
            {
                size_parts = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
            }
        }
        
        filename = GetFileName(2);
        DBG_LOG_DEBUG("THE FILE NAME IS***: %s\n", filename);

        fp = fopen(filename,"rb"); // read mode
        
        if( fp == NULL )
        {
           DBG_LOG_DEBUG("Error while opening update file.\r\n\r");
           AddToTransmit("{\n\"PARTHASH\": [\n");
           snprintf(buffer,STRING_SIZE,"{\"parthash\":0x%04X}",0);
           AddToTransmit(buffer);
           AddToTransmit("\n]\n}\n");
        }
        else 
        {
            end = 0;
            num = 0;
            DBG_LOG_DEBUG("Part %d .\r\n\r",ind_i);
            AddToTransmit("{\n\"PARTHASH\": [\n");
            if (ind_i == -1)
            {
                sizefp = fread(partBuffer,sizeof(uint8_t),size_parts,fp);
                //DBG_LOG_DEBUG("%d readed from file.\n",sizefp);
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);
                if (sizefp != size_parts) {
                    end = 1;
                    allhash = CRC16ANSI(&partBuffer,sizefp);
                    DBG_LOG_DEBUG("allhash: %X\n",allhash);
                    snprintf(buffer,STRING_SIZE,"{\"hash\":0x%04X}",allhash);
                    AddToTransmit(buffer);

                    size_parts_cur = sizefp;
                    DBG_LOG_DEBUG("size_parts_cur: %X\n",size_parts_cur);
                    num++;
                }
            }
            else
            {
                while (num <= ind_i)
                {
                    sizefp = fread(partBuffer,sizeof(uint8_t),size_parts,fp);
                    DBG_LOG_DEBUG("%d:%d readed from file hash %04X.\n",
                            num,sizefp,CRC16ANSI(partBuffer,sizefp));
                    //coap_dump(partBuffer, sizefp, true);
                    if (sizefp == 0)
                        return(INVALID_PARAMETERS_ERROR);
                    if (sizefp != size_parts)
                    {
                        end = 1;
                    }
                    num++;
                } 
                num--;
                allhash = CRC16ANSI(partBuffer,sizefp);
                printf("allhash: %X\n",allhash);
                
                snprintf(buffer,STRING_SIZE,"{\"hash\":0x%04X}",allhash);
                AddToTransmit(buffer);
                size_parts_cur = sizefp;
                
                DBG_LOG_DEBUG("size_parts_cur: %X\n",size_parts_cur);
            }
            AddToTransmit("\n]\n}\n");
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

    //AddToTransmit("</PARTHASH>\r\n\r");
    DBG_LOG_DEBUG("Into END of PartHash.\n");
    return(ret_val);
}
int CallbackPartHash(ParameterList_t *TempParam)
{
    int ret_val = 0;
    int i,ind_i;
    char namepart[STRING_SIZE];
    int end;
    char *ptr;
    char *str;
    Array *value;
    uint16_t allhash = 0;
    uint16_t allhashserver = 0;
    const char *filename;
    int type;
    
    DBG_LOG_DEBUG("Into CallbackPartHash.\n");
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
            if (!strcmp(TempParam->Params[i-1].strParam,"type"))
            {
                type = TempParam->Params[i].intParam;
            }
        }
        
        DBG_LOG_DEBUG("Device type***: %d\n", DEVICE);
        
        filename = GetFileName(1);
        
        end = 0;
        
        snprintf(namepart,STRING_SIZE,"%s.p%02d",filename,ind_i);  
        DBG_LOG_DEBUG("THE FILE NAME IS***: %s\n", namepart);
        if (hashtable_get(table, namepart, &value) == CC_OK) 
        {
            array_get_at(value, 0, (void*) &str);
        }
        allhash = str;
        
        ptr = strstr(scratch_buf.p,"0x");
        
        if(ptr) 
        {
            ptr[6] = 0;
            allhashserver = StringToUnsignedInteger(ptr);
            DBG_LOG_DEBUG("%X <> %X.\n",allhashserver,allhash);
            if ((allhashserver != allhash) && (allhash > 0))
            {       
                if (hashtable_get(table, namepart, &value) == CC_OK) 
                {
                    array_replace_at(value, 1, 3, NULL);
                }
                else 
                {
                    DBG_LOG_DEBUG("Couldn't find %s key in table", namepart);
                }
            }
            else
            {
                DBG_LOG_INFO("File received correctly.\n");
                if (hashtable_get(table, namepart, &value) == CC_OK) 
                {
                    array_replace_at(value, 1, 1, NULL);
                }
                else 
                {
                    DBG_LOG_DEBUG("Couldn't find %s key in table", namepart);
                }
            }
            PrintHashTable();
        }
        else 
        {
            DBG_LOG_DEBUG("Pointer was null. Skipped\n");
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        DBG_LOG_WARNING("Invalid parameters.\n");
    }

    DBG_LOG_DEBUG("Into END of CallbackPartHash.\n");
    return(ret_val);
}
int TechUpdate(ParameterList_t *TempParam)
{
    int ret_val = 0;
    int i;
    
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
        AddToTransmit("Update request received!\r\n\r");
        AddToTransmit("</TECHUPDATE>\r\n\r");
        WriteMem(REG_UPD_File,1);
        updateStatus=1;
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
    #ifdef CPU
    char command[STRING_SIZE];
    DBG_LOG_DEBUG("Into sendQueryNode.\n");
    snprintf(command,STRING_SIZE,"/GET/QUERYNODES?part=0");
    CommandLineInterpreter(command);
    #endif
    return;
}
void setUpdateStatus(int value) 
{
    updateStatus = value;
    return;
}
void startUpdate() 
{
    char* filename2;
    printf("startUpdate.\n");
    const char* s = GetFileName(1);
    printf("GetFileName to s.\n");
    uint32_t i = strlen(s);
    filename2 = (char*) malloc(sizeof(char)*i); 
    printf("strncpy %d .\n",i);
    strncpy(filename2, s, i+1);
    TableEntry *entry;
    HashTableIter hti;
    //updateStatus = 1;
    Array *value;
    uint16_t hash = 0;
    
    printf("table.\n");
    if (table!=NULL) {     
        //free memory from all arrays within
        if (table!=NULL) {
            hashtable_iter_init(&hti, table);
            while (hashtable_iter_next(&hti, &entry) != CC_ITER_END) {
                DestroyLine(entry->key);
            }
        }
        printf("hashtable_destroy\n");
        //and destroy the table
        hashtable_destroy(table);
    }
    
    printf("CreateHashTable\n");
    CreateHashTable();
    enum cc_stat status = array_new(&value);
    printf("Creating array with:\n");
    printf("hash: %d\n", 0);
    printf("filename: %s\n", filename2);
    array_add(value, (void*) hash);
    array_add(value, 0);
    array_add(value, -1);
    
    hashtable_add(table, (void*) filename2, (void*) value);
    
    PrintHashTable();
    return;
}
int checkHash(char* filename) 
{
    int result;
    Array *value;
    uint16_t hh;
    DBG_LOG_DEBUG("Into checkHash.\n");
    if (hashtable_get(table, filename, &value) == CC_OK) 
    {
        DBG_LOG_TRACE("array_get_at.\n");
        array_get_at(value, 0, (void*) &hh);
        if (hh == 0) 
        {
            DBG_LOG_TRACE("result 1.\n");
            result = 1;
        }
        else 
        {
            DBG_LOG_TRACE("result 0.\n");
            result = 0;
        }
    }
    else 
    {
        DBG_LOG_TRACE("result -1.\n");
        result = -1;
    }
    return result;
}
// 0 - Updater.sh
// 1 - iotbaseserverlinux.sh
// 2 - iotdeviceeegserverlinux.sh
// other - Updater.sh
void function_update(int type)
{
    int n = 3; //number of iterations to wait
    char command[STRING_SIZE];
    const char *filename;
    filename = GetFileName(1);        
    snprintf(updatefilepath,STRING_SIZE,"Updater.sh");
    uint32_t part = 0;
    timeCounter = timeCounter+1;        
    DBG_LOG_DEBUG("Into function_update.\n");
    DBG_LOG_DEBUG("Into function_update. Status: %d timeCounter: %d\n", updateStatus, timeCounter);   
    switch (updateStatus) {
        case -1:                                //not started
            break;
        case 1:                                 //needs to be started. Find update server. Ask hash.
            //if (FindUpdateServer()) {;        //if update server found
                startUpdate();                      //creates hash table
                PrintHashTable();
                askUpdateFileHash(type);          
                timeCounter = 0;                    //reset clock
                updateStatus = 2;                   //hash requested 
            //}
            break;
        case 2:                                 //needs to be started
            PrintHashTable();
            filename = GetFileName(1);  
            printf("GetFileName to %s.\n",filename);  
            if (checkHash(filename)) {                  //if never got a responce with hash (hash of update file == 0)
                printf("askUpdateFileHash.\n");  
                if (timeCounter > n) {          //and wait time for responce went off
                    askUpdateFileHash(type);    //ask for hash again
                    timeCounter = 0;            //reset clock
                }
            }
            else {                              //start asking for file parts starting with 1 part
                part = 0;
                DBG_LOG_DEBUG("ASKING FOR PART NUMBER %d\n", part);
                snprintf(command,STRING_SIZE,"/REQUERY/UPDATE?part=%d&repeat=3&type=%d",part,type);
                DBG_LOG_DEBUG("command: %s \n",command);
                CommandLineInterpreter(command);
                updateStatus = 3;
                timeCounter = 0;                //reset clock
            }
            break;
        case 3: 
            PrintHashTable();                                                   //requesting file parts
            if (timeCounter > n) {                             //if no more repeats or wait time for response went off
                timeCounter = 0;                                                //reset clock
                DBG_LOG_DEBUG("search for a part that is not present\n");
                part = hashtable_size(table)-1;
                DBG_LOG_DEBUG("ASKING FOR PART NUMBER %d\n", part);
                requeryFailed = false;
                snprintf(command,STRING_SIZE,"/REQUERY/UPDATE?part=%d&repeat=3&type=%d",part,type);
                DBG_LOG_DEBUG("command: %s \n",command);
                CommandLineInterpreter(command);
            }
            break;
        case 4:                                //recheck table
            DBG_LOG_DEBUG("Got last part\n");
            DBG_LOG_DEBUG("Cheking table for files with wrong status\n");
            part=-1;
            part=findNextPart(filename);
            if (part!=-1) {
                DBG_LOG_DEBUG("ASKING FOR PART NUMBER %d\n", part);
                snprintf(command,STRING_SIZE,"/REQUERY/UPDATE?part=%d&repeat=3&type=%d",part,type);
                DBG_LOG_DEBUG("command: %s \n",command);
                CommandLineInterpreter(command);
            }
            else {
                updateStatus = 5;
            }
            timeCounter = 0;                                                //reset clock
            break;
        case 5:                                //finished
            updateStatus = 6;
            FormUpdateFile(type, hashtable_size(table)-2);
            timeCounter = 0;                                                //reset clock
            break;
        case 6:
            DBG_LOG_DEBUG("Updates were finished recently. Skipping update\n");    //alternatively check hash (updateStatus = 1;)
            //updateStatus = 1;
            timeCounter = 0; 
            break;
        default:
            DBG_LOG_DEBUG("Update module deactivated.\n");
            break;
    }
    DBG_LOG_DEBUG("Into END of function_update.\n");
    return;
}
int UpdateHash(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i = -1;
    FILE *fp;
    const char *filename;
    int num;
    uint16_t allhash = 0;
    int sizefp;
    int end;
    char buffer[STRING_SIZE];
    int type;
   
    DBG_LOG_DEBUG("Into UpdateHash.\n");
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
        
        filename = GetFileName(2);
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
        else 
        {
            end = 0;
            num = 0;
            AddToTransmit("{\n\"UPDATEHASH\": [\n");
            while (end == 0)
            {
                sizefp = fread(scratch_raw,sizeof(uint8_t),size_parts,fp);
                DBG_LOG_DEBUG("%d:%d readed from file hash %04X.\n",
                            num,sizefp,CRC16ANSI(scratch_raw,sizefp));
                allhash += CRC16ANSI(scratch_raw,sizefp);
                if (sizefp == 0) 
                {
                    return(INVALID_PARAMETERS_ERROR);
                }
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
    const char *filename;
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
        
        filename = GetFileName(2);
        DBG_LOG_DEBUG("THE FILE NAME IS***: %s\n", filename);

        fp = fopen(filename,"rb"); // read mode
        content_type = COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;

        if( fp == NULL )
        {
           printf("Error while opening update file.\r\n\r");
        }
        else 
        {
            end = 0;
            num = 0;
            DBG_LOG_DEBUG("Part %d .\r\n\r",ind_i);
            if (ind_i == -1)
            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                //DBG_LOG_DEBUG("%d readed from file.\n",sizefp);
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
                    DBG_LOG_DEBUG("%d:%d readed from file hash %04X.\n",
                            num,sizefp,CRC16ANSI(bufsa,sizefp));
                    //coap_dump(bufsa, sizefp, true);
                    if (sizefp == 0)
                        return(INVALID_PARAMETERS_ERROR);
                    if (sizefp != size_parts)
                    {
                        end = 1;
                    }
                    num++;
                } 
                num--;
                allhash += CRC16ANSI(bufsa,sizefp);
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
        DBG_LOG_WARNING("Invalid parameters.\n");
    }

    AddToTransmit("</UPDATE>\r\n\r");
    DBG_LOG_DEBUG("Into END of Update.\n");
    return(ret_val);
}

int CreateHashTable()
{
    int  ret_val = 0;
    DBG_LOG_INFO("Creating hash table\n");
    hashtable_new(&table);
    return ret_val;
}
void DestroyLine(char* filename) {
    Array *value;
    DBG_LOG_INFO("Searching for line: %s\n", filename);
    if (hashtable_get(table, filename, &value) == CC_OK) {
        DBG_LOG_INFO("try to destroy array\n");
        array_destroy(value);
        //array_destroy_free(value); ERROR
        DBG_LOG_INFO("array destroyed\n");
        enum cc_stat stat = hashtable_remove(table, filename, NULL);
        DBG_LOG_INFO("Freed memory from line: %s\n", filename);
    }
    return;
}
void PrintHashTable() {
    TableEntry *entry;
    Array *value;
    ArrayIter ai;
    char *str1;
    char *str2;
    char *str3;
    int counter = 0;
    HashTableIter hti;
    if (table!=NULL) {
        hashtable_iter_init(&hti, table);
        DBG_LOG_INFO("------------------------------------------------------------\n");
        DBG_LOG_INFO("|   ID  |      FILENAME      |   HASH    | STATUS |   NUM  |\n");
        DBG_LOG_INFO("------------------------------------------------------------\n");
        while (hashtable_iter_next(&hti, &entry) != CC_ITER_END) {
            value = entry->value;
            array_iter_init(&ai,value);
            array_get_at(value, 0, (void*) &str1);
            array_get_at(value, 1, (void*) &str2);
            array_get_at(value, 2, (void*) &str3);
            DBG_LOG_INFO("|%7d|%20s|%11X|%8d|%8d|\n", 
                    counter, entry->key, str1, str2, str3);
            counter=counter+1;
        }
    }
}
int findNextPart(char* filename) 
{
    TableEntry *entry;
    Array *value;
    ArrayIter ai;
    char *str1;
    char *str2;
    char *str3;
    int counter = 0;
    HashTableIter hti;
    bool found = false;
    int result = -1;
    int status = -1;
    
    if (table!=NULL) {
        hashtable_iter_init(&hti, table);
        while (hashtable_iter_next(&hti, &entry) != CC_ITER_END && found != true) { //РїРѕРєР° РЅРµ РїРѕСЃР»РµРґРЅРёР№ РёР»Рё СЌР»РµРјРµРЅС‚ РЅРµ РЅР°Р№РґРµРЅ
            
            value = entry->value;
            array_iter_init(&ai,value);
            array_get_at(value, 0, (void*) &str1);
            array_get_at(value, 1, (void*) &str2);
            array_get_at(value, 2, (void*) &str3);
            DBG_LOG_INFO("|%10d|%20s|%10X|%10d|%10d|\n", 
                    counter, entry->key, str1, str2, str3);
            status = str2;
            if (status == 0 && (str3 != -1)) {
                DBG_LOG_INFO("found at: %d\n",counter);
                found = true;
                result = str3;
            }
            
            counter=counter+1;
        }
    }
    
    return result;
}
void askPartHash(int type, int part) 
{
    int rc;
    char command[STRING_SIZE];
    char path_update_hash[STRING_SIZE];
    size_t pktlen = sizeof(scratch_raw);
    
    DBG_LOG_INFO("Sending part hash\n");
    
    snprintf(path_update_hash,STRING_SIZE,"parthash?type=%d&part=%d",type,part);
    
    snprintf(path_update_hash_clb,STRING_SIZE,"/CALLBACK/PARTHASH?type=%d&part=%d",type,part);    
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
    snprintf(command,STRING_SIZE,"/REQUERY/UPDATEHASH?repeat=3&type=%d",type);
    if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_hash_clb, NULL)))
    {
        TransferTo((uint8_t*)scratch_raw,pktlen,updateserver,5683);
    }
    #ifdef DEBUG
        DBG_LOG_DEBUG("Sending: ");
        coap_dump(scratch_raw, pktlen, true);
    #endif
    return;
}
void askUpdateFileHash(int type) 
{    
    int rc;
    char command[STRING_SIZE];
    char path_update_hash[STRING_SIZE];
    size_t pktlen = sizeof(scratch_raw);
    
    DBG_LOG_INFO("Searching for a new version of update file\n");
    if (type==0) {
        snprintf(path_update_hash,STRING_SIZE,"updatehash?type=%d?filepath=%s",type,updatefilepath);
    }   
    else {
        snprintf(path_update_hash,STRING_SIZE,"updatehash?type=%d",type);
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
    snprintf(command,STRING_SIZE,"/REQUERY/UPDATEHASH?repeat=3&type=%d",type);
    if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_update_hash_clb, command)))
    {
        TransferTo((uint8_t*)scratch_raw,pktlen,updateserver,5683);
    }
    #ifdef DEBUG
        DBG_LOG_DEBUG("Sending: ");
        coap_dump(scratch_raw, pktlen, true);
    #endif
    return;
}
//#endif
/*============================================================================*/