/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"
#include "circular_printf.h"

char *my_put_perc(char *buff, va_list *valist, t_circular_printf_flags *fl)
{
	size_t max;
	char *p;

	max = BUFF_PRINT - 1;
	buff[(max)--] = 0;
	buff[(max)] = '%';
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& !(fl->flags & (F_MINUS)))
		p = put_str_align_zeros(buff, 0, &max, fl->min_width);
	if (fl->flags & F_MINUS)
		p = put_str_align_left(buff, 0, &max, fl->min_width);
	else
		p = put_str_align_right(buff, 0, &max, fl->min_width);
	fl = (t_circular_printf_flags *) valist;
	valist = (va_list *) fl;
	return (p);
}

char *my_put_s(char *buff, va_list *valist, t_circular_printf_flags *fl)
{
	size_t max;
	size_t mm;
	char *p;

	max = BUFF_PRINT - 1;
	p = va_arg(*valist, char *);
	if (!p)
		p = "(null)";
	if (fl->precision_par == 1)
		mm = fl->precision;
	else
		mm = strnlen(p, BUFF_PRINT);
	max -= mm;
	if (fl->precision_par == 1)
		strncpy(buff + (max), p, fl->precision);
	else
		strcpy(buff + (max), p);
	buff[BUFF_PRINT - 1] = 0;
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& !(fl->flags & (F_MINUS)))
		p = put_str_align_zeros(buff, mm, &max, fl->min_width);
	return (put_str_align(buff, &max, fl));
}

static char *put_char_align_left(char *buffer, size_t alr,
		size_t *max, size_t min_width)
{
	alr = 1;
	while ((min_width-- > 0) && (alr < BUFF_PRINT))
		buffer[alr++] = ' ';
	buffer[alr] = 0;
	buffer[0] = buffer[*max];
	*max = BUFF_PRINT - alr - 1;
	return (buffer);
}

char *my_put_c(char *buff, va_list *valist, t_circular_printf_flags *fl)
{
	size_t max;
	char *p;
	char d;

	max = BUFF_PRINT - 1;
	buff[(max)--] = 0;
	buff[(max)] = (char) va_arg(*valist, int);
	d = buff[(max)];
	if (buff[(max)] == 0 && fl->min_width && fl->min_width_par)
		fl->min_width--;
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& !(fl->flags & (F_MINUS)))
		p = put_str_align_zeros(buff, 0, &max, fl->min_width);
	if (fl->flags & F_MINUS)
	{
		if (d != 0)
			p = put_str_align_left(buff, 0, &(max), fl->min_width);
		else
			p = put_char_align_left(buff, max, &(max), fl->min_width);
	} else
		p = put_str_align_right(buff, 0, &max, fl->min_width);
	if (d == 0)
		fl->tt = BUFF_PRINT - 1 - max;
	return (p);
}

char *my_put_p(char *buff, va_list *valist, t_circular_printf_flags *fl)
{
	unsigned long long int d;
	size_t max;

	max = BUFF_PRINT - 1;
	d = (unsigned long long int) va_arg(*valist, void *);
	if (!((d == 0) && (fl->precision_par == 1) && (fl->precision == 0)))
		put_unsnum_to_str(buff, &max,
			get_base16x_string(fl->flags) + 1, d);
	if (fl->precision_par == 1)
		put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& (fl->precision_par != 1)
			&& !(fl->flags & (F_MINUS)))
	{
		put_str_align_zeros(buff, 0, &max, fl->min_width);
	}
	if (fl->precision_par == 1)
		put_prefix_x_to_str(buff, &max);
	else
		put_prefix_x_mod_to_str(buff, &max);
	return (put_str_align(buff, &max, fl));
}




