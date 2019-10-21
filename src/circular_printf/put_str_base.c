/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"
#include <math.h>

char	*get_base8_string(char flag)
{
	char *bptr;

	if ((flag & (F_PLUS)))
		bptr = "+01234567";
	else if ((flag & (F_MINUS)))
		bptr = "-01234567";
	else
		bptr = "-01234567";
	return (bptr);
}

char	*get_base16x_string(char flag)
{
	char *bptr;

	if ((flag & (F_PLUS)))
		bptr = "+0123456789abcdef";
	else if ((flag & (F_MINUS)))
		bptr = "-0123456789abcdef";
	else
		bptr = "-0123456789abcdef";
	return (bptr);
}

char	*get_base16xx_string(char flag)
{
	char *bptr;

	if ((flag & (F_PLUS)))
		bptr = "+0123456789ABCDEF";
	else if ((flag & (F_MINUS)))
		bptr = "-0123456789ABCDEF";
	else
		bptr = "-0123456789ABCDEF";
	return (bptr);
}

char	*get_base10_string(char flag)
{
	char *bptr;

	if ((flag & (F_PLUS | F_SPACE)))
		bptr = "+0123456789";
	else if ((flag & (F_MINUS)))
		bptr = "-0123456789";
	else
		bptr = "-0123456789";
	return (bptr);
}

char	*get_not(char *buff, size_t *max, double pre_calcs)
{
	if (pre_calcs == INFINITY)
	{
		(*max) -= 4;
		strcpy(buff + (*max), "inf");
	}
	else if (pre_calcs == -INFINITY)
	{
		(*max) -= 5;
		strcpy(buff + (*max), "-inf");
	}
	else if (isnan(pre_calcs))
	{
		(*max) -= 4;
		strcpy(buff + (*max), "nan");
	}
	else
		return (0);
	return (buff + (*max));
}




