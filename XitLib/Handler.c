// ----------------------------------------------------------------------------
//
// Handler.c - Main handlers and global functions
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Handler.h"
#include "LogModule.h"
#include "ExtFunctions.h"
#include "CRC16ANSI.h"
/*============================================================================*/

/* Private defines -----------------------------------------------------------*/
#define TXTIMEOUT 10
#define PORT_BACK 5683
/*============================================================================*/

extern coap_option_t opt_part;

/* Private function prototypes -----------------------------------------------*/
char *StringParser(char *String);
int CommandParser(UserCommand_t *TempCommand, char *Input);
int CommandInterpreter(UserCommand_t *TempCommand);
int Reset(ParameterList_t *TempParam);
int MEMRead(ParameterList_t *TempParam);
int MEMWrite(ParameterList_t *TempParam);
int DISTRead(ParameterList_t *TempParam);
int DISTWrite(ParameterList_t *TempParam);
int CLOCKSet(ParameterList_t *TempParam);
int CLOCKGet(ParameterList_t *TempParam);
int CALCFREECYCLESGet(ParameterList_t *TempParam);
int CALCMAXCYCLESGet(ParameterList_t *TempParam);
int CALCPERCENTCYCLESGet(ParameterList_t *TempParam);
int DEVICEGet(ParameterList_t *TempParam);
CommandFunction_t FindCommand(char *Command);
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint8_t inb, rc, cmdlen = 0;
uint8_t id_out = 0;
uint8_t scratch_raw[COAP_SIZE];
uint8_t bufsa[COAP_SIZE];
coap_rw_buffer_t scratch_buf = {scratch_raw, sizeof (scratch_raw)};
coap_packet_t pkt;
size_t rsplen;
size_t pktlen;
coap_packet_t rsppkt;
coap_option_t opt;
coap_option_t opt_path;
coap_option_t opt_args;
coap_option_t opt_part;
int size_parts = COAP_SIZE;
int size_parts_cur = COAP_SIZE;
uint32_t lenght = 0;
uint8_t transfer_free = 1;
uint32_t transfer_time = 0;
uint8_t content_type;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
const char *path_null = "";
const char *path_clock = "/clock";
const char *path_dist = "/distance";
/*============================================================================*/

