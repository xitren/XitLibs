// ----------------------------------------------------------------------------
//
// strnlen.c - Contains animation system API
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <string.h>
#include "strnlen.h"
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
size_t strnlen(const char *s, size_t maxlen)
{  
	size_t		i;

	i = 0;
	while ((s[i]) && (i < maxlen))
		i++;
	return (i);
}
/*============================================================================*/
