// ----------------------------------------------------------------------------
//
// CommandModule.c - Implements a command module with link API and shedule
//                   deque
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "LibConfig.h"
#include "deque.h"
#include "umm_malloc.h"
#include "LogModule.h"
#include "Schedule.h"
/*============================================================================*/

/* Private structures --------------------------------------------------------*/
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
static Deque *ScheduleTableDeque;
/*============================================================================*/

/* Private function prototypes -----------------------------------------------*/
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void InitSchedule(void) {
	if (deque_new(&ScheduleTableDeque) != 0)
		return;
}

void AddToSchedule(ScheduleFunction_t ScheduleFunction) {
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	ScheduleFunction_t *comm;
	comm = (ScheduleFunction_t *) umm_calloc(1, sizeof (ScheduleFunction_t));
	if ((comm == NULL)) {
		DBG_LOG_ERROR("comm argument is NULL\n");
		return;
	}
	*comm = ScheduleFunction;
	if (deque_add_last(ScheduleTableDeque, (void *) comm) != 0) {
		umm_free((void *) comm);
		return;
	}
	return;
}

void ClearSchedule(void) {
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((ScheduleTableDeque == NULL)) {
		DBG_LOG_ERROR("ScheduleTableDeque argument is NULL\n");
		return;
	}
	deque_remove_all_free(ScheduleTableDeque);
	return;
}

void ExecuteSchedule(void) {
	ScheduleFunction_t *Comm;

	if ((ScheduleTableDeque == NULL)) {
		DBG_LOG_ERROR("ScheduleTableDeque argument is NULL\n");
		return;
	}
	while (deque_size(ScheduleTableDeque) > 0) {
		deque_remove_first(ScheduleTableDeque, (void**) &Comm);
		if ((Comm == NULL)) {
			DBG_LOG_ERROR("Comm argument is NULL\n");
			continue;
		}
		if (deque_size(ScheduleTableDeque) > 2) {
			DBG_LOG_INFO("Schedule executing, %d left. \n",
					deque_size(ScheduleTableDeque));
		}
		(*(*Comm))();
		umm_free((void *) Comm);
	}
	return;
}
/*============================================================================*/
