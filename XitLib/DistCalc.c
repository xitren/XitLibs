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
/*============================================================================*/

/* Private defines -----------------------------------------------------------*/
int ClockCommand_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int ClockCommand_PUT(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int CalculationFreeCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int CalculationMaxCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int CalculationPercentCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
/*============================================================================*/

/* Private extern ------------------------------------------------------------*/
/*============================================================================*/

/* Private structures --------------------------------------------------------*/
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
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
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        switch (MediaType)
        {
            case Media_XML:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "<CLOCK>\r\n\r "
                        "%d"
                        "</CLOCK>\r\n\r",
                        (int)GetClock()
                );
                break;
            case Media_TEXT:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "%d", (int)GetClock()
                );
                break;
            case Media_BYTE:
                Value = (int)GetClock();
                memcpy((void*)data,(void*)&Value,4);
                (*data_size) = 4;
                break;
            default:
                break;
        }
    }
    else
    {
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, *data_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }

    return(ret_val);
}

inline int ClockCommand_PUT(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam) && (TempParam->NumberofParameters > 0))
    {
        ret_val = get_parameter(TempParam,"value",(uint32_t*)&Value);
        if ( (ret_val >= 0) )
        {
            SetClock(Value);
            switch (MediaType)
            {
                case Media_XML:
                    (*data_size) = snprintf(
                            (char*)data, *data_size,
                            "<CLOCK>\r\n\r "
                            "%d"
                            "</CLOCK>\r\n\r",
                            (int)GetClock()
                    );
                    break;
                case Media_TEXT:
                    (*data_size) = snprintf(
                            (char*)data, *data_size,
                            "%d", (int)GetClock()
                    );
                    break;
                case Media_BYTE:
                    Value = (int)GetClock();
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
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, *data_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }

    return(ret_val);
}

int ClockCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = ClockCommand_GET(MediaType,TempParam,data,data_size);
            break;
        case Method_PUT:
            ret_val = ClockCommand_PUT(MediaType,TempParam,data,data_size);
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

inline int CalculationFreeCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        switch (MediaType)
        {
            case Media_XML:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "<FREECYCLES>\r\n\r "
                        "%d"
                        "</FREECYCLES>\r\n\r",
                        (int)GetCycle()
                );
                break;
            case Media_TEXT:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "%d", (int)GetCycle()
                );
                break;
            case Media_BYTE:
                Value = (int)GetCycle();
                memcpy((void*)data,(void*)&Value,4);
                (*data_size) = 4;
                break;
            default:
                break;
        }
    }
    else
    {
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, *data_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }

    return(ret_val);
}

int CalculationFreeCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = CalculationFreeCycles_GET(MediaType,TempParam,data,data_size);
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

inline int CalculationMaxCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        switch (MediaType)
        {
            case Media_XML:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "<MAXCYCLES>\r\n\r "
                        "%d"
                        "</MAXCYCLES>\r\n\r",
                        (int)GetMaxCycle()
                );
                break;
            case Media_TEXT:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "%d", (int)GetMaxCycle()
                );
                break;
            case Media_BYTE:
                Value = (int)GetMaxCycle();
                memcpy((void*)data,(void*)&Value,4);
                (*data_size) = 4;
                break;
            default:
                break;
        }
    }
    else
    {
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, *data_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }

    return(ret_val);
}

int CalculationMaxCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = CalculationMaxCycles_GET(MediaType,TempParam,data,data_size);
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

inline int CalculationPercentCycles_GET(uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    int Value = -1;
    if ((TempParam))
    {
        switch (MediaType)
        {
            case Media_XML:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "<PERCENTCYCLES>\r\n\r "
                        "%d"
                        "</PERCENTCYCLES>\r\n\r",
                        (int)GetPercent()
                );
                break;
            case Media_TEXT:
                (*data_size) = snprintf(
                        (char*)data, *data_size,
                        "%d", (int)GetPercent()
                );
                break;
            case Media_BYTE:
                Value = (int)GetPercent();
                memcpy((void*)data,(void*)&Value,4);
                (*data_size) = 4;
                break;
            default:
                break;
        }
    }
    else
    {
        ret_val = INVALID_PARAMETERS_ERROR;
        (*data_size) = snprintf(
                (char*)data, *data_size,
                "<INVALID_PARAMETERS_ERROR/>\r\n\r"
        );
    }

    return(ret_val);
}

int CalculationPercentCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = 0;
    switch (Method) 
    {
        case Method_GET:
            ret_val = CalculationPercentCycles_GET(
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