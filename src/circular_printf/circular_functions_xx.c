/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"
#include "circular_printf.h"

char *my_put_x(char *buff, va_list *valist, t_circular_printf_flags *fl) {
	unsigned long long int d;
	size_t max;

	max = BUFF_PRINT - 1;
	d = get_unsigned_varg(valist, fl);
	if (!((d == 0) && (fl->precision_par == 1) && (fl->precision == 0)))
		put_unsnum_to_str(buff, &max, get_base16x_string(fl->flags) + 1, d);
	else
		buff[--(max)] = 0;
	if (fl->precision_par == 1)
		put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->flags & F_SHARP) && (d != 0))
		put_prefix_x_to_str(buff, &max);
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& (fl->precision_par != 1)
			&& !(fl->flags & (F_MINUS))) {
		put_str_align_zeros(buff, 0, &max, fl->min_width);
		if ((fl->flags & F_SHARP) && (d != 0))
			put_prefix_x_mod_to_str(buff, &max);
	}
	return (put_str_align(buff, &max, fl));
}

char *my_put_xx(char *buff, va_list *valist, t_circular_printf_flags *fl) {
	unsigned long long int d;
	size_t max;

	max = BUFF_PRINT - 1;
	d = get_unsigned_varg(valist, fl);
	if (!((d == 0) && (fl->precision_par == 1) && (fl->precision == 0)))
		put_unsnum_to_str(buff, &max, get_base16xx_string(fl->flags) + 1, d);
	else
		buff[--(max)] = 0;
	if (fl->precision_par == 1)
		put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->flags & F_SHARP) && (d != 0))
		put_prefix_xx_to_str(buff, &max);
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& (fl->precision_par != 1)
			&& !(fl->flags & (F_MINUS))) {
		put_str_align_zeros(buff, 0, &max, fl->min_width);
		if ((fl->flags & F_SHARP) && (d != 0))
			put_prefix_xx_mod_to_str(buff, &max);
	}
	return (put_str_align(buff, &max, fl));
}

