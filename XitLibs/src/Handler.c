#include "Handler.h"
#include "LogModule.h"
    
#define HANDLER_BUFFER_LENGTH   4096
#define CIRCULAR_BUFFER_LENGTH  48

coap_packet_t inpkt;
coap_packet_t outpkt;
uint8_t scratch_b[HANDLER_BUFFER_LENGTH];
uint8_t message_b[HANDLER_BUFFER_LENGTH];
coap_rw_buffer_t scratch = {scratch_b, sizeof (scratch_b)};
coap_rw_buffer_t message = {message_b, sizeof (message_b)};

CircularBufferItem_t file[CIRCULAR_BUFFER_LENGTH];
    
void InitHandler(const uint32_t sample_frequency, const uint32_t sample_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    InitCommands();
    InitStreamRecorder(file, CIRCULAR_BUFFER_LENGTH, sample_frequency, sample_size);

    AddCommand(
            Method_GET | Method_PUT | Method_POST | Method_RESET,
            global_link_memory[0],
            global_link_memory[1],
            &MemoryCommand);
    AddCommand(
            Method_GET | Method_RESET,
            global_link_streamer[0][0],
            global_link_streamer[0][1],
            &StreamRecorderCommand);
    AddCommand(
            Method_GET,
            global_link_streamer[1][0],
            global_link_streamer[1][1],
            &StreamRecorderCurrentCommand);
    AddCommand(
            Method_GET,
            global_link_streamer[2][0],
            global_link_streamer[2][1],
            &StreamRecorderLastCommand);
    AddCommand(
            Method_GET,
            global_link_wellknown[0],
            global_link_wellknown[1],
            &WellKnownCommand);
}

coap_rw_buffer_t *UserHandler(const uint8_t *buf, size_t buflen, char *ip, uint32_t port)
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
    switch (current_coap_mediatype)
    {
        case Media_TEXT:
            media_option = COAP_CONTENTTYPE_TEXT_PLAIN;
            break;
        case Media_BYTE:
            media_option = COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;
            break;
        case Media_XML:
            media_option = COAP_CONTENTTYPE_APPLICATION_XML;
            break;
        case Media_JSON:
            media_option = COAP_CONTENTTYPE_APPLICATION_JSON;
            break;
        case Media_LINK:
            media_option = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
            break;
        default:
            media_option = COAP_CONTENTTYPE_APPLICATION_XML;
            break;
    }
    DBG_LOG_TRACE("coap_handle_req return code rc == %d\n",rc);
    if (rc == 0)
    {
        DBG_LOG_TRACE("header rc == %d\n",inpkt.hdr.code);
        if ((inpkt.hdr.code == COAP_METHOD_GET))
        {
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