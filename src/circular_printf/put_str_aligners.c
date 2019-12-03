/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"
#include "circular_functions.h"

char *put_str_align(char *buff, size_t *max, t_circular_printf_flags *fl)
{
	char *p;

	if (fl->flags & F_MINUS)
		p = put_str_align_left(buff, 0, max, fl->min_width);
	else
		p = put_str_align_right(buff, 0, max, fl->min_width);
	return (p);
}

char *put_str_space_before(char *buffer,
		size_t *max, char f)
{
	if (f && ((*max) > 0))
	{
		buffer[--(*max)] = ' ';
	}
	return (buffer + (*max));
}

char *put_str_align_zeros(char *buffer, size_t alr,
		size_t *max, size_t prec)
{
	char sign;

	sign = buffer[(*max)];
	if (alr == 0)
	{
		if ((sign == '-' || sign == '+'))
			alr = strlen(buffer + (*max));
		else
			alr = strlen(buffer + (*max));
	}
	if (prec > alr)
		prec -= alr;
	else
		return (buffer + (*max));
	if (!(buffer[(*max)] == '-' || buffer[(*max)] == '+'))
		(*max)--;
	while ((prec-- > 0) && ((*max) > 0))
		buffer[(*max)--] = '0';
	if ((sign == '-' || sign == '+'))
		buffer[(*max)--] = sign;
	return (buffer + ++(*max));
}

char *put_str_align_right(char *buffer, size_t alr,
		size_t *max, size_t min_width)
{
	if (alr == 0)
		alr = strlen(buffer + (*max));
	if (min_width > alr)
		min_width -= alr;
	else
		return (buffer + (*max));
	(*max)--;
	while ((min_width-- > 0) && ((*max) > 0))
		buffer[(*max)--] = ' ';
	if ((++(*max)) > 0)
		return (buffer + (*max));
	else
		return (buffer);
}

char *put_str_align_left(char *buffer, size_t alr,
		size_t *max, size_t min_width)
{
	if (alr == 0)
		alr = strnlen(buffer + (*max), BUFF_PRINT);
	if (min_width > alr)
		min_width -= alr;
	else
		return (buffer + (*max));
	strcpy(buffer, buffer + (*max));
	while ((min_width-- > 0) && ((*max) > 0))
		buffer[alr++] = ' ';
	buffer[alr] = 0;
	return (buffer);
}
