
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Handler.h"
#include "LogModule.h"

#define TXTIMEOUT 10
#define PORT_BACK 5683

/* Private variables ---------------------------------------------------------*/
uint8_t inb, rc, cmdlen = 0;
uint8_t id_out = 0;
uint8_t scratch_raw[4096];
coap_rw_buffer_t scratch_buf = {scratch_raw, sizeof (scratch_raw)};
coap_packet_t pkt;
size_t rsplen;
size_t pktlen;
coap_packet_t rsppkt;
coap_option_t opt;
coap_option_t opt_path;
coap_option_t opt_args;
coap_option_t opt_part;
int size_parts = 1024;
int size_parts_cur = 1024;
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
int Transfer(const uint8_t *data, const uint32_t datalen, const char *_func) {
    //    transfer_time = 0;
    //    while ((!transfer_free) && (transfer_time < TXTIMEOUT));
    //    if (transfer_time >= TXTIMEOUT)
    //        return -1;
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
        return TransferUDP(data, datalen, address, port);
    #else
        transfer_free = 0;
        return TransferDMA(data, datalen);
    #endif
    return -2;
}

int TransferBand(const uint8_t *data, const uint32_t datalen) {
    transfer_time = 0;
    //    while ((!transfer_free) && (transfer_time < TXTIMEOUT));
    //    if (transfer_time >= TXTIMEOUT)
    //        return -1;
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
    DBG_LOG_INFO("Memory used by CoAP: %d Bytes\n",MEMORY_COAP);
    DBG_LOG_INFO("Memory used by CommandModule: %d Bytes\n",MEMORY_COMMAND);
    DBG_LOG_INFO("Memory used by ConfigModule: %d Bytes\n",MEMORY_CONFIG);
    DBG_LOG_INFO("Memory used by DMAModule: %d Bytes\n",MEMORY_DMA);
    DBG_LOG_INFO("Memory used by DiscoveryModule: %d Bytes\n",MEMORY_CORE_WELLKNOWN);
    DBG_LOG_INFO("Memory used by InOutBuffer: %d Bytes\n",MEMORY_INOUT);
    DBG_LOG_INFO("Memory used by StreamDataRecorder: %d Bytes\n",MEMORY_STREAM);
    DBG_LOG_INFO("========ALL=========================%d=Bytes====\n"
                    ,MEMORY_COAP+MEMORY_COMMAND+MEMORY_CONFIG+MEMORY_DMA+
                    MEMORY_CORE_WELLKNOWN+MEMORY_INOUT+MEMORY_STREAM);
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
        open_device("/dev/video0");
        init_device();
        start_capturing();
        return;
    }

    void VideoFrameDeInitHandler(void) {
        stop_capturing();
        uninit_device();
        close_device();
        return;
    }
#endif

int old_s[4];
union {
        struct { uint8_t s_b1,s_b2,s_b3,s_b4; } S_un_b;
        uint32_t S_addr;
} translate;

inline void ProtocolHandler(void) {
    char ip[16];
    uint32_t cmdlent = 0;
    uint32_t port = 0;
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
                DBG_LOG_INFO("Bad packet(%d) ", rc);
                DBG_LOG_DEBUG("Received %s: ", ip);
                #ifdef DEBUG
                    coap_dump(scratch_raw, cmdlent, true);
                #endif
            } 
            else 
            {
                #ifdef DEBUG
                    coap_dumpHeader(&pkt.hdr);
                    coap_dumpOptions(&pkt.opts, pkt.numopts);
                #endif
                content_type = COAP_CONTENTTYPE_APPLICATION_XML;
                coap_handle_req(&scratch_buf, &pkt, &rsppkt,
                        CommandLineInterpreter,ip);
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
                            (uint8_t*) tbuffer, size_parts_cur,
                            pkt.hdr.id[0], pkt.hdr.id[1],
                            pkt.tok_p,pkt.tok_len, COAP_RSPCODE_CONTENT,
                            content_type);
                        opt_part.num = 0;
                    }
                } else {
                    return;
                }
                if (0 != (rc = coap_build(scratch_raw, &rsplen, &rsppkt, NULL, NULL))) {
                    printf("coap_build failed rc=%d\r\n\r", rc);
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
//    DBG_LOG_TRACE("Into OperationHandler");

    #ifdef PLATFORM_LINUX
        //VideoFrameHandler();
    #endif

//    #ifndef CPU    
//    if ((ReadMem(REG_EEG_PocketSize) <= l) && (ReadMem(REG_EEG_Auto_Band) > 0)) {
//        l = GetDataReadyCnt(ReadMem(REG_EEG_PocketSize), (int*) scratch_raw);
//        if (l > 0) {
//            if ((k = Packetize((uint8_t*) scratch_raw, l * 4, 
//                BUFFER_SAMPLE_SIZE * ReadMem(REG_EEG_PocketSize) + 22)) > 0) {
//                TransferBand((uint8_t*) scratch_raw, k);
//            }
//        }
//    }
//    #else
//    #endif
//
    if (ReadMem(REG_UPD_File) > 0) 
    {
        DBG_LOG_DEBUG("Update");
        WriteMem(REG_UPD_File, 0);
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
    AddToPocketReceive(let);
    return;
}

void UartTransferCompleteHandler(void) {
    SetCStatLedsUnderPWM(0, 0, 0);
    transfer_free = 1;
    return;
}

void UartReceiveCompleteHandler(void) {
    char *pstr;
    unsigned char pstrs = 0;
    pstr = (char*) GetPocketBuffer(&pstrs);
    AddToReceive(pstr, pstrs, 0, 0);
    SetCStatLedsUnderPWM(0, 0, 0);
    return;
}


/* Adders --------------------------------------------------------------------*/
void SecClockHandler(void) {
    AddToSchedule(SecClockSheduler);
    return;
}

void SoftPWMHandler(void) {
//    AddToSchedule(SoftPWMSheduler);
    IncPWM();
    SetLedsUnderPWM();
    return;
}

void StatChangeHandler(void) {
//    AddToSchedule(StatChangeSheduler);
    ChangeLedsCode();
    return;
}

void CalculationHandler(void) {
    FreeCycle();
    return;
}
void SampleHandler(void) {
    AddToSchedule(SampleSheduler);
    return;
}
/*============================================================================*/

/* Handlers ------------------------------------------------------------------*/
void SampleSheduler(void) {
//    DBG_LOG_INFO("Scheduled SampleHandler.\n");
    AddSample();
    return;
}

void SecClockSheduler(void) {
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