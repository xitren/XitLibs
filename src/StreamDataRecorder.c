// ----------------------------------------------------------------------------
//
// StreamDataRecorder.c - Recorder to store and process stream data with speed
//                          more than 20 milliseconds.
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#include "DistCalc.h"
#include "LogModule.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"
#include "circularbuffer.h"
#include "ConfigMem.h"
#include "coap.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
const char* global_link_streamer[][2] = {
    {"/streamdatarecorder", "</streamdatarecorder>"},
    {"/streamdatarecorder/current", "</streamdatarecorder/current>"},
    {"/streamdatarecorder/last", "</streamdatarecorder/last>"}
};
CircularBuffer_t buffer_test;
uint32_t sample_size = 8;
coap_packet_t observe_pkt;
static uint32_t sample_frequency = 250;
static uint32_t signal_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {10,100,1000,10000,1000,100,10};
static uint32_t noise_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {100,100,100,100,100,100,100};
static uint32_t power_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {100,1000,10000,1000,1000,1000,1000};
static uint32_t signal_frequency[BUFFER_SAMPLE_SIZE-1] = {10,20,30,40,50,60,70};
static uint8_t signal_type = 0;    
static uint8_t observed = 0;
static uint8_t media_type = Media_FREE;
static uint32_t observer_ip;
static uint32_t observer_port;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
const double TwoPi = 6.283185307179586;
/*============================================================================*/

