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
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
const char* global_link_streamer[][2] = {
    {"/STREAMDATARECORDER", "</streamdatarecorder>"},
    {"/STREAMDATARECORDER/CURRENT", "</streamdatarecorder/current>"},
    {"/STREAMDATARECORDER/LAST", "</streamdatarecorder/last>"}
};
CircularBuffer_t buffer;
static uint32_t sample_frequency = 250;
uint32_t sample_size = 8;
static uint32_t signal_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {10,100,1000,10000,1000,100,10};
static uint32_t noise_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {100,100,100,100,100,100,100};
static uint32_t power_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {100,1000,10000,1000,1000,1000,1000};
static uint32_t signal_frequency[BUFFER_SAMPLE_SIZE-1] = {10,20,30,40,50,60,70};
static uint8_t signal_type = 0;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
const double TwoPi = 6.283185307179586;
/*============================================================================*/

/* Private function prototypes -----------------------------------------------*/
int StreamRecorderCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int StreamRecorderCommand_RESET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int StreamRecorderCurrentCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int StreamRecorderLastCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void InitStreamRecorder(uint8_t* _storage, uint32_t _storage_size, 
        uint32_t _sample_frequency, uint32_t _sample_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    sample_frequency = _sample_frequency;
    sample_size = _sample_size;
    circularbuffer_new(
            &buffer,
            sample_size * sizeof(uint32_t),
            _storage,
            _storage_size
    );
}
void AddSample(void)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int i;
    uint32_t Data_sample[MAX_SAMPLE_SIZE];
    if (signal_type == 1)
    {
        for(i=0;i<BUFFER_SAMPLE_SIZE;i++)
        {
            uint32_t selAD = (ReadMem(REG_ADC_ORDER) >> (i*4)) & 0x0000000F;
            if (selAD < 8) 
                Data_sample[i] = ReadMem(REG_ADC_CH1+selAD);
            else if (selAD < 11)
            {
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
        double phase = (TwoPi*circularbuffer_get_first_index(&buffer)) 
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
    circularbuffer_push(&buffer,(void *)Data_sample);
    return;
}
void ClearStreamRecorder(void)
{
    circularbuffer_remove_all(&buffer);
}
inline int StreamRecorderCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int ret_val_f = 0;
    int ret_val_t = 0;
    int From = -1;
    int To = -1;
    size_t last;
    size_t first;
    uint8_t *data_st = data;
    uint32_t data_size_st = 0;
    uint32_t l = 0,i,k;
    uint32_t Data_sample[MAX_SAMPLE_SIZE];
    enum cc_stat ret;
    if ((TempParam))
    {
        ret_val_f = get_parameter(TempParam,"from",(uint32_t*)&From);
        ret_val_t = get_parameter(TempParam,"to",(uint32_t*)&To);
        if ( (ret_val_f >= 0) && (ret_val_t >= 0) ) 
        {
            last = circularbuffer_get_last_index(&buffer);
            first = circularbuffer_get_first_index(&buffer);
            if ( (last <= From) && (To <= first) && (From <= To) )
                switch (MediaType)
                {
                    case Media_JSON:
                        data_size_st = snprintf(
                                (char*)data, *data_size,
                                "{\n \"DATABLOCK\": [\n"
                        );
                        data += data_size_st;
                        *data_size -= data_size_st;
                        l = circularbuffer_unreaded_items_size(&buffer);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last;i < first;i++)
                            {
                                circularbuffer_get_at(
                                        &buffer, i, (void*)Data_sample
                                );
                                if(i != last)
                                {
                                    data_size_st = snprintf(
                                            (char*)data, *data_size,
                                            ",\n"
                                    );
                                    data += data_size_st;
                                    *data_size -= data_size_st;
                                }
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        "  {\"sample\": %d, \"data\": [",i
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                                for (k=0;k < (sample_size-1);k++)
                                {
                                    data_size_st = snprintf(
                                            (char*)data, *data_size,
                                            "%d, ", Data_sample[k]
                                    );
                                    data += data_size_st;
                                    *data_size -= data_size_st;
                                }
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        "%d]}", Data_sample[k]
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                            }
                        }
                        data_size_st = snprintf(
                                (char*)data, *data_size,
                                "\n ]\n}\n"
                        );
                        data += data_size_st;
                        *data_size -= data_size_st;
                        break;
                    case Media_XML:
                        data_size_st = snprintf(
                                (char*)data, *data_size,
                                "<DATABLOCK>"
                        );
                        data += data_size_st;
                        *data_size -= data_size_st;
                        l = circularbuffer_unreaded_items_size(&buffer);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last;i < first;i++)
                            {
                                circularbuffer_get_at(
                                        &buffer, i, 
                                        (void*)Data_sample
                                );
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        "<SAMPLE ID=\"%d\"",i
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                                for (k=0;k < (sample_size);k++)
                                {
                                    data_size_st = snprintf(
                                            (char*)data, *data_size,
                                            " ch%d=\"%d\"", k, Data_sample[k]
                                    );
                                    data += data_size_st;
                                    *data_size -= data_size_st;
                                }
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        ">"
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                            }
                        }
                        else
                        {
                            data_size_st = snprintf(
                                    (char*)data, *data_size,
                                    "<NO_DATA>"
                            );
                            data += data_size_st;
                            *data_size -= data_size_st;
                        }
                        data_size_st = snprintf(
                                (char*)data, *data_size,
                                "</DATABLOCK>"
                        );
                        data += data_size_st;
                        *data_size -= data_size_st;
                        break;
                    case Media_TEXT:
                        l = circularbuffer_unreaded_items_size(&buffer);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last;i < first;i++)
                            {
                                circularbuffer_get_at(
                                        &buffer, i, (void*)Data_sample
                                );
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        "%d",i
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                                for (k=0;k < (sample_size);k++)
                                {
                                    data_size_st = snprintf(
                                            (char*)data, *data_size,
                                            " %d", Data_sample[k]
                                    );
                                    data += data_size_st;
                                    *data_size -= data_size_st;
                                }
                            }
                        }
                        break;
                    case Media_BYTE:
                        l = circularbuffer_unreaded_items_size(&buffer);
                        if (l > 0)
                        {
                            last = From;
                            first = To;
                            for (i=last; (i < first) 
                                    && ((*data_size) > ((sample_size+1)*sizeof(uint32_t)) );i++)
                            {
                                memcpy(
                                        (void*)data,
                                        (void*)&i,
                                        sizeof(uint32_t)
                                );
                                data += sizeof(uint32_t);
                                *data_size -= sizeof(uint32_t);
                                circularbuffer_get_at(
                                        &buffer, i, (void*)Data_sample
                                );
                                memcpy(
                                        (void*)data,
                                        (void*)Data_sample,
                                        sample_size*sizeof(uint32_t)
                                );
                                data += sample_size*sizeof(uint32_t);
                                *data_size -= sample_size*sizeof(uint32_t);
                            }
                        }
                        break;
                    default:
                        break;
                }
            else
                return INVALID_PARAMETERS_ERROR;
        }
        else
            switch (MediaType)
            {
                case Media_JSON:
                    data_size_st = snprintf(
                            (char*)data, *data_size,
                            "{\n \"DATABLOCK\": [\n"
                    );
                    data += data_size_st;
                    *data_size -= data_size_st;
                    l = circularbuffer_unreaded_items_size(&buffer);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer);
                        first = circularbuffer_get_first_index(&buffer);
                        for (i=last;i < first;i++)
                        {
                            circularbuffer_get_at(
                                    &buffer, i, (void*)Data_sample
                            );
                            if(i != last)
                            {
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        ",\n"
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                            }
                            data_size_st = snprintf(
                                    (char*)data, *data_size,
                                    "  {\"sample\": %d, \"data\": [",i
                            );
                            data += data_size_st;
                            *data_size -= data_size_st;
                            for (k=0;k < (sample_size-1);k++)
                            {
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        "%d, ", Data_sample[k]
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                            }
                            data_size_st = snprintf(
                                    (char*)data, *data_size,
                                    "%d]}", Data_sample[k]
                            );
                            data += data_size_st;
                            *data_size -= data_size_st;
                        }
                    }
                    data_size_st = snprintf(
                            (char*)data, *data_size,
                            "\n ]\n}\n"
                    );
                    data += data_size_st;
                    *data_size -= data_size_st;
                    break;
                case Media_XML:
                    data_size_st = snprintf(
                            (char*)data, *data_size,
                            "<DATABLOCK>"
                    );
                    data += data_size_st;
                    *data_size -= data_size_st;
                    l = circularbuffer_unreaded_items_size(&buffer);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer);
                        first = circularbuffer_get_first_index(&buffer);
                        for (i=last;i < first;i++)
                        {
                            circularbuffer_get_at(
                                    &buffer, i, (void*)Data_sample
                            );
                            data_size_st = snprintf(
                                    (char*)data, *data_size,
                                    "<SAMPLE ID=\"%d\"",i
                            );
                            data += data_size_st;
                            *data_size -= data_size_st;
                            for (k=0;k < (sample_size);k++)
                            {
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        " ch%d=\"%d\"", k, Data_sample[k]
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                            }
                            data_size_st = snprintf(
                                    (char*)data, *data_size,
                                    ">"
                            );
                            data += data_size_st;
                            *data_size -= data_size_st;
                        }
                    }
                    else
                    {
                        data_size_st = snprintf(
                                (char*)data, *data_size,
                                "<NO_DATA>"
                        );
                        data += data_size_st;
                        *data_size -= data_size_st;
                    }
                    data_size_st = snprintf(
                            (char*)data, *data_size,
                            "</DATABLOCK>"
                    );
                    data += data_size_st;
                    *data_size -= data_size_st;
                    break;
                case Media_TEXT:
                    l = circularbuffer_unreaded_items_size(&buffer);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer);
                        first = circularbuffer_get_first_index(&buffer);
                        for (i=last;i < first;i++)
                        {
                            circularbuffer_get_at(
                                    &buffer, i, (void*)Data_sample
                            );
                            data_size_st = snprintf(
                                    (char*)data, *data_size,
                                    "%d",i
                            );
                            data += data_size_st;
                            *data_size -= data_size_st;
                            for (k=0;k < (sample_size);k++)
                            {
                                data_size_st = snprintf(
                                        (char*)data, *data_size,
                                        " %d", Data_sample[k]
                                );
                                data += data_size_st;
                                *data_size -= data_size_st;
                            }
                        }
                    }
                    break;
                case Media_BYTE:
                    l = circularbuffer_unreaded_items_size(&buffer);
                    if (l > 0)
                    {
                        last = circularbuffer_get_last_index(&buffer);
                        first = circularbuffer_get_first_index(&buffer);
                        for (i=last; (i < first) 
                                    && ((*data_size) > ((sample_size+1)*sizeof(uint32_t)) );i++)
                        {
                            memcpy(
                                    (void*)data,
                                    (void*)&i,
                                    sizeof(uint32_t)
                            );
                            data += sizeof(uint32_t);
                            *data_size -= sample_size*sizeof(uint32_t);
                            circularbuffer_get_at(
                                    &buffer, i, (void*)Data_sample
                            );
                            memcpy(
                                    (void*)data,
                                    (void*)Data_sample,
                                    sample_size*sizeof(uint32_t)
                            );
                            data += sample_size*sizeof(uint32_t);
                            *data_size -= sample_size*sizeof(uint32_t);
                        }
                    }
                    break;
                default:
                    break;
            }
        (*data_size) = data - data_st;
    }
    else
    {
        switch (MediaType) 
        {
            case Media_XML:
                ret_val = INVALID_PARAMETERS_ERROR;
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "<INVALID_PARAMETERS_ERROR/>\r\n\r"
                );
                break;
            default:
                break;
        }
    }
    return(ret_val);
}
inline int StreamRecorderCommand_RESET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    ClearStreamRecorder();
    return(ret_val);
}
int StreamRecorderCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = StreamRecorderCommand_GET(
                    MediaType,TempParam,data,data_size
            );
            break;
        case Method_RESET:
            ret_val = StreamRecorderCommand_RESET(
                    MediaType,TempParam,data,data_size
            );
            break;
        default:
            ret_val = INVALID_PARAMETERS_ERROR;
            (*data_size) = snprintf(
                    (char*)data, *data_size,
                    "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
            );
            break;
    }
    return(ret_val);
}

