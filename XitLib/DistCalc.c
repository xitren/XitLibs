
/* Local headers -------------------------------------------------------------*/
#include "DistCalc.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*============================================================================*/

/* Private defines -----------------------------------------------------------*/
#define MAXEXTMEM 4000
#define EXTMEMTIMEOUT 10
#define EXTMEMBUFFER 2000*4
/*============================================================================*/

/* Private extern ------------------------------------------------------------*/
extern coap_rw_buffer_t scratch_buf;
/*============================================================================*/

/* Private structures --------------------------------------------------------*/
#ifdef EXTMEMSERVER
    typedef struct _tagExtMemMapSrv_t
    {
       uint8_t *_ptr;
       uint32_t _dlen;
       uint32_t _extid;
       uint8_t  isSet;
       uint8_t  clock;
    } ExtMem_t;
#else
    typedef struct _tagExtMemMap_t
    {
       uint32_t _intid;
       uint32_t _extid;
       uint8_t  isSet;
       uint8_t  clock;
    } ExtMem_t;
#endif
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint32_t now_clock = 0;
uint32_t free_cycles = 0;
uint32_t max_free_cycles = 1;
uint32_t last_free_cycles = 0;
static char path_mem_buf[100];
static char path_arg_buf[100];
static ExtMem_t memMap[MAXEXTMEM];
uint32_t memMapCnt = 0;
static uint8_t memMapBuffer[EXTMEMBUFFER];
uint32_t memMapBufferCnt = 0;
#ifdef EXTMEMSERVER
    uint32_t extCnt = 1;
    uint8_t rc;
#endif
/*============================================================================*/
    
/* Private constants ---------------------------------------------------------*/
const char *path_mem="extmemory";
#ifdef EXTMEMSERVER
#else
    const char *path_mem_clb_cr="/CALLBACK/EXTMEMORY/CREATE";
    const char *path_mem_clb_ret="/CALLBACK/EXTMEMORY/RETURN";