/* Private function prototypes -----------------------------------------------*/
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void Interface_Memory(void)
{
    DBG_LOG_TRACE("Into Interface_Memory.\n");
    ClearCommands();
    ClearSchedule();
    AddCommand(global_link[0], global_link[2], MEMRead);
    AddCommand(global_link[1], global_link[2], MEMWrite);
    AddCommand("/DEVICE", "</device>", DEVICEGet);
    AddCommand("/RESET", "</reset>", Reset);
    AddCommand("/GET/LOG", "</log>", LOGRead);
    AddCommand("/GET/.WELL-KNOWN/CORE", "</.well-known/core>", WELLKnown);
    AddCommand("/CALLBACK/.WELL-KNOWN/CORE", "</.well-known/core>", 
                                                        CallbackWELLKnown);
    AddCommand("/PUT/CLOCK", "</clock>", CLOCKSet);
    AddCommand("/GET/CLOCK", "</clock>", CLOCKGet);
    AddCommand("/GET/CALCULATE/CYCLES/FREE", "</calculate/cycles/free>", 
                                                        CALCFREECYCLESGet);
    AddCommand("/GET/CALCULATE/CYCLES/MAX", "</calculate/cycles/max>", 
                                                        CALCMAXCYCLESGet);
    AddCommand("/GET/CALCULATE/CYCLES/PERCENT", "</calculate/cycles/percent>", 
                                                        CALCPERCENTCYCLESGet); 
    AddCommand("/GET/VERSION", "</version>", Version);
    if (signal_type == 2) 
    {
        AddCommand("/GET/MOVEMENT", "</movement>;if=\"accel\"", GetLastBlock);
    }
    else
    {
        AddCommand("/GET/EEG", "</eeg>;if=\"neuro\"", GetLastBlock); 
        AddCommand("/GET/EEG/RECORD", "</eeg/record>;if=\"neuro\"", GetRecord); 
        AddCommand("/GET/EEGCONCRETEBLOCK", "</eegconcreteblock>;if=\"neuro\"", 
                GetConcreteBlock);
    }
    #ifdef CPU
        AddCommand("/GET/SNAP/FILE", "</snap/take>;if=\"video\"", Snap);
        AddCommand("/GET/SNAP/TAKE", "</snap/file>;if=\"video\"", GetSnap);
        AddCommand("/GET/LIGHT", "</light>;if=\"lamp\"", Light);
        AddCommand("/GET/VIDEOTHREAD", "</videothread>;if=\"video\"", VIDEOThread);
        AddCommand("/GET/UPDATE", "</update>", Update);
        AddCommand("/GET/UPDATEHASH", "</updatehash>", UpdateHash);
        AddCommand("/CALLBACK/UPDATE", "</update>", CallbackUpdate);
        AddCommand("/CALLBACK/UPDATEHASH", "</updatehash>", CallbackUpdateHash);
        AddCommand("/REQUERY/UPDATE", "</update>", QueryUpdate);
        AddCommand("/GET/TECHUPDATE", "</techupdate>", TechUpdate); 
        AddCommand("/REQUERY/UPDATEHASH", "</updatehash>", QueryUpdateHash); 
        AddCommand("/GET/PARTHASH", "</parthash>", PartHash);
        AddCommand("/CALLBACK/PARTHASH", "</parthash>", CallbackPartHash);
    #endif

    #ifndef RTOS
    AddCommand("/GET/RUNGENERATOR", "</rungenerator>;if=\"generator\"", 
            RunGenerator);
    AddCommand("/GET/STOPGENERATOR", "</stopgenerator>;if=\"generator\"", 
            StopGenerator);
    AddCommand("/GET/QUERYNODES", "</querynodes>;if=\"dev_n\"", QueryNodes);
    #endif
   
    return;
}
int Reset(ParameterList_t *TempParam)
{
    int  ret_val = 0;

    DBG_LOG_DEBUG("Into Reset.\n");
    AddToTransmit("<RESET>\r\n\r");
    if ((TempParam))
    {
        #ifdef CPU
            exit(0);
        #else
            HAL_NVIC_SystemReset();
        #endif
    }
    else
    {
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</RESET>\r\n\r");
    return(ret_val);
}
int CLOCKSet(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  Clock = -1;
    int i;
    char buffer[STRING_SIZE];
    DBG_LOG_DEBUG("Into CLOCKSet.\n");
    AddToTransmit("<CLOCKSET>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            snprintf((char*)buffer,STRING_SIZE,"%s - %d\r\n\r",
                    TempParam->Params[i-1].strParam,
                    (unsigned int)(TempParam->Params[i].intParam));
            AddToTransmit((char*)buffer);
            if (!strcmp(TempParam->Params[i-1].strParam,"clock"))
            {
                 Clock = (unsigned int)(TempParam->Params[i].intParam);
            }
        }
        if (Clock >= 0)
        {
            SetClock(Clock);
            AddToTransmit(" <SET/>\r\n\r");
            DBG_LOG_WARNING("Invalid clock parameter.\n");
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</CLOCKSET>\r\n\r");
    return(ret_val);
}
int DEVICEGet(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    DBG_LOG_DEBUG("Into DEVICEGet.\n");
    AddToTransmit("<DEVICE>");
    if (DEVICE == EEG)
        AddToTransmit("EEG");
    else if (DEVICE == POLYGRAPH)
        AddToTransmit("POLYGRAPH");
    else if (DEVICE == ROBOT)
        AddToTransmit("ROBOT");
    AddToTransmit("</DEVICE>\r\n\r");
    return(ret_val);
}

   /* The following function is responsible for reading data that was   */
   /* stored in memory.  The function reads a fixed number of bytes.    */
   /* This function returns zero if successful                          */
   /* and a negative value if an error occurred.                        */
int DISTRead(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    char buffer[STRING_SIZE];

    DBG_LOG_DEBUG("Into DISTRead.\n");
    AddToTransmit("<DISTANCE>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        snprintf((char*)buffer,STRING_SIZE," %d\r\n\r",(int)ReadMem(REG_Distance));
        AddToTransmit((char*)buffer);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</DISTANCE>\r\n\r");

    return(ret_val);
}


   /* The following function is responsible for parsing user input      */
   /* and call appropriate command function.                            */
int CommandLineInterpreter(char *Command)
{
    int     		Result = !EXIT_CODE;
    uint8_t      	ret_val = 0;
    UserCommand_t 	TempCommand;
    char                buf_local[60];

    DBG_LOG_DEBUG("Into CommandLineInterpreter.\n");
    DBG_LOG_DEBUG("> %s\n",Command);
    /* The string input by the user contains a value, now run the string */
    /* through the Command Parser.                                       */
    if(CommandParser(&TempCommand, Command) >= 0)
    {
        /* The Command was successfully parsed run the Command.           */
        Result = CommandInterpreter(&TempCommand);
        switch(Result)
        {
            case INVALID_COMMAND_ERROR:
                DBG_LOG_WARNING("Invalid command.\n");
                ret_val = 0;
                break;
            case FUNCTION_ERROR:
                DBG_LOG_WARNING("Invalid function.\n");
                ret_val = 0;
                break;
            case EXIT_CODE:
                break;
            default:
                ret_val = 1;
                break;
        }
    }
    else
    {
        DBG_LOG_WARNING("INVALID_COMMAND_ERROR.\n");
    }

    DBG_LOG_DEBUG("Into END of CommandLineInterpreter.\n");
    return(ret_val);
}
int Transfer(const uint8_t *data, const uint32_t datalen, const char *_func) {
    //    transfer_time = 0;
    //    while ((!transfer_free) && (transfer_time < TXTIMEOUT));
    //    if (transfer_time >= TXTIMEOUT)
    //        return -1;
    DBG_LOG_TRACE("Into Transfer.\n");
    #ifdef CPU
        transfer_free = 1;
        if (data[0] == 0) {
            DBG_LOG_ERROR("Bad packet\n");
            #ifdef DEBUG
                coap_dumpHeader(&pkt.hdr);
                DBG_LOG_DEBUG("Received: ");
                coap_dump(data, datalen, true);
                exit(0);
            #endif
        }
        return TransferUDP(data, datalen,
                get_first_node_by_func(_func), PORT_BACK);
    #else
        transfer_free = 0;
        return TransferDMA(data, datalen);
    #endif
    return -2;
}
int TransferTo(const uint8_t *data, const uint32_t datalen,
        const char* address /* = "192.168.1.255" */,
        const uint32_t port /* = 5683 */) {
    //    transfer_time = 0;
    //    while ((!transfer_free) && (transfer_time < TXTIMEOUT));
    //    if (transfer_time >= TXTIMEOUT)
    //        return -1;
    DBG_LOG_TRACE("Into TransferTo.\n");
//        transfer_free = 1;
    if (data[0] == 0) {
        DBG_LOG_ERROR("Bad packet\n");
    }
    return TransferUDP(data, datalen, address, port);
}

int TransferBand(const uint8_t *data, const uint32_t datalen) {
    transfer_time = 0;
    //    while ((!transfer_free) && (transfer_time < TXTIMEOUT));
    //    if (transfer_time >= TXTIMEOUT)
    //        return -1;
    DBG_LOG_TRACE("Into TransferBand.\n");
    #ifdef CPU
        transfer_free = 1;
        if (data[0] == 0) {
            DBG_LOG_ERROR("Bad packet\n");
            #ifdef DEBUG
                coap_dumpHeader(&pkt.hdr);
                DBG_LOG_DEBUG("Received: ");
                coap_dump(data, datalen, true);
                exit(0);
            #endif
        }
        return TransferBroadbandUDP(data, datalen, PORT_BACK);
    #else
        transfer_free = 0;
        return TransferDMA(data, datalen);
    #endif
    return -2;
}

void InitHandler(DeviceTypeDef device) {
    ClearLog();
    DBG_LOG_TRACE("Into InitHandler.\n");
    DBG_LOG_INFO("Memory used by CoAP: %d Bytes\n",(int)MEMORY_COAP);
    DBG_LOG_INFO("Memory used by CommandModule: %d Bytes\n",(int)MEMORY_COMMAND);
    DBG_LOG_INFO("Memory used by ConfigModule: %d Bytes\n",(int)MEMORY_CONFIG);
    DBG_LOG_INFO("Memory used by DMAModule: %d Bytes\n",(int)MEMORY_DMA);
    DBG_LOG_INFO("Memory used by DiscoveryModule: %d Bytes\n",(int)MEMORY_CORE_WELLKNOWN);
    DBG_LOG_INFO("Memory used by InOutBuffer: %d Bytes\n",(int)MEMORY_INOUT);
    DBG_LOG_INFO("Memory used by StreamDataRecorder: %d Bytes\n",(int)MEMORY_STREAM);
    DBG_LOG_INFO("========ALL=========================%d=Bytes====\n"
                    ,(int)(MEMORY_COAP+MEMORY_COMMAND+MEMORY_CONFIG+MEMORY_DMA+
                    MEMORY_CORE_WELLKNOWN+MEMORY_INOUT+MEMORY_STREAM));
    transfer_free = 1;
    transfer_time = 0;
    coap_setup();
    InitCfgMem();
    InitCfgDevType();
    DEVICE = device;
    InitBuffer();
    ClearBuffer();
    Interface_Memory();
    rsplen = sizeof (scratch_raw);
    return;
}
#ifdef PLATFORM_LINUX
    void VideoFrameInitHandler(void) {
/*
        open_device("/dev/video0");
        init_device();
        start_capturing();
*/
        return;
    }

    void VideoFrameDeInitHandler(void) {
/*
        stop_capturing();
        uninit_device();
        close_device();
*/
        return;
    }
#endif

int old_s[4];
union {
        struct { uint8_t s_b1,s_b2,s_b3,s_b4; } S_un_b;
        uint32_t S_addr;
} translate;

typedef union { unsigned char bytes4[4];
                uint32_t ui32; } converter;
              
inline void ProtocolHandler(void) {
    char ip[16];
    uint8_t i;
    converter reader;
    uint32_t cmdlent = 0;
    uint32_t port = 0;
    //DBG_LOG_TRACE("Into ProtocolHandler.\n");
//    DBG_LOG_TRACE("Into ProtocolHandler");
    if (NO_BUFFER_ERROR == ProceedReceive((char*)scratch_raw, &cmdlent, 
                                          &(translate.S_addr), &port)) {
        snprintf(ip,sizeof(ip),"%d.%d.%d.%d",translate.S_un_b.s_b1
                                    ,translate.S_un_b.s_b2
                                    ,translate.S_un_b.s_b3
                                    ,translate.S_un_b.s_b4);
        DBG_LOG_DEBUG("%d.%d.%d.%d",translate.S_un_b.s_b1
                                    ,translate.S_un_b.s_b2
                                    ,translate.S_un_b.s_b3
                                    ,translate.S_un_b.s_b4);
        DBG_LOG_DEBUG("Start to parse message.");        
        DBG_LOG_INFO("Simple link(%d) ", ReadMem(REG_Simple_link)); 
        if (ReadMem(REG_Simple_link) > 0) {
            char* tbuffer2;
            CommandLineInterpreter((char*) &scratch_raw);
            if (0 != (tbuffer2 = ProceedTransmit(&lenght))) {
                Transfer((uint8_t*) tbuffer2, lenght, 0);
            }
            return;
        } 
        else 
        {
            if (0 != (rc = coap_parse(&pkt, scratch_raw, cmdlent))) 
            {
                if( (scratch_raw[0] == 0x50) 
                        && (scratch_raw[1] == 0x0A) 
                        && (scratch_raw[2] == 0x01) )
                {
                    for (i=0;i < 8;i++)
                    {
                        reader.bytes4[3] = 0x00;
                        reader.bytes4[2] = scratch_raw[3+(i*3)];
                        reader.bytes4[1] = scratch_raw[3+(i*3+1)];
                        reader.bytes4[0] = scratch_raw[3+(i*3+2)];
                        WriteMem(REG_IMG_1+i,reader.ui32);
                    }
                    TransferTo("image setted", 12, "0.0.0.0", 0);
                }
                else
                {
                    DBG_LOG_INFO("Bad packet(%d) ", rc);
                    DBG_LOG_DEBUG("Received %s: ", ip);
                    #ifdef DEBUG
                        coap_dump(scratch_raw, cmdlent, true);
                    #endif
                }
            } 
            else 
            {
                DBG_LOG_DEBUG("ProtocolHandler %d bytes hash %04X.\n",
                    pkt.payload.len,CRC16ANSI(pkt.payload.p,pkt.payload.len));
                #ifdef DEBUG
                    coap_dumpHeader(&pkt.hdr);
                    coap_dumpOptions(&pkt.opts, pkt.numopts);
                    coap_dump(scratch_raw, cmdlent, true);
                #endif
                content_type = COAP_CONTENTTYPE_APPLICATION_XML;
                DBG_LOG_DEBUG("ProtocolHandler2 %d bytes hash %04X.\n",
                    pkt.payload.len,CRC16ANSI(pkt.payload.p,pkt.payload.len));
                #ifdef DEBUG
                    DBG_LOG_DEBUG("coap_handle_req %s:%d \r\n\r",ip,port);
                #endif
                coap_handle_req(&scratch_buf, &pkt, &rsppkt,
                        CommandLineInterpreter,ip,port);
                size_t rsplen = sizeof (scratch_raw);

                uint32_t cmdlen;
                char* tbuffer;
                DBG_LOG_DEBUG("type of %d\r\n\r",content_type);
                if (NULL != (tbuffer = ProceedTransmit(&cmdlen))) {
                    tbuffer[cmdlen] = 0;
//                    #ifdef DEBUG
//                        DBG_LOG_INFO("%s length %d type of %d\r\n\r", 
//                                tbuffer, cmdlen, content_type);
//                    #endif
                    scratch_buf.len = 4096;
                    if (opt_part.num == 0)
                        coap_make_response(&scratch_buf, &rsppkt, 0,
                            (uint8_t*) tbuffer, cmdlen,
                            pkt.hdr.id[0], pkt.hdr.id[1],
                            pkt.tok_p,pkt.tok_len, COAP_RSPCODE_CONTENT,
                            content_type);
                    else
                    {
                        coap_make_response(&scratch_buf, &rsppkt, &opt_part,
                            (uint8_t*) bufsa, size_parts_cur,
                            pkt.hdr.id[0], pkt.hdr.id[1],
                            pkt.tok_p,pkt.tok_len, COAP_RSPCODE_CONTENT,
                            content_type);
                        opt_part.num = 0;
                    }
                } else {
                    return;
                }
                rsplen = sizeof (scratch_raw);
                if (0 != (rc = coap_build(scratch_raw, &rsplen, &rsppkt, NULL, NULL))) {
                    printf("coap_build failed rc=%d/%d\r\n\r", rc, rsplen);
                } else {
                    #ifdef DEBUG
                        DBG_LOG_DEBUG("Sending: ");
                        coap_dump(scratch_raw, rsplen, true);
                    #endif
                    #ifdef DEBUG
                        DBG_LOG_DEBUG("Sended to %s:%d \r\n\r",ip,port);
                    #endif
                    TransferTo(scratch_raw, rsplen, ip, port);
                }
            }
        }
        DBG_LOG_DEBUG("End.");
    }
//    DBG_LOG_TRACE("End ProtocolHandler");
    return;
}
inline void OperationHandler(void) {
    int i,j, k = 0, l = 0;
    l = GetCnt();
    char systemcmd[100];
    //DBG_LOG_TRACE("Into OperationHandler.\n");
//    DBG_LOG_TRACE("Into OperationHandler");

    #ifdef PLATFORM_LINUX
        //VideoFrameHandler();
    #endif

    #ifndef CPU    
    #else
    #endif

    if (ReadMem(REG_UPD_File) > 0) 
    {
        DBG_LOG_DEBUG("Update");
//        if (updateStatus == -1)
//        {
            WriteMem(REG_UPD_File, 0);
//            updateStatus=1;
//        }
        #ifdef CPU
            function_update(0);
        #endif
    }
    
//    DBG_LOG_TRACE("ExecuteSchedule");
    ExecuteSchedule();
//    DBG_LOG_TRACE("End OperationHandler");
    return;
}

#ifdef PLATFORM_LINUX
void VideoFrameHandler(void) {
    //mainloop();
    return;
}
#endif

void UartProtocolHandler(char let) {
    DBG_LOG_TRACE("Into UartProtocolHandler.\n");
    AddToPocketReceive(let);
    return;
}

void UartTransferCompleteHandler(void) {
    DBG_LOG_TRACE("Into UartTransferCompleteHandler.\n");
    SetCStatLedsUnderPWM(0, 0, 0);
    transfer_free = 1;
    return;
}

void UartReceiveCompleteHandler(void) {
    char *pstr;
    unsigned char pstrs = 0;
    DBG_LOG_TRACE("Into UartReceiveCompleteHandler.\n");
    pstr = (char*) GetPocketBuffer(&pstrs);
    AddToReceive(pstr, pstrs, 0, 0);
    SetCStatLedsUnderPWM(0, 0, 0);
    return;
}


/* Adders --------------------------------------------------------------------*/
void SecClockHandler(void) {
    DBG_LOG_TRACE("Into SecClockHandler.\n");
    AddToSchedule((ScheduleFunction_t)SecClockSheduler);
    return;
}

void SoftPWMHandler(void) {
//    AddToSchedule(SoftPWMSheduler);
    DBG_LOG_TRACE("Into SoftPWMHandler.\n");
    IncPWM();
    SetLedsUnderPWM();
    return;
}

void StatChangeHandler(void) {
//    AddToSchedule(StatChangeSheduler);
    DBG_LOG_TRACE("Into StatChangeHandler.\n");
    ChangeLedsCode();
    return;
}

void CalculationHandler(void) {
    //DBG_LOG_TRACE("Into CalculationHandler.\n");
    FreeCycle();
    return;
}
void SampleHandler(void) {
    DBG_LOG_TRACE("Into SampleHandler.\n");
    AddToSchedule((ScheduleFunction_t)SampleSheduler);
    return;
}
/*============================================================================*/

/* Handlers ------------------------------------------------------------------*/
void SampleSheduler(void) {
    DBG_LOG_TRACE("Into SampleSheduler.\n");
//    DBG_LOG_INFO("Scheduled SampleHandler.\n");
    AddSample();
    return;
}

void SecClockSheduler(void) {
    DBG_LOG_TRACE("Into SecClockSheduler.\n");
//    DBG_LOG_INFO("Scheduled SecClockHandler.\n");
    ClockHandler();
    #ifdef CPU
        coap_clock();
    #endif
    transfer_time++;
    WriteMem(REG_CLK_Band, 1);
    return;
}
/*============================================================================*/

int ResetReq() {
    int rc;
    DBG_LOG_DEBUG("Into ResetReq.\n");
    //ToDo: Make query
    pktlen = sizeof (scratch_raw);
    #ifdef CPU
        coap_make_msg(&scratch_buf, &pkt, 0, 0, 0,
                0, 0,
                0, id_out++, 0, 0,
                COAP_METHOD_RESET,
                COAP_CONTENTTYPE_NONE);
        if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, NULL, NULL)))
            TransferBand((uint8_t*) scratch_raw, pktlen);
    #endif
    return 0;
}
/*============================================================================*/