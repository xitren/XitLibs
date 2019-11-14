/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"
#include "circular_printf.h"

static void strprep(char *src, char cs, char cr) {
	while ((*src) != 0) {
		if ((*src) == cs)
			(*src) = cr;
		src++;
	}
}

char *my_put_d(char *buff, va_list *valist, t_circular_printf_flags *fl) {
	long long int d;
	char *p;
	size_t max;

	max = BUFF_PRINT - 1;
	d = get_signed_varg(valist, fl);
	if (!((d == 0) && (fl->precision_par == 1) && (fl->precision == 0)))
		p = put_num_to_str(buff, &max, get_base10_string(fl->flags), d);
	else
		p = put_onl_to_str(buff, &max, get_base10_string(fl->flags), d);
	if (fl->precision_par == 1)
		p = put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->flags & F_SHARP))
		p = put_zeros_to_str(buff, 0, &max, fl->precision);
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& (fl->precision_par != 1)
			&& !(fl->flags & (F_MINUS)))
		p = put_str_align_zeros(buff, 0, &max, fl->min_width);
	p = put_str_align(buff, &max, fl);
	if ((fl->flags & F_SPACE) && !(fl->flags & F_PLUS))
		strprep(p, '+', ' ');
	return (p);
}

void get_last(char *p[3], t_circular_printf_flags *fl,
		unsigned long cnt[5]) {
	cnt[0]++;
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& !(fl->flags & (F_MINUS)))
		p[0] = put_str_align_zeros(p[2], 0, cnt, fl->min_width);
	p[0] = put_str_align(p[2], cnt, fl);
}