#endif
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void ClearExtMem(void)
{
    #ifdef EXTMEMSERVER
        int i;
        for (i=0;i<memMapCnt;i++)
            if (memMap[i]._ptr) free(memMap[i]._ptr);
    #endif
    memMapCnt = 0;
    return;
}
#ifdef EXTMEMSERVER
    uint32_t GetSize(uint32_t _extid)
    {
        int i;
        for (i=0;i<memMapCnt;i++)
            if (memMap[i]._extid == _extid)
                return memMap[i]._dlen;
        return 0;
    }
    uint8_t* GetPointer(uint32_t _extid)
    {
        int i;
        for (i=0;i<memMapCnt;i++)
            if (memMap[i]._extid == _extid)
                return memMap[i]._ptr;
        return 0;
    }
    int ExtMemCreateReq(ParameterList_t *TempParam)
    {
        int  ret_val = 0;
        int  Clock = -1;
        int i;
         uint32_t _intid;

        #ifdef DEBUG
           printf("--//internal//-- Into ExtMemCreateReq.\r\n\r");
        #endif
        AddToTransmit("<EXTMEMORY>\r\n\r");
        /* First check to see if the parameters required for the execution of*/
        /* this function appear to be semi-valid.                            */
        if ((TempParam) && (TempParam->NumberofParameters > 1))
        {
            for (i=1;i<TempParam->NumberofParameters;i+=2)
            {
                if (!strcmp(TempParam->Params[i-1].strParam,"intmemid"))
                {
                    _intid = (unsigned int)(TempParam->Params[i].intParam);
                }
            }
            if (_intid > 0)
            {
                if (memMapCnt >= MAXEXTMEM)
                {
                    #ifdef DEBUG
                       printf("--//internal//-- EXT memory depleted.\r\n\r");
                    #endif
                    pktlen = sizeof(buf);
                    sprintf((char *)path_arg_buf,"intmemid=%d&extmemid=%d",
                                                                    _intid,0);
                    opt_args.num = COAP_OPTION_URI_QUERY;
                    opt_args.buf.p = path_arg_buf;
                    opt_args.buf.len = strlen(path_arg_buf);
//                    coap_make_response(&scratch_buf, &rsppkt, 0,
//                                    path_arg_buf, strlen(path_arg_buf), 
//                                    pkt.hdr.id[0], pkt.hdr.id[1], 
//                                    &pkt.tok, COAP_RSPCODE_BAD_REQUEST, 
//                                    COAP_CONTENTTYPE_TEXT_PLAIN);
//                    coap_make_msg(&scratch_buf, &pkt, &opt_path, &opt_args,
//                                       NULL, 0, 
//                                       0, id_out++, 0, 
//                                       COAP_METHOD_PUT, 
//                                       COAP_CONTENTTYPE_NONE);
                    memMapCnt++;
                    #ifdef DEBUG
                        printf("---------------> CoAP packet start.\r\n\r");
                        coap_dumpPacket(&pkt);
                        printf("---------------> CoAP packet end.\r\n\r");
                    #endif
//                    if (!(rc = coap_build(buf, &pktlen, &pkt)))
//                      Transfer((uint8_t*)buf,pktlen);
                    return EXT_MEM_FUNCTION_BUFFERSIZE_ERROR; 
                }
                AddToTransmit("<DATA_TRANSLATED/>\r\n\r");
                memMap[memMapCnt]._extid = extCnt++;
                memMap[memMapCnt]._ptr = (uint8_t *)malloc(scratch_buf.len);
                memcpy(memMap[memMapCnt]._ptr,scratch_buf.p,
                        memMap[memMapCnt]._dlen = scratch_buf.len);
                memMap[memMapCnt].clock = 0;
                memMap[memMapCnt].isSet = 1;
                pktlen = sizeof(buf);
                //printf("%s %d\r\n\r",path_mem_buf,strlen(path_mem_buf));
                sprintf((char *)path_arg_buf,"intmemid=%d&extmemid=%d",
                        _intid,memMap[memMapCnt]._extid);
                #ifdef DEBUG
                    printf("--//internal//-- EXT mem translated extid = %d.\r\n\r",
                            memMap[memMapCnt]._extid);
                #endif
                opt_args.num = COAP_OPTION_URI_QUERY;
                opt_args.buf.p = path_arg_buf;
                opt_args.buf.len = strlen(path_arg_buf);
                
//                coap_make_response(&scratch_buf, &rsppkt, 0,
//                                path_arg_buf, strlen(path_arg_buf), 
//                                pkt.hdr.id[0], pkt.hdr.id[1], 
//                                &pkt.tok, COAP_RSPCODE_CONTENT, 
//                                COAP_CONTENTTYPE_TEXT_PLAIN);
//                coap_make_msg(&scratch_buf, &pkt, &opt_path, &opt_args,
//                                   NULL, 0, 
//                                   0, id_out++, 0, 
//                                   COAP_METHOD_PUT, 
//                                   COAP_CONTENTTYPE_NONE);
                memMapCnt++;
                #ifdef DEBUG
                    printf("---------------> CoAP packet start.\r\n\r");
                    coap_dumpPacket(&rsppkt);
                    printf("---------------> CoAP packet end.\r\n\r");
                #endif
//                if (!(rc = coap_build(buf, &pktlen, &pkt)))
//                  Transfer((uint8_t*)buf,pktlen);
            }
        }
        else
        {
            /* One or more of the necessary parameters are invalid.           */
            ret_val = INVALID_PARAMETERS_ERROR;
            AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
            #ifdef DEBUG
               printf("--//internal//--  Invalid parameters.\r\n\r");
            #endif
        }
        AddToTransmit("</EXTMEMORY>\r\n\r");

        return(ret_val);
    }
    int ExtMemDeleteReq(ParameterList_t *TempParam)
    {
        int  ret_val = 0;
        int  Clock = -1;
        int i,j;
        uint32_t _extid;

        #ifdef DEBUG
           printf("--//internal//-- Into ExtMemCreateReq.\r\n\r");
        #endif
        AddToTransmit("<EXTMEMORY>\r\n\r");
        /* First check to see if the parameters required for the execution of*/
        /* this function appear to be semi-valid.                            */
        if ((TempParam) && (TempParam->NumberofParameters > 1))
        {
            for (i=1;i<TempParam->NumberofParameters;i+=2)
            {
                if (!strcmp(TempParam->Params[i-1].strParam,"extmemid"))
                {
                    _extid = (unsigned int)(TempParam->Params[i].intParam);
                }
            }
            if (_extid > 0)
            {
                for (i=0;i<memMapCnt;i++)
                    if (memMap[i]._extid == _extid)
                    {
                        #ifdef DEBUG
                           printf("--//internal//--  EXT data erased.\r\n\r");
                        #endif
                        AddToTransmit("<DATA_DELETED/>\r\n\r");
                        free(memMap[i]._ptr);
                        for (j=i+1;j<memMapCnt;j++)
                            memMap[j-1] = memMap[j];
                        memMapCnt--;
                        return 0;
                    }
            }
        }
        else
        {
            /* One or more of the necessary parameters are invalid.           */
            ret_val = INVALID_PARAMETERS_ERROR;
            AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
            #ifdef DEBUG
               printf("--//internal//--  Invalid parameters.\r\n\r");
            #endif
        }
        AddToTransmit("</EXTMEMORY>\r\n\r");

        return(ret_val);
    }
    int ExtMemClearReq(ParameterList_t *TempParam)
    {
        int  ret_val = 0;
        int  Clock = -1;
        int i,j;
        uint32_t _extid;

        #ifdef DEBUG
           printf("--//internal//-- Into ExtMemClearReq.\r\n\r");
        #endif
        AddToTransmit("<EXTMEMORY>\r\n\r");
        /* First check to see if the parameters required for the execution of*/
        /* this function appear to be semi-valid.                            */
        if ((TempParam))
        {
            ClearExtMem();
            printf("--//internal//-- ExtMem CLEARED.\r\n\r");
            AddToTransmit("<CLEARED/>\r\n\r");
        }
        else
        {
            /* One or more of the necessary parameters are invalid.           */
            ret_val = INVALID_PARAMETERS_ERROR;
            AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
            #ifdef DEBUG
               printf("--//internal//--  Invalid parameters.\r\n\r");
            #endif
        }
        AddToTransmit("</EXTMEMORY>\r\n\r");

        return(ret_val);
    }
    int ExtMemGetReq(ParameterList_t *TempParam)
    {
        int  ret_val = 0;
        int i;
        uint32_t _extid;

        #ifdef DEBUG
           printf("--//internal//-- Into ExtMemGetReq.\r\n\r");
        #endif
        AddToTransmit("<EXTMEMORY>\r\n\r");
        /* First check to see if the parameters required for the execution of*/
        /* this function appear to be semi-valid.                            */
        if ((TempParam) && (TempParam->NumberofParameters > 1))
        {
            for (i=1;i<TempParam->NumberofParameters;i+=2)
            {
                if (!strcmp(TempParam->Params[i-1].strParam,"extmemid"))
                {
                    _extid = (unsigned int)(TempParam->Params[i].intParam);
                }
            }
            if (_extid > 0)
            {
                for (i=0;i<memMapCnt;i++)
                    if (memMap[i]._extid == _extid)
                    {
                        AddToTransmit("<DATA_TRANSMITTED/>\r\n\r");
                        #ifdef DEBUG
                           printf("--//internal//--  EXT data transmitted.\r\n\r");
                        #endif
                        memMap[i]._extid = _extid;
                        pktlen = sizeof(buf);
//                        opt_path.num = COAP_OPTION_URI_PATH;
//                        opt_path.buf.p = path_mem_clb_get;
//                        opt_path.buf.len = strlen(path_mem_clb_get);
//                        //printf("%s %d\r\n\r",path_mem_buf,strlen(path_mem_buf));
//                        sprintf((char *)path_arg_buf,"extmemid=%d",
//                                                    memMap[memMapCnt]._extid);
//                        opt_args.num = COAP_OPTION_URI_QUERY;
//                        opt_args.buf.p = path_arg_buf;
//                        opt_args.buf.len = strlen(path_arg_buf);
                
//                        coap_make_response(&scratch_buf, &rsppkt, 0,
//                                        memMap[i]._ptr, memMap[i]._dlen, 
//                                        pkt.hdr.id[0], pkt.hdr.id[1], 
//                                        &pkt.tok, COAP_RSPCODE_CONTENT, 
//                                        COAP_CONTENTTYPE_NONE);
//                        coap_make_msg(&scratch_buf, &pkt, &opt_path, &opt_args,
//                                           memMap[i]._ptr, memMap[i]._dlen, 
//                                           0, id_out++, 0, 
//                                           COAP_METHOD_PUT, 
//                                           COAP_CONTENTTYPE_NONE);
                        #ifdef DEBUG
                            printf("---------------> CoAP packet start.\r\n\r");
                            coap_dumpPacket(&rsppkt);
                            printf("---------------> CoAP packet end.\r\n\r");
                        #endif
//                        if (!(rc = coap_build(buf, &pktlen, &pkt)))
//                          Transfer((uint8_t*)buf,pktlen);
                        return 0;
                    }

//                coap_make_response(&scratch_buf, &rsppkt, 0,
//                                NULL, 0, 
//                                pkt.hdr.id[0], pkt.hdr.id[1], 
//                                &pkt.tok, COAP_RSPCODE_NOT_FOUND, 
//                                COAP_CONTENTTYPE_NONE);
                #ifdef DEBUG
                    printf("---------------> CoAP packet start.\r\n\r");
                    coap_dumpPacket(&rsppkt);
                    printf("---------------> CoAP packet end.\r\n\r");
                #endif
            }
        }
        else
        {
            /* One or more of the necessary parameters are invalid.           */
            ret_val = INVALID_PARAMETERS_ERROR;
            AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
            #ifdef DEBUG
               printf("--//internal//--  Invalid parameters.\r\n\r");
            #endif
        }
        AddToTransmit("</EXTMEMORY>\r\n\r");

        return(ret_val);
    }
    #ifdef DEBUG
        int ExtMemDump(void)
        {
            int i,j;
            printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\r\n\r");
            for (i=0;i<memMapCnt;i++)
            {
                printf("+++++++++++++++++++++++++++++++++++\r\n\r");
                printf("%d memory item with len %d\r\n\r",i,memMap[i]._dlen);
                printf("\r\n\r");
                for (j=0;j<memMap[i]._dlen;j++)
                {
                    printf("%02X ",memMap[i]._ptr[j]);
                }
                printf("\r\n\r\r\n\r");
                for (j=0;j<memMap[i]._dlen;j++)
                {
                    printf("%c ",memMap[i]._ptr[j]);
                }
                printf("\r\n\r");
                printf("+++++++++++++++++++++++++++++++++++\r\n\r");
            }
            printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\r\n\r");
            return 0;
        }
    #endif
