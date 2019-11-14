/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"
#include "circular_printf.h"

char *my_put_u(char *buff, va_list *valist, t_circular_printf_flags *fl) {
	long long int d;
	size_t max;

	max = BUFF_PRINT;
	d = get_unsigned_varg(valist, fl);
	if (!((d == 0) && (fl->precision_par == 1) && (fl->precision == 0)))
		put_unsnum_to_str(buff, &max, get_base10_string(fl->flags) + 1, d);
	else
		buff[--(max)] = 0;
	if (fl->precision_par == 1)
		put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->flags & F_SHARP))
		put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& (fl->precision_par != 1)
			&& !(fl->flags & (F_MINUS)))
		put_str_align_zeros(buff, 0, &max, fl->min_width);
	return (put_str_align(buff, &max, fl));
}

char *my_put_o(char *buff, va_list *valist, t_circular_printf_flags *fl) {
	unsigned long long int d;
	size_t max;

	max = BUFF_PRINT;
	d = get_unsigned_varg(valist, fl);
	if (!((d == 0) && (fl->precision_par == 1) && (fl->precision == 0)))
		put_unsnum_to_str(buff, &max, get_base8_string(fl->flags) + 1, d);
	else
		buff[--(max)] = 0;
	if (fl->precision_par == 1)
		put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->flags & F_SHARP))
		put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->flags & F_SHARP))
		put_prefix_0_to_str(buff, &max);
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& (fl->precision_par != 1)
			&& !(fl->flags & (F_MINUS)))
		put_str_align_zeros(buff, 0, &max, fl->min_width);
	return (put_str_align(buff, &max, fl));
}

