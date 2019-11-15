/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"

void set_flags_1(char v[2], t_circular_printf_flags *fl)
{
	v[0] = ' ';
	v[1] = ' ';
	if (fl->flags & F_ZERO)
	{
		if (fl->flags & F_PLUS)
		{
			if (fl->precision_par)
				v[0] = '0';
			else
				v[0] = ' ';
		} else
			v[0] = ' ';
	}
	if (fl->flags & F_SPACE)
		v[1] = ' ';
}

void set_flags_2(char v[2], t_circular_printf_flags *fl)
{
	v[0] = ' ';
	v[1] = ' ';
	if (fl->flags & F_ZERO)
	{
		if (fl->flags & F_PLUS)
			v[0] = ' ';
		else
			v[0] = ' ';
	}
	if (fl->flags & F_SPACE)
		v[1] = ' ';
}

void set_flags_3(char v[2], t_circular_printf_flags *fl)
{
	v[0] = ' ';
	v[1] = ' ';
	if (fl->flags & F_ZERO)
	{
		if (fl->precision_par == 1)
			v[0] = ' ';
		else
			v[0] = '0';
	}
	if (fl->flags & F_SPACE)
		v[1] = ' ';
}

void set_flags_4(char v[2], t_circular_printf_flags *fl)
{
	v[0] = ' ';
	v[1] = ' ';
	if (fl->flags & F_ZERO)
		v[0] = '0';
	if (fl->flags & F_SPACE)
		v[1] = ' ';
}

