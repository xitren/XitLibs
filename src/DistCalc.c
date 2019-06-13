// ----------------------------------------------------------------------------
//
// DistCalc.c - API for distant calculation and perfomance measurement
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
#include "DistCalc.h"
#include "LogModule.h"
#include "CommandModule.h"
#include "coap.h"
/*============================================================================*/

/* Private defines -----------------------------------------------------------*/
int ClockCommand_GET(uint8_t MediaType, ParameterList_t *TempParam, 
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int ClockCommand_PUT(uint8_t MediaType, ParameterList_t *TempParam, 
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int ClockCommand_RESET(uint8_t MediaType, ParameterList_t *TempParam, 
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int CalculationFreeCycles_GET(uint8_t MediaType, ParameterList_t *TempParam, 
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int CalculationMaxCycles_GET(uint8_t MediaType, ParameterList_t *TempParam, 
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int CalculationMaxCycles_RESET(uint8_t MediaType, ParameterList_t *TempParam, 
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int CalculationPercentCycles_GET(uint8_t MediaType, ParameterList_t *TempParam, 
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
/*============================================================================*/

/* Private extern ------------------------------------------------------------*/
/*============================================================================*/

/* Private structures --------------------------------------------------------*/
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
const char* global_link_syncro[][2] = {
    {"/clock", "</clock>"},
    {"/calculation/cycles/free", "</calculation/cycles/free>"},
    {"/calculation/cycles/max", "</calculation/cycles/max>"},
    {"/calculation/cycles/percent", "</calculation/cycles/percent>"}
};
uint32_t now_clock = 0;
uint32_t free_cycles = 0;
uint32_t max_free_cycles = 1;
uint32_t last_free_cycles = 0;
/*============================================================================*/
    
/* Private constants ---------------------------------------------------------*/
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
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
  return;
}

inline int ClockCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        if (MediaType == Media_FREE)
            MediaType = Media_XML;
        switch (MediaType)
        {
            case Media_XML:
                current_coap_mediatype = Media_XML;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "<CLOCK>\r\n\r "
                        "%d"
                        "</CLOCK>\r\n\r",
                        (int)GetClock()
                );
                break;
            case Media_TEXT:
                current_coap_mediatype = Media_TEXT;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "%d", (int)GetClock()
                );
                break;
            case Media_BYTE:
                current_coap_mediatype = Media_BYTE;
                Value = (int)GetClock();
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

inline int ClockCommand_PUT(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        if (MediaType == Media_FREE)
            MediaType = Media_XML;
        ret_val = get_parameter(TempParam,"value",(uint32_t*)&Value);
        if ( (ret_val >= 0) )
        {
            SetClock(Value);
            switch (MediaType)
            {
                case Media_XML:
                    current_coap_mediatype = Media_XML;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "<CLOCK>\r\n\r "
                            "%d"
                            "</CLOCK>\r\n\r",
                            (int)GetClock()
                    );
                    break;
                case Media_TEXT:
                    current_coap_mediatype = Media_TEXT;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "%d", (int)GetClock()
                    );
                    break;
                case Media_BYTE:
                    current_coap_mediatype = Media_BYTE;
                    Value = (int)GetClock();
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

inline int ClockCommand_RESET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        if ( (ret_val >= 0) )
        {
            if (MediaType == Media_FREE)
                MediaType = Media_XML;
            SetClock(0);
            switch (MediaType)
            {
                case Media_XML:
                    current_coap_mediatype = Media_XML;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "<CLOCK>\r\n\r "
                            "%d"
                            "</CLOCK>\r\n\r",
                            (int)GetClock()
                    );
                    break;
                case Media_TEXT:
                    current_coap_mediatype = Media_TEXT;
                    (*data_size) = snprintf(
                            (char*)data, buffer_size,
                            "%d", (int)GetClock()
                    );
                    break;
                case Media_BYTE:
                    current_coap_mediatype = Media_BYTE;
                    Value = (int)GetClock();
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

int ClockCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = ClockCommand_GET(
                    MediaType,TempParam,data,data_size,buffer_size
            );
            break;
        case Method_PUT:
            ret_val = ClockCommand_PUT(
                    MediaType,TempParam,data,data_size,buffer_size
            );
            break;
        case Method_RESET:
            ret_val = ClockCommand_RESET(
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

inline int CalculationFreeCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        if (MediaType == Media_FREE)
            MediaType = Media_XML;
        switch (MediaType)
        {
            case Media_XML:
                current_coap_mediatype = Media_XML;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "<FREECYCLES>\r\n\r "
                        "%d"
                        "</FREECYCLES>\r\n\r",
                        (int)GetCycle()
                );
                break;
            case Media_TEXT:
                current_coap_mediatype = Media_TEXT;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "%d", (int)GetCycle()
                );
                break;
            case Media_BYTE:
                current_coap_mediatype = Media_BYTE;
                Value = (int)GetCycle();
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

int CalculationFreeCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = CalculationFreeCycles_GET(
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

inline int CalculationMaxCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        if (MediaType == Media_FREE)
            MediaType = Media_XML;
        switch (MediaType)
        {
            case Media_XML:
                current_coap_mediatype = Media_XML;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "<MAXCYCLES>\r\n\r "
                        "%d"
                        "</MAXCYCLES>\r\n\r",
                        (int)GetMaxCycle()
                );
                break;
            case Media_TEXT:
                current_coap_mediatype = Media_TEXT;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "%d", (int)GetMaxCycle()
                );
                break;
            case Media_BYTE:
                current_coap_mediatype = Media_BYTE;
                Value = (int)GetMaxCycle();
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
inline int CalculationMaxCycles_RESET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        if (MediaType == Media_FREE)
            MediaType = Media_XML;
        max_free_cycles = 1;
        switch (MediaType)
        {
            case Media_XML:
                current_coap_mediatype = Media_XML;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "<MAXCYCLES>\r\n\r "
                        "%d"
                        "</MAXCYCLES>\r\n\r",
                        (int)GetMaxCycle()
                );
                break;
            case Media_TEXT:
                current_coap_mediatype = Media_TEXT;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "%d", (int)GetMaxCycle()
                );
                break;
            case Media_BYTE:
                current_coap_mediatype = Media_BYTE;
                Value = (int)GetMaxCycle();
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

int CalculationMaxCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = CalculationMaxCycles_GET(
                    MediaType,TempParam,data,data_size,buffer_size
            );
            break;
        case Method_RESET:
            ret_val = CalculationMaxCycles_RESET(
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

inline int CalculationPercentCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        if (MediaType == Media_FREE)
            MediaType = Media_XML;
        switch (MediaType)
        {
            case Media_XML:
                current_coap_mediatype = Media_XML;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "<PERCENTCYCLES>\r\n\r "
                        "%d"
                        "</PERCENTCYCLES>\r\n\r",
                        (int)GetPercent()
                );
                break;
            case Media_TEXT:
                current_coap_mediatype = Media_TEXT;
                (*data_size) = snprintf(
                        (char*)data, buffer_size,
                        "%d", (int)GetPercent()
                );
                break;
            case Media_BYTE:
                current_coap_mediatype = Media_BYTE;
                Value = (int)GetPercent();
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
    else
    {
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, buffer_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }

    return(ret_val);
}

int CalculationPercentCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = CalculationPercentCycles_GET(
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