
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Handler.h"
#include "LogModule.h"

#define TXTIMEOUT 10
#define PORT_BACK 5683

/* Private variables ---------------------------------------------------------*/
uint8_t buffer[STRING_SIZE];
uint8_t buffer2[10];
uint8_t buffer3[40];
uint8_t tbuffer[STRING_SIZE];
uint8_t bufsa[1024];
uint8_t inb, rc, cmdlen = 0;
coap_packet_t pkt;
size_t rsplen;
size_t pktlen;
coap_packet_t rsppkt;
#ifndef MC
uint8_t buf[4096];
#endif
uint8_t scratch_raw[4096];
coap_rw_buffer_t scratch_buf = {scratch_raw, sizeof (scratch_raw)};
uint8_t id_out = 0;
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
    ClearBuffer();
    Interface_Memory();
    rsplen = sizeof (buf);
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

void SampleHandler(void) {
    AddSample();
}

inline void ProtocolHandler(void) {
#ifdef CPU
#else
    char buffer[STRING_SIZE];
    uint32_t cmdlent = 0;
    if (NO_BUFFER_ERROR == ProceedReceive((char*) tbuffer, &cmdlent)) {
        if (ReadMem(REG_Simple_link) > 0) {
            char* tbuffer2;
            CommandLineInterpreter((char*) &tbuffer);
            if (0 != (tbuffer2 = ProceedTransmit(&lenght))) {
                Transfer((uint8_t*) tbuffer2, lenght, 0);
            }
            return;
        }
    }
#endif
    return;
}
inline void OperationHandler(void) {
    int i,j, k = 0, l = 0;
    l = GetCnt();
    char systemcmd[100];

    #ifdef PLATFORM_LINUX
        //VideoFrameHandler();
    #endif

    #ifndef CPU    
    if ((ReadMem(REG_EEG_PocketSize) <= l) && (ReadMem(REG_EEG_Auto_Band) > 0)) {
        l = GetDataReadyCnt(ReadMem(REG_EEG_PocketSize), (int*) scratch_raw);
        if (l > 0) {
            if ((k = Packetize((uint8_t*) scratch_raw, l * 4, 
                BUFFER_SAMPLE_SIZE * ReadMem(REG_EEG_PocketSize) + 22)) > 0) {
                TransferBand((uint8_t*) scratch_raw, k);
            }
        }
    }
    #else
    #endif

    if (ReadMem(REG_UPD_File) > 0) 
    {
        WriteMem(REG_UPD_File, 0);
    #ifdef CPU
        function_update(0);
    #endif
    }
    return;
}

void CalculationHandler(void) {
    FreeCycle();
    return;
}

#ifdef PLATFORM_LINUX
void VideoFrameHandler(void) {
    //mainloop();
    return;
}
#endif

void UartDistanceHandler(void) {
    uint32_t dist;
    buffer2[4] = '\0';
    dist = StringToUnsignedInteger((char *) (buffer2 + 1));
    if (ReadMem(REG_Distance) != dist)
        WriteMem(REG_Distance_Band, 1);
    WriteMem(REG_Distance, dist);
    return;
}

void UartProtocolHandler(void) {
    AddToPocketReceive(buffer[0]);

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

#ifndef CPU
//    HAL_TIM_Base_Stop(&htim13);
#endif
    pstr = (char*) GetPocketBuffer(&pstrs);
    //    sprintf((char*)buffer,"len %d\r\n\r",pstrs);
    //    AddToTransmit((char*)buffer);
//      Transfer((uint8_t*)pstr,pstrs,0);
    AddToReceive(pstr, pstrs);
    SetCStatLedsUnderPWM(0, 0, 0);
    return;
}

void SecClockHandler(void) {
    ClockHandler();
#ifdef CPU
    coap_clock();
#endif
    transfer_time++;
    WriteMem(REG_CLK_Band, 1);
    return;
}

void SoftPWMHandler(void) {
    IncPWM();
    SetLedsUnderPWM();
    return;
}

void StatChangeHandler(void) {
    ChangeLedsCode();
    return;
}

int ResetReq() {
    int rc;
    DBG_LOG_DEBUG("Into ResetReq.\n");
    //ToDo: Make query
    pktlen = sizeof (buf);
#ifdef CPU
    coap_make_msg(&scratch_buf, &pkt, 0, 0, 0,
            0, 0,
            0, id_out++, 0, 0,
            COAP_METHOD_RESET,
            COAP_CONTENTTYPE_NONE);
    if (!(rc = coap_build(buf, &pktlen, &pkt, NULL, NULL)))
        TransferBand((uint8_t*) buf, pktlen);
#endif
    return 0;
}
/*============================================================================*/