/* Private function prototypes -----------------------------------------------*/
int StreamRecorderCommand_GET(uint8_t MediaType, ParameterList_t *TempParam, 
                    uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int StreamRecorderCommand_RESET(uint8_t MediaType, ParameterList_t *TempParam, 
                    uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int StreamRecorderCurrentCommand_GET(uint8_t MediaType, ParameterList_t *TempParam, 
                    uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int StreamRecorderLastCommand_GET(uint8_t MediaType, ParameterList_t *TempParam, 
                    uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int IsObserved(void){
    return observed;
}

void InitStreamRecorder(CircularBufferItem_t* _storage, uint32_t _storage_size, 
        uint32_t _sample_frequency, uint32_t _sample_size, uint32_t _signal_type)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    sample_frequency = _sample_frequency;
    sample_size = _sample_size;
    signal_type = _signal_type;
    circularbuffer_new(
            &buffer_test,
            _storage,
            _storage_size
    );
}

void AddSample(void)
{
//    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
//                      __LINE__, __FILE__, __func__);
    int i;
    uint32_t Data_sample[MAX_SAMPLE_SIZE];
    if (signal_type == 1)
    {
        for(i=0;i<BUFFER_SAMPLE_SIZE;i++)
        {
            uint32_t selAD = (ReadMem(REG_ADC_ORDER) >> (i*4)) & 0x0000000F;
            if (selAD < 8) {
//                DBG_LOG_TRACE("i = %d: %d \n",i,ReadMem(REG_ADC_CH1+selAD));
                Data_sample[i] = ReadMem(REG_ADC_CH1+selAD);
            }
            else if (selAD < 11)
            {
//                DBG_LOG_TRACE("i = %d: %d \n",i,ReadMem(REG_ADC_CHA+selAD));
                selAD -= 8;
                Data_sample[i] = ReadMem(REG_ADC_CHA+selAD);
            }
            else
                Data_sample[i] = 0;
        }
    }
    else if (signal_type == 2)
        for(i=0;i < 4;i++)
            Data_sample[i] = (int32_t)ReadMem(REG_ACCEL_X+i);
    else if (signal_type == 3)
    {}
    else
    {
        double phase = (TwoPi*circularbuffer_get_first_index(&buffer_test)) 
                                                            / sample_frequency;
        Data_sample[0] = ReadMem(REG_ADC_CHA);
        WriteMem(REG_ADC_CHA,ReadMem(REG_ADC_CHA)+1);
        Data_sample[1] = ReadMem(REG_ADC_CHB);
        for(i=2;i<BUFFER_SAMPLE_SIZE;i++)
            Data_sample[i] = ((int32_t)
                                    (signal_amplitude[i-1]*
                                         sin(signal_frequency[i-1]*phase)) +
                                    (int32_t)
                                    (power_amplitude[i-1]*sin(0.5*phase)) +
                                    (int32_t)
                                    ((rand()*noise_amplitude[i-1])/RAND_MAX) );
    }
    circularbuffer_push(&buffer_test,(void *)Data_sample);
    return;
}

int GetStreamDataReadyCnt(void)
{
    return circularbuffer_unreaded_items_size(&buffer_test);
}

void ClearStreamRecorder(void)
{
    circularbuffer_remove_all(&buffer_test);
}

uint32_t StreamGetObserverIp(){
    return observer_ip;
}

uint32_t StreamGetObserverPort(){
    return observer_port;
}

coap_packet_t* StreamGetObserverPacket(){
    return &observe_pkt;
}

int StreamGetObserverData(uint8_t *data, uint32_t *data_size, 
                                uint32_t buffer_size, uint32_t iter_s)
{
    ParameterList_t TempParam;
    TempParam.NumberofParameters = 0;
    if (observed < 1)
        return -1;
    size_t last = circularbuffer_get_last_index(&buffer_test);
    add_parameter(&TempParam,"from",last);
    add_parameter(&TempParam,"to",last + iter_s);
    StreamRecorderCommand_GET(media_type,&TempParam,data,data_size,buffer_size);
    increment_last_index(&buffer_test,iter_s);
    return 0;
}

inline int StreamRecorderCommand_GET(uint8_t MediaType, ParameterList_t *TempParam, 
                    uint8_t *data, uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int ret_val_f = 0;
    int ret_val_t = 0;
    uint32_t From = -1;
    uint32_t To = -1;
    int Observer = -1;
    size_t last;
    size_t first;
    uint8_t *data_st = data;
    uint32_t data_size_st = 0;
    uint32_t l = 0,i,k;
    uint32_t Data_sample[MAX_SAMPLE_SIZE];
    DBG_LOG_DEBUG("buffer_size %u.\n", buffer_size)
    if ((TempParam))
    {
        if (MediaType == Media_FREE)
            MediaType = Media_BYTE;
        ret_val_f = get_parameter(TempParam,"observe",(uint32_t*)&Observer);
        if ( (ret_val_f >= 0) )
        {
            DBG_LOG_DEBUG("Found observer property.\n")
            ret_val_f = get_parameter(TempParam,"ip",(uint32_t*)&From);
            ret_val_t = get_parameter(TempParam,"port",(uint32_t*)&To);
            observed = Observer;
            media_type = MediaType;
            if ( (Observer >= 0) && (ret_val_f >= 0) && (ret_val_t >= 0) ) 
            {
                memcpy(&observe_pkt, current_packet, sizeof(coap_packet_t));
                observer_ip = From;
                observer_port = To;
            }
        }
        ret_val_f = get_parameter(TempParam,"from",(uint32_t*)&From);
        ret_val_t = get_parameter(TempParam,"to",(uint32_t*)&To);
        if ( (ret_val_f >= 0) && (ret_val_t >= 0) ) 
        {
			DBG_LOG_DEBUG("buffer_size2 %s %u.\n", data_st, *data_size);
            last = circularbuffer_get_last_index(&buffer_test);
            first = circularbuffer_get_first_index(&buffer_test);
            DBG_LOG_TRACE("(last %d <=> first %d) \n",last,first);
            if ( (last <= From) && (To <= first) && (From <= To) )
                switch (MediaType)
                {
                    case Media_JSON:
                        current_coap_mediatype = Media_JSON;
                        data_size_st = snprintf(
                                (char*)data, buffer_size,
                                "{\n \"DATABLOCK\": [\n"
                        );
                        data += data_size_st;
                        buffer_size -= data_size_st;
                        l = circularbuffer_unreaded_items_size(&buffer_test);
                        DBG_LOG_TRACE("(circularbuffer_unreaded_items_size %d) \n",l);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last;i < first;i++)
                            {
                                circularbuffer_get_at(
                                        &buffer_test, i, (void*)Data_sample
                                );
                                if(i != last)
                                {
                                    data_size_st = snprintf(
                                            (char*)data, buffer_size,
                                            ",\n"
                                    );
                                    data += data_size_st;
                                    buffer_size -= data_size_st;
                                }
                                DBG_LOG_TRACE("sample %d \n",i);
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        "  {\"sample\": %lu, \"data\": [",
										(long unsigned int)i
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                                for (k=0;k < (sample_size-1);k++)
                                {
                                    DBG_LOG_TRACE("%d \n",Data_sample[k]);
                                    data_size_st = snprintf(
                                            (char*)data, buffer_size,
                                            "%lu, ", 
										(long unsigned int)Data_sample[k]
                                    );
                                    data += data_size_st;
                                    buffer_size -= data_size_st;
                                }
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        "%lu]}", 
										(long unsigned int)Data_sample[k]
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                            }
                        }
                        data_size_st = snprintf(
                                (char*)data, buffer_size,
                                "\n ]\n}\n"
                        );
                        data += data_size_st;
                        buffer_size -= data_size_st;
                        break;
                    case Media_XML:
                        current_coap_mediatype = Media_XML;
                        data_size_st = snprintf(
                                (char*)data, buffer_size,
                                "<DATABLOCK>"
                        );
                        data += data_size_st;
                        buffer_size -= data_size_st;
                        l = circularbuffer_unreaded_items_size(&buffer_test);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last;i < first;i++)
                            {
                                circularbuffer_get_at(
                                        &buffer_test, i, 
                                        (void*)Data_sample
                                );
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        "<SAMPLE ID=\"%lu\"",
										(long unsigned int)i
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                                for (k=0;k < (sample_size);k++)
                                {
                                    data_size_st = snprintf(
                                            (char*)data, buffer_size,
                                            " ch%lu=\"%lu\"", 
											(long unsigned int)k, 
											(long unsigned int)Data_sample[k]
                                    );
                                    data += data_size_st;
                                    buffer_size -= data_size_st;
                                }
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        ">"
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                            }
                        }
                        else
                        {
                            data_size_st = snprintf(
                                    (char*)data, buffer_size,
                                    "<NO_DATA>"
                            );
                            data += data_size_st;
                            buffer_size -= data_size_st;
                        }
                        data_size_st = snprintf(
                                (char*)data, buffer_size,
                                "</DATABLOCK>"
                        );
                        data += data_size_st;
                        buffer_size -= data_size_st;
                        break;
                    case Media_TEXT:
                        current_coap_mediatype = Media_TEXT;
                        l = circularbuffer_unreaded_items_size(&buffer_test);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last;i < first;i++)
                            {
                                circularbuffer_get_at(
                                        &buffer_test, i, (void*)Data_sample
                                );
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        "%lu",
										(long unsigned int)i
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                                for (k=0;k < (sample_size);k++)
                                {
                                    data_size_st = snprintf(
                                            (char*)data, buffer_size,
                                            " %lu", 
											(long unsigned int)Data_sample[k]
                                    );
                                    data += data_size_st;
                                    buffer_size -= data_size_st;
                                }
                            }
                        }
                        break;
                    case Media_BYTE:
                        current_coap_mediatype = Media_BYTE;
                        l = circularbuffer_unreaded_items_size(&buffer_test);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last; (i < first) 
                                    && (buffer_size > ((sample_size+1)*sizeof(uint32_t)) );i++)
                            {
                                memcpy(
                                        (void*)data,
                                        (void*)&i,
                                        sizeof(uint32_t)
                                );
                                data += sizeof(uint32_t);
                                buffer_size -= sizeof(uint32_t);
                                circularbuffer_get_at(
                                        &buffer_test, i, (void*)Data_sample
                                );
                                memcpy(
                                        (void*)data,
                                        (void*)Data_sample,
                                        sample_size*sizeof(uint32_t)
                                );
                                data += sample_size*sizeof(uint32_t);
                                buffer_size -= sample_size*sizeof(uint32_t);
                            }
                        }
                        break;
                    default:
						DBG_LOG_TRACE("MEDIA_FORMAT_NOT_ALLOWED %d \n", MediaType);
                        current_coap_mediatype = Media_XML;
                        (*data_size) = snprintf(
                                (char*)data, buffer_size,
                                "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
                        );
                        break;
                }
            else
            {
                current_coap_mediatype = Media_XML;
						DBG_LOG_TRACE("MEDIA_FORMAT_NOT_ALLOWED \n");
                ret_val = INVALID_PARAMETERS_ERROR;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "<INVALID_PARAMETERS_ERROR/>\r\n\r"
                );
            }
        }
        else
		{
            switch (MediaType)
            {
                case Media_JSON:
                    current_coap_mediatype = Media_JSON;
                    data_size_st = snprintf(
                            (char*)data, buffer_size,
                            "{\n \"DATABLOCK\": [\n"
                    );
                    data += data_size_st;
                    buffer_size -= data_size_st;
                    l = circularbuffer_unreaded_items_size(&buffer_test);
                    DBG_LOG_TRACE("circularbuffer_unreaded_items_size %d \n",l);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer_test);
                        first = circularbuffer_get_first_index(&buffer_test);
                        for (i=last;i < first;i++)
                        {
                            circularbuffer_get_at(
                                    &buffer_test, i, (void*)Data_sample
                            );
                            if(i != last)
                            {
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        ",\n"
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                            }
                            data_size_st = snprintf(
                                    (char*)data, buffer_size,
                                    "  {\"sample\": %lu, \"data\": [",
									(long unsigned int)i
                            );
//                            DBG_LOG_TRACE("2sample %d \n",i);
                            data += data_size_st;
                            buffer_size -= data_size_st;
                            for (k=0;k < (sample_size-1);k++)
                            {
//                                DBG_LOG_TRACE("%d \n",Data_sample[k]);
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        "%lu, ", 
										(long unsigned int)Data_sample[k]
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                            }
                            data_size_st = snprintf(
                                    (char*)data, buffer_size,
                                    "%lu]}", 
									(long unsigned int)Data_sample[k]
                            );
                            data += data_size_st;
                            buffer_size -= data_size_st;
                        }
                    }
                    data_size_st = snprintf(
                            (char*)data, buffer_size,
                            "\n ]\n}\n"
                    );
                    data += data_size_st;
                    buffer_size -= data_size_st;
                    circularbuffer_unreaded_items_nullify(&buffer_test);
                    break;
                case Media_XML:
                    current_coap_mediatype = Media_XML;
                    data_size_st = snprintf(
                            (char*)data, buffer_size,
                            "<DATABLOCK>"
                    );
                    data += data_size_st;
                    buffer_size -= data_size_st;
                    l = circularbuffer_unreaded_items_size(&buffer_test);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer_test);
                        first = circularbuffer_get_first_index(&buffer_test);
                        for (i=last;i < first;i++)
                        {
                            circularbuffer_get_at(
                                    &buffer_test, i, (void*)Data_sample
                            );
                            data_size_st = snprintf(
                                    (char*)data, buffer_size,
                                    "<SAMPLE ID=\"%lu\"",
									(long unsigned int)i
                            );
                            data += data_size_st;
                            buffer_size -= data_size_st;
                            for (k=0;k < (sample_size);k++)
                            {
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        " ch%lu=\"%lu\"", 
										(long unsigned int)k, 
										(long unsigned int)Data_sample[k]
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                            }
                            data_size_st = snprintf(
                                    (char*)data, buffer_size,
                                    ">"
                            );
                            data += data_size_st;
                            buffer_size -= data_size_st;
                        }
                    }
                    else
                    {
                        data_size_st = snprintf(
                                (char*)data, buffer_size,
                                "<NO_DATA>"
                        );
                        data += data_size_st;
                        buffer_size -= data_size_st;
                    }
                    data_size_st = snprintf(
                            (char*)data, buffer_size,
                            "</DATABLOCK>"
                    );
                    data += data_size_st;
                    buffer_size -= data_size_st;
                    circularbuffer_unreaded_items_nullify(&buffer_test);
                    break;
                case Media_TEXT:
                    current_coap_mediatype = Media_TEXT;
                    l = circularbuffer_unreaded_items_size(&buffer_test);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer_test);
                        first = circularbuffer_get_first_index(&buffer_test);
                        for (i=last;i < first;i++)
                        {
                            circularbuffer_get_at(
                                    &buffer_test, i, (void*)Data_sample
                            );
                            data_size_st = snprintf(
                                    (char*)data, buffer_size,
                                    "%lu",
									(long unsigned int)i
                            );
                            data += data_size_st;
                            buffer_size -= data_size_st;
                            for (k=0;k < (sample_size);k++)
                            {
                                data_size_st = snprintf(
                                        (char*)data, buffer_size,
                                        " %lu", 
										(long unsigned int)Data_sample[k]
                                );
                                data += data_size_st;
                                buffer_size -= data_size_st;
                            }
                        }
                    }
                    circularbuffer_unreaded_items_nullify(&buffer_test);
                    break;
                case Media_BYTE:
			DBG_LOG_DEBUG("buffer_size3 %s %u.\n", data_st, *data_size);
                    current_coap_mediatype = Media_BYTE;
                    l = circularbuffer_unreaded_items_size(&buffer_test);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer_test);
                        first = circularbuffer_get_first_index(&buffer_test);
                        for (i=last; (i < first) 
                                    && (buffer_size > ((sample_size+1)*sizeof(uint32_t)) );i++)
                        {
                            memcpy(
                                    (void*)data,
                                    (void*)&i,
                                    sizeof(uint32_t)
                            );
                            data += sizeof(uint32_t);
                            buffer_size -= sample_size*sizeof(uint32_t);
                            circularbuffer_get_at(
                                    &buffer_test, i, (void*)Data_sample
                            );
                            memcpy(
                                    (void*)data,
                                    (void*)Data_sample,
                                    sample_size*sizeof(uint32_t)
                            );
                            data += sample_size*sizeof(uint32_t);
                            buffer_size -= sample_size*sizeof(uint32_t);
                        }
                    }
                    circularbuffer_unreaded_items_nullify(&buffer_test);
                    break;
                default:
					DBG_LOG_TRACE("r MEDIA_FORMAT_NOT_ALLOWED %d \n", MediaType);
                    current_coap_mediatype = Media_XML;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
                    );
                    break;
            }
		}
        (*data_size) = data - data_st;
    }
    else
    {
		DBG_LOG_TRACE("INVALID_PARAMETERS_ERROR \n");
        current_coap_mediatype = Media_XML;
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, buffer_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }
    DBG_LOG_DEBUG("buffer_size %s %u.\n", data_st, *data_size)
    return(ret_val);
}
inline int StreamRecorderCommand_RESET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    ClearStreamRecorder();
    return(ret_val);
}
int StreamRecorderCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = StreamRecorderCommand_GET(
                    MediaType,TempParam,data,data_size,buffer_size
            );
            break;
        case Method_RESET:
            ret_val = StreamRecorderCommand_RESET(
                    MediaType,TempParam,data,data_size,buffer_size
            );
            break;
        default:
            current_coap_mediatype = Media_XML;
            ret_val = INVALID_PARAMETERS_ERROR;
            (*data_size) = snprintf(
                    (char*)data, *data_size,
                    "<INVALID_PARAMETERS_ERROR/>\r\n\r"
            );
            break;
    }
    return(ret_val);
}

