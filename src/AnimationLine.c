// ----------------------------------------------------------------------------
//
// AnimationLine.c - Contains animation system API
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <string.h>
#include "AnimationLine.h"
#include "LogModule.h"
#include "CommandModule.h"
#include "coap.h"
#include "array.h"
#include "umm_malloc.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
static enum timeline_mode animation_mode = 0;
static uint8_t animation_needed;
static uint32_t animation_time;
static Array *FiguresArray;
static DrawFunction_t func;
const char* global_link_animation[][2] = {
	{"/animation/line", "</animation/line>"},
	{"/animation/figures/%s", "</animation/figures/%s>"}
};
/*============================================================================*/

/* Private function prototypes -----------------------------------------------*/
int AnimationLine_PUT(uint8_t MediaType, ParameterList_t *TempParam,
		uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int AnimationLine_GET(uint8_t MediaType, ParameterList_t *TempParam,
		uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int AnimationLine_RESET(uint8_t MediaType, ParameterList_t *TempParam,
		uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void InitCfgAnimLine(DrawFunction_t _func, uint8_t _mode) {
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	func = _func;
	animation_mode = _mode;
	if (FiguresArray != 0) {
		ResetAnimationLine();
	} else {
		if (array_new(&FiguresArray) != 0) {
			return;
		}
	}
	ResetAnimationTime();
	animation_needed = 0;
	return;
}

void ResetAnimationTime(void) {
	animation_time = 0;
}

uint32_t GetAnimationTime(void) {
	return animation_time;
}

void ResetAnimationLine(void) {
	UserFigure_t *commf;
	while (array_size(FiguresArray) > 0) {
		array_remove_at(FiguresArray, 0, (void**) &commf);
		umm_free(commf->name);
		if (commf->size_type > 1)
			umm_free(commf->data);
		umm_free(commf);
	}
}

void IncAnimationTime(void) {
	UserFigure_t *commf;
	animation_time++;
	if (array_size(FiguresArray) > 0) {
		array_get_at(FiguresArray, 0, (void**) &commf);
		if (func && (commf->show_time < animation_time)) {
			if (animation_mode) {
				animation_needed = 1;
			} else {
				(func) (commf);
				if (commf->permanent)
					AddAnimationFigure(
						commf->size_type, commf->name,
						commf->show_time + commf->permanent, commf->data,
						commf->x, commf->y, commf->permanent
						);
				array_remove_at(FiguresArray, 0, (void**) &commf);
				umm_free(commf->name);
				if (commf->size_type > 1)
					umm_free(commf->data);
				umm_free(commf);
			}
		}
	}
}

void MainAnimationCycle(void) {
	UserFigure_t *commf;
	if ((array_size(FiguresArray) > 0) && animation_needed && animation_mode) {
		array_get_at(FiguresArray, 0, (void**) &commf);
		if (func && (commf->show_time < animation_time)) {
			(func) (commf);
			if (commf->permanent)
				AddAnimationFigure(
					commf->size_type, commf->name,
					commf->show_time + commf->permanent, commf->data,
					commf->x, commf->y, commf->permanent
					);
			array_remove_at(FiguresArray, 0, (void**) &commf);
			umm_free(commf->name);
			if (commf->size_type > 1)
				umm_free(commf->data);
			umm_free(commf);
		}
	}
	animation_needed = 0;
}

#define FULL_DATA_SIZE  (LED_WIDTH * 3 * LED_HEIGHT) / 8
#define QUARTER_DATA_SIZE (LED_WIDTH * 3 * LED_HEIGHT) / 32
#define AREA_DATA_SIZE  6
#define SMALLAREA_DATA_SIZE 2

int SetAnimationFigure(char _size_type, char *_name,
		uint32_t _show_time, uint8_t *_data,
		uint8_t _x, uint8_t _y,
		uint32_t _permanent) {
	int ret_val = 0;
	UserFigure_t comm;
	comm.size_type = _size_type;
	comm.show_time = _show_time;
	comm.x = _x;
	comm.y = _y;
	comm.permanent = _permanent;
	comm.name = "";
	comm.data = _data;
	if (func)
		(func)(&comm);
	return (ret_val);
}

int AddAnimationFigure(char _size_type, char *_name,
		uint32_t _show_time, uint8_t *_data,
		uint8_t _x, uint8_t _y,
		uint32_t _permanent) {
	int ret_val = 0;
	size_t strl = 0;
	size_t Index = 0;
	UserFigure_t *comm;
	UserFigure_t *commf;

	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	/* First, make sure that the parameters passed to us appear to be    */
	/* semi-valid.                                                       */
	if ((_show_time) && (FiguresArray)) {
		/* Simply add the command data to the command table and        */
		/* increment the number of supported commands.                 */
		comm = (UserFigure_t *) umm_calloc(1, sizeof (UserFigure_t));
		if (comm == NULL) {
			return 1;
		}
		comm->size_type = _size_type;
		comm->show_time = _show_time;
		comm->x = _x;
		comm->y = _y;
		comm->permanent = _permanent;
		strl = strlen(_name) + 1;
		comm->name = (char *) umm_malloc(strl);
		if (comm->name == NULL) {
			umm_free(comm);
			return 1;
		}
		memcpy(comm->name, _name, strl);
		switch (_size_type) {
			case 0:
				comm->data = _data;
				break;
			case 1:
				comm->data = _data;
				break;
			case 2:
				comm->data = (uint8_t *) umm_malloc(AREA_DATA_SIZE);
				if (comm->data == NULL) {
					umm_free(comm->name);
					umm_free(comm);
					return 1;
				}
				memcpy(comm->data, _data, AREA_DATA_SIZE);
				break;
			default:
				comm->data = (uint8_t *) umm_malloc(SMALLAREA_DATA_SIZE);
				if (comm->data == NULL) {
					umm_free(comm->name);
					umm_free(comm);
					return 1;
				}
				memcpy(comm->data, _data, SMALLAREA_DATA_SIZE);
				break;
		}
		//Finding the position
		strl = array_size(FiguresArray);
		for (Index = 0;
				Index < strl; /* && (!ret_val)*/
				Index++) {
			array_get_at(FiguresArray, Index, (void**) &commf);
			if (_show_time < commf->show_time)
				break;
		}
		//Insert before the position
		if (Index < strl) {
			if (array_add_at(FiguresArray, (void *) comm, Index) != 0) {
				umm_free(comm->name);
				if (_size_type > 1)
					umm_free(comm->data);
				umm_free(comm);
				return 1;
			}
		} else {
			if (array_add(FiguresArray, (void *) comm) != 0) {
				umm_free(comm->name);
				if (_size_type > 1)
					umm_free(comm->data);
				umm_free(comm);
				return 1;
			}
		}
		DBG_LOG_INFO("%s\n", _name);
		DBG_LOG_INFO("Figure added.\n");

		/* Return success to the caller.                               */
		ret_val = 0;
	} else {
		ret_val = 1;
	}

	return (ret_val);
}

int AnimationLine_RESET(uint8_t MediaType, ParameterList_t *TempParam,
		uint8_t *data, uint32_t *data_size, uint32_t buffer_size) {
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	InitCfgAnimLine(func, TIMELINE_INDEPENDENT_CYCLE_DRAW);
	return 0;
}

int AnimationLine_GET(uint8_t MediaType, ParameterList_t *TempParam,
		uint8_t *data, uint32_t *data_size, uint32_t buffer_size) {
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	int ret_val = 0;
	//    int Address = -1;
	//    int Value = -1;
	//
	//    DBG_LOG_TRACE("%s: %08X (NumberofParameters %d)\n",
	//            __func__,
	//            (unsigned int)TempParam,
	//            TempParam->NumberofParameters);
	//    if ((TempParam) && (TempParam->NumberofParameters > 0))
	//    {
	//        ret_val = get_parameter(TempParam, "address", (uint32_t *) &Address);
	//        if (MediaType == Media_FREE)
	//            MediaType = Media_XML;
	//        DBG_LOG_TRACE("%s: %08X = %d\n", __func__, Address, Value);
	//        if (ret_val >= 0)
	//        {
	//            ret_val = 0;
	//            DBG_LOG_TRACE("%s: Gen res %d\n", __func__, MediaType);
	//            switch (MediaType)
	//            {
	//                case Media_XML:
	//                    current_coap_mediatype = Media_XML;
	//                    (*data_size) = snprintf(
	//                            (char *) data, buffer_size,
	//                            "<MEMORY>\r\n\r "
	//                            "<ADDRESS>%d</ADDRESS>\r\n\r "
	//                            "<VALUE>%d</VALUE>\r\n\r"
	//                            "</MEMORY>\r\n\r",
	//                            (int) Address,
	//                            (int) ReadMem(Address));
	//                    break;
	//                case Media_TEXT:
	//                    current_coap_mediatype = Media_TEXT;
	//                    (*data_size) = snprintf(
	//                            (char *) data,
	//                            buffer_size,
	//                            "%d",
	//                            (int) ReadMem(Address));
	//                    break;
	//                case Media_BYTE:
	//                    current_coap_mediatype = Media_BYTE;
	//                    Value = (int) ReadMem(Address);
	//                    memcpy((void *) data, (void *) &Value, 4);
	//                    (*data_size) = 4;
	//                    break;
	//                default:
	//                    current_coap_mediatype = Media_XML;
	//                    (*data_size) = snprintf(
	//                            (char *) data,
	//                            buffer_size,
	//                            "<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r");
	//                    break;
	//            }
	//        }
	//    }
	//    else
	//    {
	//        current_coap_mediatype = Media_XML;
	//        ret_val = INVALID_PARAMETERS_ERROR;
	//        (*data_size) = snprintf(
	//                (char *) data,
	//                buffer_size,
	//                "<INVALID_PARAMETERS_ERROR/>\r\n\r");
	//    }
	return (ret_val);
}

int AnimationLine_PUT(uint8_t MediaType, ParameterList_t *TempParam,
		uint8_t *data, uint32_t *data_size, uint32_t buffer_size) {
	DBG_LOG_TRACE("This is line %d of file %s (function %s).\n",
			__LINE__, __FILE__, __func__);
	int ret_val1 = 0;
	//    int ret_val2 = 0;
	//    int Address = -1;
	//    int Value = -1;
	//
	//    if ((TempParam) && (TempParam->NumberofParameters > 0))
	//    {
	//        ret_val1 = get_parameter(TempParam, "address", (uint32_t *) &Address);
	//        ret_val2 = get_parameter(TempParam, "value", (uint32_t *) &Value);
	//        if (ret_val2 >= 0)
	//            WriteMem(Address, Value);
	//        if (MediaType == Media_FREE)
	//            MediaType = Media_XML;
	//        data[*data_size - 1] = 0;
	//        switch (MediaType)
	//        {
	//            case Media_XML:
	//                current_coap_mediatype = Media_XML;
	//                ret_val2 = sscanf(
	//                        (char *) data,
	//                        "<MEMORY>\r\n\r "
	//                        "<ADDRESS>%d</ADDRESS>\r\n\r"
	//                        "<VALUE>%d</VALUE>\r\n\r"
	//                        "</MEMORY>\r\n\r",
	//                        &Address,
	//                        &Value);
	//                if (ret_val2 > 1)
	//                {
	//                    ret_val2 = INVALID_PARAMETERS_ERROR;
	//                    return ret_val2;
	//                }
	//                break;
	//            case Media_TEXT:
	//                ret_val1 = get_parameter(TempParam,
	//                        "address",
	//                        (uint32_t *) &Address);
	//                if (ret_val2 > 1)
	//                {
	//                    ret_val2 = INVALID_PARAMETERS_ERROR;
	//                    return ret_val2;
	//                }
	//                ret_val2 = sscanf(
	//                        (char *) data,
	//                        "%d",
	//                        &Value);
	//                if (ret_val2 > 0)
	//                {
	//                    ret_val2 = INVALID_PARAMETERS_ERROR;
	//                    return ret_val2;
	//                }
	//                break;
	//            case Media_BYTE:
	//                memcpy((void *) &Value, (void *) data, 4);
	//                break;
	//            default:
	//                break;
	//        }
	//        WriteMem(Address, Value);
	//    }
	//    else
	//    {
	//        current_coap_mediatype = Media_XML;
	//        ret_val1 = INVALID_PARAMETERS_ERROR;
	//    }
	return (ret_val1);
}

int AnimationLine(uint8_t Method, uint8_t MediaType, ParameterList_t *TempParam,
		uint8_t *data, uint32_t *data_size, uint32_t buffer_size) {
	DBG_LOG_TRACE("This is line %d of file %s (function %s).\n",
			__LINE__, __FILE__, __func__);
	int ret_val = 0;
	switch (Method) {
		case Method_RESET:
			ret_val = AnimationLine_RESET(
					MediaType, TempParam, data, data_size, buffer_size);
			break;
		case Method_GET:
			ret_val = AnimationLine_GET(
					MediaType, TempParam, data, data_size, buffer_size);
			break;
		case Method_PUT:
			ret_val = AnimationLine_PUT(
					MediaType, TempParam, data, data_size, buffer_size);
			break;
		default:
			current_coap_mediatype = Media_XML;
			ret_val = INVALID_PARAMETERS_ERROR;
			(*data_size) = snprintf(
					(char *) data,
					buffer_size,
					"<MEDIA_FORMAT_NOT_ALLOWED/>\r\n\r");
			break;
	}
	return (ret_val);
}
/*============================================================================*/