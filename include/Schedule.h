// ----------------------------------------------------------------------------
//
// CommandModule.h - Implements a command module with link API and shedule
//                   deque
//
// ----------------------------------------------------------------------------

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/

#ifndef __SCHEDULEMODULE_H__
#define __SCHEDULEMODULE_H__   

#ifdef __cplusplus
extern "C" {
#endif

	/* Public structures ---------------------------------------------------------*/
	typedef int (*ScheduleFunction_t)(void);
	/*============================================================================*/

	/* Public variables ----------------------------------------------------------*/
	/*============================================================================*/

	/* Public function prototypes ------------------------------------------------*/
	void InitSchedule(void);
	void AddToSchedule(ScheduleFunction_t ScheduleFunction);
	void ClearSchedule(void);
	void ExecuteSchedule(void);
	/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
