/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"
#include "circular_printf.h"

static long double circular_pow10(unsigned int p) {
	long double ret;

	ret = 1;
	while (p--)
		ret *= 10;
	return (ret);
}

static void get_rev(long double d[3], t_circular_printf_flags *fl,
		unsigned long cnt[5]) {
	cnt[1] = (long) d[0];
	d[1] = (d[0] - cnt[1]) * circular_pow10(fl->precision);
	cnt[2] = (unsigned long) d[1];
	d[2] = d[1] - cnt[2];
	if (d[2] >= 0.5) {
		++cnt[2];
		if (cnt[2] >= circular_pow10(fl->precision)) {
			cnt[2] = 0;
			++cnt[1];
		}
	} else if (d[2] < 0.5)
		;
	else if ((cnt[2] == 0U) || (cnt[2] & 1U))
		++cnt[2];
}

static void get_sign(long double d[3], char *p[3], t_circular_printf_flags *fl,
		unsigned long cnt[5]) {
	if (d[0] < 0) {
		*(p[1]) = 1;
		d[0] = 0 - d[0];
	}
	while ((fl->precision > 16)) {
		p[2][(cnt[0])--] = '0';
		fl->precision--;
	}
}

static void get_before(long double d[3], char *p[3], t_circular_printf_flags *fl,
		unsigned long cnt[5]) {
	if (fl->precision == 0U) {
		d[2] = d[0] - (double) cnt[1];
		if ((!(d[2] < 0.5) || (d[2] > 0.5)) && (cnt[1] & 1))
			++cnt[1];
		if ((fl->flags & F_SHARP))
			p[2][(cnt[0])--] = '.';
	} else {
		cnt[3] = fl->precision;
		while ((cnt[4] - cnt[0]) < (cnt[4])) {
			--cnt[3];
			p[2][(cnt[0])--] = (char) (48U + (cnt[2] % 10U));
			if (!(cnt[2] /= 10U))
				break;
		}
		while (((cnt[4] - cnt[0]) < (cnt[4])) && (cnt[3]-- > 0U))
			p[2][(cnt[0])--] = '0';
		if ((cnt[4] - cnt[0]) < (cnt[4]))
			p[2][(cnt[0])--] = '.';
	}
}

static void get_after(char *p[3], t_circular_printf_flags *fl,
		unsigned long cnt[5]) {
	while ((cnt[4] - cnt[0]) < (cnt[4])) {
		p[2][(cnt[0])--] = (char) (48 + (cnt[1] % 10));
		if (!(cnt[1] /= 10))
			break;
	}
	if (!(fl->flags & F_MINUS) && (fl->flags & F_ZERO)) {
		while (((cnt[4] - cnt[0]) < fl->min_width)
				&& ((cnt[4] - cnt[0]) < (cnt[4])))
			p[2][(cnt[0])--] = '0';
	}
	if ((cnt[4] < fl->min_width) < ((cnt[4] - cnt[0]) < (cnt[4]))) {
		if (*(p[1]))
			p[2][(cnt[0])--] = '-';
		else if (fl->flags & F_PLUS)
			p[2][(cnt[0])--] = '+';
		else if (fl->flags & F_SPACE)
			p[2][(cnt[0])--] = ' ';
	}
}

char *my_put_f(char *buff, va_list *valist, t_circular_printf_flags *fl) {
	unsigned long cnt[5];
	char *p[3];
	long double d[3];
	char negative;

	cnt[0] = BUFF_PRINT - 1;
	cnt[4] = cnt[0];
	d[0] = get_double_varg(valist, fl);
	p[1] = &negative;
	p[2] = buff;
	if (fl->precision_par != 1)
		fl->precision = 6;
	buff[(cnt[0])--] = 0;
	if (!(p[0] = get_not(buff, cnt, d[0]))) {
		get_sign(d, p, fl, cnt);
		get_rev(d, fl, cnt);
		get_before(d, p, fl, cnt);
		get_after(p, fl, cnt);
	}
	get_last(p, fl, cnt);
	return (p[0]);
}