inline int StreamRecorderCurrentCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    
    if ((TempParam) && (TempParam->NumberofParameters > 0))
    {
        if (ret_val >= 0)
        {
            if (MediaType == Media_FREE)
                MediaType = Media_XML;
            switch (MediaType) 
            {
                case Media_XML:
                    current_coap_mediatype = Media_XML;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "<CURRENTRECORDER>%d</CURRENTRECORDER>",
                            circularbuffer_get_first_index(&buffer_test)
                    );
                    break;
                case Media_TEXT:
                    current_coap_mediatype = Media_TEXT;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "%d", circularbuffer_get_first_index(&buffer_test)
                    );
                    break;
                case Media_BYTE:
                    current_coap_mediatype = Media_BYTE;
                    Value = circularbuffer_get_first_index(&buffer_test);
                    memcpy((void*)data,(void*)&Value,4);
                    (*data_size) = 4;
                    break;
                default:
                    current_coap_mediatype = Media_XML;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
                    );
                    break;
            }
        }
    }
    else
    {
        current_coap_mediatype = Media_XML;
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, buffer_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }
    return(ret_val);
}
inline int StreamRecorderLastCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    
    if ((TempParam) && (TempParam->NumberofParameters > 0))
    {
        if (ret_val >= 0)
        {
            if (MediaType == Media_FREE)
                MediaType = Media_XML;
            switch (MediaType) 
            {
                case Media_XML:
                    current_coap_mediatype = Media_XML;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "<LASTRECORDER>%d</LASTRECORDER>",
                            circularbuffer_get_first_index(&buffer_test)
                    );
                    break;
                case Media_TEXT:
                    current_coap_mediatype = Media_TEXT;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "%d", circularbuffer_get_first_index(&buffer_test)
                    );
                    break;
                case Media_BYTE:
                    current_coap_mediatype = Media_BYTE;
                    Value = circularbuffer_get_last_index(&buffer_test);
                    memcpy((void*)data,(void*)&Value,4);
                    (*data_size) = 4;
                    break;
                default:
                    current_coap_mediatype = Media_XML;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
                    );
                    break;
            }
        }
    }
    else
    {
        current_coap_mediatype = Media_XML;
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, buffer_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }
    return(ret_val);
}
int StreamRecorderCurrentCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = StreamRecorderCurrentCommand_GET(
                    MediaType,TempParam,data,data_size,buffer_size
            );
            break;
        default:
            current_coap_mediatype = Media_XML;
            ret_val = INVALID_PARAMETERS_ERROR;
            (*data_size) = snprintf(
                    (char*)data, buffer_size,
                    "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
            );
            break;
    }
    return(ret_val);
}
int StreamRecorderLastCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = StreamRecorderLastCommand_GET(
                    MediaType,TempParam,data,data_size,buffer_size
            );
            break;
        default:
            current_coap_mediatype = Media_XML;
            ret_val = INVALID_PARAMETERS_ERROR;
            (*data_size) = snprintf(
                    (char*)data, buffer_size,
                    "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
            );
            break;
    }
    return(ret_val);
}
/*============================================================================*/





