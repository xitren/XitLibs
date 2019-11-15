/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"
#include "circular_functions.h"

char check_step1(unsigned int *step, unsigned int i,
		t_circular_printf_list *container, t_circular_printf_flags *flags)
{
	if (*step == 0)
	{
		if (((char*) container->content)[i] == '#')
			flags->flags |= F_SHARP;
		if (((char*) container->content)[i] == '0')
			flags->flags |= F_ZERO;
		if (((char*) container->content)[i] == '-')
			flags->flags |= F_MINUS;
		if (((char*) container->content)[i] == '+')
			flags->flags |= F_PLUS;
		if (((char*) container->content)[i] == ' ')
			flags->flags |= F_SPACE;
		if (((char*) container->content)[i] == '\'')
			flags->flags |= F_SEPARATOR;
		if (((char*) container->content)[i] == 'i')
			flags->flags |= F_INCLUDE;
		return (1);
	}
	return (0);
}

char check_step2(unsigned int *step, unsigned int i,
		t_circular_printf_list *container, t_circular_printf_flags *flags)
{
	if ((*step < 1) && ISDIGIT(((char*) container->content)[i])
			&& (((char*) container->content)[i] != '0'))
	{
		*step = 1;
		flags->min_width_par = 1;
		flags->min_width = atoi(container->content + i);
		if (((char*) container->content)[i] == '*')
			flags->min_width_par = 2;
		return (1);
	}
	return (0);
}

char check_step3(unsigned int *step, unsigned int i,
		t_circular_printf_list *container, t_circular_printf_flags *flags)
{
	if ((*step < 2) && (((char*) container->content)[i] == '.'))
	{
		*step = 2;
		i++;
		flags->precision_par = 1;
		flags->precision = atoi(container->content + i);
		if (((char*) container->content)[i] == '*')
			flags->precision_par = 2;
		return (1);
	}
	return (0);
}

char check_step4(unsigned int *step, unsigned int i,
		t_circular_printf_list *container, t_circular_printf_flags *flags)
{
	char p;

	if ((*step < 3) && is_spec(((char*) container->content)[i]))
	{
		*step = 3;
		p = ((char*) container->content)[i];
		if (p == 'l')
			flags->length |= F_LONG;
		if (p == 'h')
			flags->length |= F_SHORT;
		if (p == 'L')
			flags->length |= F_UPCASE;
		return (1);
	}
	return (0);
}

char check_step5(unsigned int *step, unsigned int i,
		t_circular_printf_list *container, t_circular_printf_flags *flags)
{
	char p;

	if ((*step < 4) && ISSPEC2(((char*) container->content)[i]))
	{
		*step = 4;
		p = ((char*) container->content)[i];
		if (p == 'l')
			flags->length |= F_LONG2;
		if (p == 'h')
			flags->length |= F_SHORT2;
		return (1);
	}
	return (0);
}