#else
//    int CreateExtMemReq(uint8_t *data, uint32_t *datalen, uint32_t _intid)
//    {
//        int pntr = memMapCnt++, rc;
//        memMap[pntr]._intid = _intid;
//        memMap[pntr].isSet = 0;
//        memMap[pntr].clock = 0;
//        //ToDo: Meake query
//        pktlen = sizeof(buf);
//        sprintf((char *)path_mem_buf,"%s",path_mem);
//        opt_path.num = COAP_OPTION_URI_PATH;
//        opt_path.buf.p = (uint8_t*)path_mem_buf;
//        opt_path.buf.len = strlen(path_mem_buf);
//        //printf("%s %d\r\n\r",path_mem_buf,strlen(path_mem_buf));
//        sprintf((char *)path_arg_buf,"intmemid=%d",(int)_intid);
//        opt_args.num = COAP_OPTION_URI_QUERY;
//        opt_args.buf.p = (uint8_t*)path_arg_buf;
//        opt_args.buf.len = strlen(path_arg_buf);
//        //printf("%s %d\r\n\r",path_arg_buf,strlen(path_arg_buf));
//        coap_make_msg(&scratch_buf, &pkt, &opt_path, &opt_args, 0,
//                           data, *datalen, 
//                           0, id_out++, 0, 
//                           COAP_METHOD_PUT, 
//                           COAP_CONTENTTYPE_NONE);
//        //coap_dumpPacket(&pkt);
//        if (!(rc = coap_build(buf, &pktlen, &pkt, path_mem_clb_cr)))
//          Transfer((const uint8_t*)buf,pktlen,path_mem);
//        #ifdef DEBUG
//            printf("---------------> CoAP packet start.\r\n\r");
//            coap_dumpPacket(&pkt);
//            printf("---------------> CoAP packet end.\r\n\r");
//        #endif
//        //Transfer(data,*datalen);
//        //while ((!memMap[pntr].isSet) && (memMap[pntr].clock < EXTMEMTIMEOUT))
//        //{
//        //    printf(" ");
//        //}
//        if (memMap[pntr].isSet)
//        {
//            #ifdef DEBUG
//                printf("<--------Completed\r\n\r");
//            #endif
//        }
//        if (memMap[pntr].clock >= EXTMEMTIMEOUT)
//        {
//            printf("<--XXX---Timedout\r\n\r");
//            return EXT_MEM_TIMEOUT_ERROR;
//        }
//        return 0;
//    }
//    int CallbackExtMemCreateReq(ParameterList_t *TempParam)
//    {
//        int  ret_val = 0;
//        int i;
//        uint32_t _intid,_extid;
//
//        #ifdef DEBUG
//           printf("--//internal//-- Into CallbackExtMemCreateReq.\r\n\r");
//        #endif
//        AddToTransmit("<EXTMEMORY>\r\n\r");
//        /* First check to see if the parameters required for the execution of*/
//        /* this function appear to be semi-valid.                            */
//        if ((TempParam) && (TempParam->NumberofParameters > 1))
//        {
//            for (i=1;i<TempParam->NumberofParameters;i+=2)
//            {
//                if (!strcmp(TempParam->Params[i-1].strParam,"intmemid"))
//                {
//                    _intid = (unsigned int)(TempParam->Params[i].intParam);
//                }
//                if (!strcmp(TempParam->Params[i-1].strParam,"extmemid"))
//                {
//                    _extid = (unsigned int)(TempParam->Params[i].intParam);
//                }
//            }
//            for (i=0;i<memMapCnt;i++)
//                if (memMap[i]._intid == _intid)
//                {
//                    AddToTransmit("<DATA_TRANSLATED>\r\n\r");
//                    #ifdef DEBUG
//                        printf("--//internal//-- Externally translated %d.\r\n\r",_extid);
//                    #endif
//                    memMap[i]._extid = _extid;
//                    memMap[i].isSet = 1;
//                    if (_extid == 0)
//                    {
//                        printf("--//internal//-- Buffer depleted.\r\n\r");
//                        return EXT_MEM_FUNCTION_BUFFERSIZE_ERROR;
//                    }
//                    return 0;
//                }
//            return EXT_MEM_NO_FUNCTION_ERROR;
//        }
//        else
//        {
//            /* One or more of the necessary parameters are invalid.           */
//            ret_val = INVALID_PARAMETERS_ERROR;
//            AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
//            #ifdef DEBUG
//               printf("--//internal//--  Invalid parameters.\r\n\r");
//            #endif
//        }
//        AddToTransmit("</EXTMEMORY>\r\n\r");
//
//        return(ret_val);
//    }
//    int DeleteExtMemReq(uint32_t _intid)
//    {
//        int i,j,rc;
//
//        #ifdef DEBUG
//           printf("--//internal//-- Into DeleteExtMemReq.\r\n\r");
//        #endif
//        for (i=0;i<memMapCnt;i++)
//            if (memMap[i]._intid == _intid)
//            {
//                //ToDo: Meake query
//                pktlen = sizeof(buf);
//                opt_path.num = COAP_OPTION_URI_PATH;
//                opt_path.buf.p = (uint8_t*)path_mem;
//                opt_path.buf.len = strlen(path_mem);
//                sprintf((char *)path_arg_buf,"extmemid=%d",(int)memMap[i]._extid);
//                opt_args.num = COAP_OPTION_URI_QUERY;
//                opt_args.buf.p = (uint8_t*)path_arg_buf;
//                opt_args.buf.len = strlen(path_arg_buf);
//                coap_make_msg(&scratch_buf, &pkt, &opt_path, &opt_args, 0,
//                                   0, 0, 
//                                   0, id_out++, 0, 
//                                   COAP_METHOD_DELETE, 
//                                   COAP_CONTENTTYPE_NONE);
//                if (!(rc = coap_build(buf, &pktlen, &pkt, NULL)))
//                  Transfer((uint8_t*)buf,pktlen,path_mem);
//                #ifdef DEBUG
//                    printf("---------------> CoAP packet start.\r\n\r");
//                    coap_dumpPacket(&pkt);
//                    printf("---------------> CoAP packet end.\r\n\r");
//                #endif
//                for (j=i+1;j<memMapCnt;j++)
//                    memMap[j-1] = memMap[j];
//                memMapCnt--;
//                return 0;
//            }
//        return EXT_MEM_NO_FUNCTION_ERROR;
//    }
//    int ResetExtMemReq()
//    {
//        int rc;
//        #ifdef DEBUG
//           printf("--//internal//-- Into DeleteExtMemReq.\r\n\r");
//        #endif
//        //ToDo: Make query
//        pktlen = sizeof(buf);
//        opt_path.num = COAP_OPTION_URI_PATH;
//        opt_path.buf.p = (uint8_t*)path_mem;
//        opt_path.buf.len = strlen(path_mem);
//        coap_make_msg(&scratch_buf, &pkt, &opt_path, 0, 0,
//                           0, 0, 
//                           0, id_out++, 0, 
//                           COAP_METHOD_RESET, 
//                           COAP_CONTENTTYPE_NONE);
//        if (!(rc = coap_build(buf, &pktlen, &pkt, NULL)))
//          Transfer((uint8_t*)buf,pktlen,path_mem);
//        #ifdef DEBUG
//            printf("---------------> CoAP packet start.\r\n\r");
//            coap_dumpPacket(&pkt);
//            printf("---------------> CoAP packet end.\r\n\r");
//        #endif
//        return 0;
//    }
//    int GetExtMemReq(uint8_t *data, uint32_t *datalen, uint32_t _intid)
//    {
//        int i,rc;
//        #ifdef DEBUG
//           printf("--//internal//-- Into GetExtMemReq.\r\n\r");
//        #endif
//        for (i=0;i<memMapCnt;i++)
//            if (memMap[i]._intid == _intid)
//            {
//                //ToDo: Meake query
//                pktlen = sizeof(buf);
//                opt_path.num = COAP_OPTION_URI_PATH;
//                opt_path.buf.p = (uint8_t*)path_mem;
//                opt_path.buf.len = strlen(path_mem);
//                sprintf((char *)path_arg_buf,"extmemid=%d",(int)memMap[i]._extid);
//                opt_args.num = COAP_OPTION_URI_QUERY;
//                opt_args.buf.p = (uint8_t*)path_arg_buf;
//                opt_args.buf.len = strlen(path_arg_buf);
//                //printf("prp msg\r\n\r");
//                coap_make_msg(&scratch_buf, &pkt, &opt_path, &opt_args, 0,
//                                   0, 0, 
//                                   0, id_out++, 0, 
//                                   COAP_METHOD_GET, 
//                                   COAP_CONTENTTYPE_NONE);
//                if (!(rc = coap_build(buf, &pktlen, &pkt, path_mem_clb_ret)))
//                  Transfer((uint8_t*)buf,pktlen,path_mem);
//                #ifdef DEBUG
//                    printf("---------------> CoAP packet start.\r\n\r");
//                    coap_dumpPacket(&pkt);
//                    printf("---------------> CoAP packet end.\r\n\r");
//                #endif
//                memMap[i].clock = 0;
//                memMap[i].isSet = 0;
//                while ((!memMap[i].isSet) && (memMap[i].clock < EXTMEMTIMEOUT))
//                {
//                    printf(" ");
//                }
//                if (memMap[i].isSet)
//                {
//                    printf("<--------Completed\r\n\r");
//                }
//                if (memMap[i].clock >= EXTMEMTIMEOUT)
//                {
//                    printf("<--XXX---Timedout\r\n\r");
//                    return EXT_MEM_TIMEOUT_ERROR;
//                }
//                memcpy(data,(uint8_t *)memMapBuffer,memMapBufferCnt);
//                *datalen = memMapBufferCnt;
//                return 0;
//            }
//        return EXT_MEM_NO_FUNCTION_ERROR;
//    }
//    int CallbackExtMemGetReq(ParameterList_t *TempParam)
//    {
//        int  ret_val = 0;
//        int i;
//        uint32_t _extid;
////        uint32_t _intid;
//
//        #ifdef DEBUG
//           printf("--//internal//-- Into CallbackExtMemGetReq.\r\n\r");
//        #endif
//        AddToTransmit("<EXTMEMORY>\r\n\r");
//        /* First check to see if the parameters required for the execution of*/
//        /* this function appear to be semi-valid.                            */
//        if ((TempParam) && (TempParam->NumberofParameters > 1))
//        {
//            for (i=1;i<TempParam->NumberofParameters;i+=2)
//            {
////                if (!strcmp(TempParam->Params[i-1].strParam,"intmemid"))
////                {
////                    _intid = (unsigned int)(TempParam->Params[i].intParam);
////                }
//                if (!strcmp(TempParam->Params[i-1].strParam,"extmemid"))
//                {
//                    _extid = (unsigned int)(TempParam->Params[i].intParam);
//                }
//            }
//            for (i=0;i<memMapCnt;i++)
//                if (memMap[i]._extid == _extid)
//                {
//                    AddToTransmit("<DATA_TRANSLATED/>\r\n\r");
//                    #ifdef DEBUG
//                       printf("--//internal//-- EXT data translated, extid=%d.\r\n\r"
//                                                                       ,_extid);
//                    #endif
//                    if (scratch_buf.len > EXTMEMBUFFER)
//                        return EXT_MEM_FUNCTION_BUFFERSIZE_ERROR;
//                    memcpy((uint8_t *)memMapBuffer,scratch_buf.p,
//                            memMapBufferCnt = scratch_buf.len);
//                    memMap[i].isSet = 1;
//                    return 0;
//                }
//            return EXT_MEM_NO_FUNCTION_ERROR;
//        }
//        else
//        {
//            /* One or more of the necessary parameters are invalid.           */
//            ret_val = INVALID_PARAMETERS_ERROR;
//            AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
//            #ifdef DEBUG
//               printf("--//internal//--  Invalid parameters.\r\n\r");
//            #endif
//        }
//        AddToTransmit("</EXTMEMORY>\r\n\r");
//
//        return(ret_val);
//    }
//    uint32_t GetMemExtByInt(uint32_t _intid)
//    {
//        int i;
//        for (i=0;i<memMapCnt;i++)
//            if (memMap[i]._intid == _intid)
//                return memMap[i]._extid;
//        return 0;
//    }
#endif
void ExtMemClock(void)
{
    int i;
    for (i=0;i<memMapCnt;i++)
        memMap[i].clock += 1;
    return;
}
void FreeCycle(void)
{
  free_cycles++;
  return;
}
uint32_t GetCycle(void)
{
  return last_free_cycles;
}
uint32_t GetMaxCycle(void)
{
  return max_free_cycles;
}
uint32_t GetPercent(void)
{
  return (last_free_cycles*100)/(abs(max_free_cycles)+1);
}
uint32_t GetClock(void)
{
  return now_clock;
}
void SetClock(int _clock)
{
  now_clock = _clock;
  return;
}
void ClockHandler(void)
{
  now_clock++;
  last_free_cycles = free_cycles;
  if (last_free_cycles > max_free_cycles)
    max_free_cycles = last_free_cycles;
  free_cycles = 0;
  ExtMemClock();
  return;
}
/*============================================================================*/