inline int StreamRecorderCurrentCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    
    if ((TempParam) && (TempParam->NumberofParameters > 0))
    {
        if (ret_val >= 0)
        {
            switch (MediaType) 
            {
                case Media_XML:
                    (*data_size) = snprintf(
                            (char*)data, *data_size,
                            "<CURRENTRECORDER>%d</CURRENTRECORDER>",
                            circularbuffer_get_first_index(&buffer)
                    );
                    break;
                case Media_TEXT:
                    (*data_size) = snprintf(
                            (char*)data, *data_size,
                            "%d", circularbuffer_get_first_index(&buffer)
                    );
                    break;
                case Media_BYTE:
                    Value = circularbuffer_get_first_index(&buffer);
                    memcpy((void*)data,(void*)&Value,4);
                    (*data_size) = 4;
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        switch (MediaType) 
        {
            case Media_XML:
                ret_val = INVALID_PARAMETERS_ERROR;
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "<INVALID_PARAMETERS_ERROR/>\r\n\r"
                );
                break;
            default:
                break;
        }
    }
    return(ret_val);
}
inline int StreamRecorderLastCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    
    if ((TempParam) && (TempParam->NumberofParameters > 0))
    {
        if (ret_val >= 0)
        {
            switch (MediaType) 
            {
                case Media_XML:
                    (*data_size) = snprintf(
                            (char*)data, *data_size,
                            "<LASTRECORDER>%d</LASTRECORDER>",
                            circularbuffer_get_first_index(&buffer)
                    );
                    break;
                case Media_TEXT:
                    (*data_size) = snprintf(
                            (char*)data, *data_size,
                            "%d", circularbuffer_get_first_index(&buffer)
                    );
                    break;
                case Media_BYTE:
                    Value = circularbuffer_get_last_index(&buffer);
                    memcpy((void*)data,(void*)&Value,4);
                    (*data_size) = 4;
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        switch (MediaType) 
        {
            case Media_XML:
                ret_val = INVALID_PARAMETERS_ERROR;
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "<INVALID_PARAMETERS_ERROR/>\r\n\r"
                );
                break;
            default:
                break;
        }
    }
    return(ret_val);
}
int StreamRecorderCurrentCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = StreamRecorderCurrentCommand_GET(
                    MediaType,TempParam,data,data_size
            );
            break;
        default:
            ret_val = INVALID_PARAMETERS_ERROR;
            (*data_size) = snprintf(
                    (char*)data, *data_size,
                    "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
            );
            break;
    }
    return(ret_val);
}
int StreamRecorderLastCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int  ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = StreamRecorderLastCommand_GET(
                    MediaType,TempParam,data,data_size
            );
            break;
        default:
            ret_val = INVALID_PARAMETERS_ERROR;
            (*data_size) = snprintf(
                    (char*)data, *data_size,
                    "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r"
            );
            break;
    }
    return(ret_val);
}
/*============================================================================*/
