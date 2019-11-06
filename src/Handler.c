#include "Handler.h"

coap_packet_t inpkt;
coap_packet_t outpkt;
uint8_t scratch_b[HANDLER_BUFFER_LENGTH];
uint8_t message_b[HANDLER_BUFFER_LENGTH];
coap_rw_buffer_t scratch = {scratch_b, sizeof (scratch_b)};
coap_rw_buffer_t message = {message_b, sizeof (message_b)};
coap_observer_buffer_t observer_message = {message_b, sizeof (message_b), 0, 0};

CircularBufferItem_t file[CIRCULAR_BUFFER_LENGTH];

extern int StreamGetObserverData(uint8_t *data, uint32_t *data_size, 
                                    uint32_t buffer_size, uint32_t iter_s);
extern uint32_t StreamGetObserverIp();
extern uint32_t StreamGetObserverPort();
extern coap_packet_t* StreamGetObserverPacket();
    
void timer1sHandler(CSMACDController_t *controller)
{
    csma_clock_cycle(controller);
}
    
void timerSampleFreqHandler(void)
{
    AddSample();
}

void InitHandler(const uint32_t sample_frequency, const uint32_t sample_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    InitCfgMem();
    InitBuffer();
    InitCommands();
#ifndef SMALL
    InitStreamRecorder(
            file, CIRCULAR_BUFFER_LENGTH, 
            sample_frequency, sample_size,
            1
    );
#endif

    AddCommand(
            Method_GET | Method_PUT | Method_POST | Method_RESET,
            global_link_memory[0],
            global_link_memory[1],
            &MemoryCommand
    );
#ifndef SMALL
    AddCommand(
            Method_GET | Method_RESET,
            global_link_streamer[0][0],
            global_link_streamer[0][1],
            &StreamRecorderCommand
    );
    AddCommand(
            Method_GET,
            global_link_streamer[1][0],
            global_link_streamer[1][1],
            &StreamRecorderCurrentCommand
    );
    AddCommand(
            Method_GET,
            global_link_streamer[2][0],
            global_link_streamer[2][1],
            &StreamRecorderLastCommand
    );
#endif
    AddCommand(
            Method_GET,
            global_link_wellknown[0],
            global_link_wellknown[1],
            &WellKnownCommand
    );
    AddCommand(
            Method_GET,
            global_link_device[0],
            global_link_device[1],
            &DeviceCommand
    );
    AddCommand(
            Method_GET,
            global_link_version[0],
            global_link_version[1],
            &VersionCommand
    );
}

uint8_t GetCoapFromMediaType()
{
    switch (current_coap_mediatype)
    {
        case Media_TEXT:
            return COAP_CONTENTTYPE_TEXT_PLAIN;
        case Media_BYTE:
            return COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;
        case Media_XML:
            return COAP_CONTENTTYPE_APPLICATION_XML;
        case Media_JSON:
            return COAP_CONTENTTYPE_APPLICATION_JSON;
        case Media_LINK:
            return COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
        default:
            return COAP_CONTENTTYPE_APPLICATION_XML;
    }
}

coap_rw_buffer_t *MessageHandlerIntIP( const uint8_t *buf, size_t buflen, 
                                                uint32_t ipi, uint32_t port)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int rc,i;
    char ip[16];
    conv_uint32_bytes_t ip_d;
    ip_d.ui32 = ipi;
    snprintf(ip, 16, "%u.%u.%u.%u", (unsigned int)ip_d.ui8[0], (unsigned int)ip_d.ui8[1], (unsigned int)ip_d.ui8[2], (unsigned int)ip_d.ui8[3]);
    uint8_t media_option = COAP_CONTENTTYPE_APPLICATION_XML;
    memset((void *) &inpkt, 0, sizeof (coap_packet_t));
    /*==1= Parse package =================================================*/
    rc = coap_parse(
            &inpkt,
            (uint8_t *) buf,
            buflen);
    /*==2= Handle request ================================================*/
    if (rc == 0)
        rc = coap_handle_req(&scratch, &inpkt, &outpkt, 0, ip, port);
    /*==3= Build response content ========================================*/
    media_option = GetCoapFromMediaType();
    DBG_LOG_TRACE("coap_handle_req return code rc == %d\n",rc);
    if (rc == 0)
    {
        DBG_LOG_TRACE("header rc == %d\n",inpkt.hdr.code);
        if ((inpkt.hdr.code == COAP_METHOD_GET))
        {
			DBG_LOG_TRACE("COAP_RSPCODE_CONTENT\n");
			coap_make_response(
						&scratch,
						&outpkt,
						0,
						(uint8_t*) scratch.p,
						scratch.len,
						inpkt.hdr.id[0],
						inpkt.hdr.id[1],
						inpkt.tok_p,
						inpkt.tok_len,
						COAP_RSPCODE_CONTENT,
						media_option);
        }
        else
        {
			DBG_LOG_TRACE("COAP_RSPCODE_CHANGED\n");
            coap_make_response(
                    &scratch,
                    &outpkt,
                    0,
                    (uint8_t*) scratch.p,
                    scratch.len,
                    inpkt.hdr.id[0],
                    inpkt.hdr.id[1],
                    inpkt.tok_p,
                    inpkt.tok_len,
                    COAP_RSPCODE_CHANGED,
                    media_option);
        }
    }
    else
    {
        scratch.len = HANDLER_BUFFER_LENGTH;
        switch (rc)
        {
            case INVALID_PARAMETERS_ERROR:
                DBG_LOG_TRACE("Answer INVALID_PARAMETERS_ERROR\n");
                coap_make_response(
                        &scratch,
                        &outpkt,
                        0,
                        NULL,
                        0,
                        inpkt.hdr.id[0],
                        inpkt.hdr.id[1],
                        inpkt.tok_p,
                        inpkt.tok_len,
                        COAP_RSPCODE_BAD_REQUEST,
                        media_option);
                break;
            case NO_COMMAND_ERROR:
                DBG_LOG_TRACE("Answer NO_COMMAND_ERROR\n");
                coap_make_response(
                        &scratch,
                        &outpkt,
                        0,
                        NULL,
                        0,
                        inpkt.hdr.id[0],
                        inpkt.hdr.id[1],
                        inpkt.tok_p,
                        inpkt.tok_len,
                        COAP_RSPCODE_NOT_FOUND,
                        media_option);
                break;
            default:
                DBG_LOG_TRACE("Answer default\n");
                coap_make_response(
                        &scratch,
                        &outpkt,
                        0,
                        NULL,
                        0,
                        inpkt.hdr.id[0],
                        inpkt.hdr.id[1],
                        inpkt.tok_p,
                        inpkt.tok_len,
                        COAP_RSPCODE_BAD_REQUEST,
                        media_option);
                break;
        }
    }
    /*==4= Build response package ========================================*/
    DBG_LOG_TRACE("Build response package (size:%d)\n",outpkt.payload.len);
    message.len = HANDLER_BUFFER_LENGTH;
    rc = coap_build(message.p, &message.len, &outpkt, NULL, NULL);
    /*==5= Transmitt package =============================================*/
    if (rc == 0)
    {
        return &message;
    }
    return (NULL);
}

coap_rw_buffer_t *MessageHandlerTextIP( const uint8_t *buf, size_t buflen, 
                                                char *ip, uint32_t port)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int rc;
    uint8_t media_option = COAP_CONTENTTYPE_APPLICATION_XML;
    memset((void *) &inpkt, 0, sizeof (coap_packet_t));
    /*==1= Parse package =================================================*/
    rc = coap_parse(
            &inpkt,
            (uint8_t *) buf,
            buflen);
    /*==2= Handle request ================================================*/
    if (rc == 0)
        rc = coap_handle_req(&scratch, &inpkt, &outpkt, 0, ip, port);
    /*==3= Build response content ========================================*/
    media_option = GetCoapFromMediaType();
    DBG_LOG_TRACE("coap_handle_req return code rc == %d\n",rc);
    if (rc == 0)
    {
        DBG_LOG_TRACE("header2 rc == %d\n",inpkt.hdr.code);
        if ((inpkt.hdr.code == COAP_METHOD_GET))
        {
			DBG_LOG_TRACE("COAP_RSPCODE_CONTENT\n");
            coap_make_response(
                    &scratch,
                    &outpkt,
                    0,
                    (uint8_t*) scratch.p,
                    scratch.len,
                    inpkt.hdr.id[0],
                    inpkt.hdr.id[1],
                    inpkt.tok_p,
                    inpkt.tok_len,
                    COAP_RSPCODE_CONTENT,
                    media_option);
        }
        else
        {
			DBG_LOG_TRACE("COAP_RSPCODE_CHANGED\n");
            coap_make_response(
                    &scratch,
                    &outpkt,
                    0,
                    (uint8_t*) scratch.p,
                    scratch.len,
                    inpkt.hdr.id[0],
                    inpkt.hdr.id[1],
                    inpkt.tok_p,
                    inpkt.tok_len,
                    COAP_RSPCODE_CHANGED,
                    media_option);
        }
    }
    else
    {
        scratch.len = HANDLER_BUFFER_LENGTH;
        switch (rc)
        {
            case INVALID_PARAMETERS_ERROR:
                DBG_LOG_TRACE("Answer INVALID_PARAMETERS_ERROR\n");
                coap_make_response(
                        &scratch,
                        &outpkt,
                        0,
                        NULL,
                        0,
                        inpkt.hdr.id[0],
                        inpkt.hdr.id[1],
                        inpkt.tok_p,
                        inpkt.tok_len,
                        COAP_RSPCODE_BAD_REQUEST,
                        media_option);
                break;
            case NO_COMMAND_ERROR:
                DBG_LOG_TRACE("Answer NO_COMMAND_ERROR\n");
                coap_make_response(
                        &scratch,
                        &outpkt,
                        0,
                        NULL,
                        0,
                        inpkt.hdr.id[0],
                        inpkt.hdr.id[1],
                        inpkt.tok_p,
                        inpkt.tok_len,
                        COAP_RSPCODE_NOT_FOUND,
                        media_option);
                break;
            default:
                DBG_LOG_TRACE("Answer default\n");
                coap_make_response(
                        &scratch,
                        &outpkt,
                        0,
                        NULL,
                        0,
                        inpkt.hdr.id[0],
                        inpkt.hdr.id[1],
                        inpkt.tok_p,
                        inpkt.tok_len,
                        COAP_RSPCODE_BAD_REQUEST,
                        media_option);
                break;
        }
    }
    /*==4= Build response package ========================================*/
    DBG_LOG_TRACE("Build response package (size:%d)\n", outpkt.payload.len);
    message.len = HANDLER_BUFFER_LENGTH;
    rc = coap_build(message.p, &message.len, &outpkt, NULL, NULL);
    /*==5= Transmitt package =============================================*/
    if (rc == 0)
    {
        return &message;
    }
    return (NULL);
}

coap_observer_buffer_t *StreamObserverHandler()
{
    int rc;
	static uint16_t nn;
	uint8_t n_b[2];
	coap_option_t opt_part;
    if (!IsObserved()){
        return 0;
    }
    if ((uint32_t)GetStreamDataReadyCnt() >= ReadMem(REG_EEG_PocketSize))
	{
		nn++;
		opt_part.num = COAP_OPTION_BLOCK2;
		n_b[1] = nn & 0xFF;
		n_b[0] = (nn >> 8) & 0xFF;
		opt_part.buf.p = n_b;
		opt_part.buf.len = 2;
        DBG_LOG_TRACE(
                "GetStreamDataReadyCnt (%d >= %d)\n",
                GetStreamDataReadyCnt(),
                ReadMem(REG_EEG_PocketSize)
        );
        int i = StreamGetObserverData(
                scratch.p, 
                (uint32_t *)&scratch.len, 
                HANDLER_BUFFER_LENGTH, 
                ReadMem(REG_EEG_PocketSize)
        );
        if (i >= 0) {
            uint8_t media_option = GetCoapFromMediaType();
            coap_make_response(
                    &scratch,
                    &outpkt,
                    &opt_part,
                    (uint8_t*) scratch.p,
                    scratch.len,
                    StreamGetObserverPacket()->hdr.id[0],
                    StreamGetObserverPacket()->hdr.id[1],
                    StreamGetObserverPacket()->tok_p,
                    StreamGetObserverPacket()->tok_len,
                    COAP_RSPCODE_CHANGED,
                    media_option
            );
            DBG_LOG_TRACE(
                    "Build observer package (size:%d)\n",
                    outpkt.payload.len
            );
            observer_message.len = HANDLER_BUFFER_LENGTH;
            rc = coap_build(
                    observer_message.p, &observer_message.len, 
                    &outpkt, NULL, NULL
            );
            if (rc == 0)
            {
                observer_message.ip = StreamGetObserverIp();
                observer_message.port = StreamGetObserverPort();
                return &observer_message;
            }
        }
    }
    return 0;
}






















