/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"
#include "circular_functions.h"

char is_type(char a) {
	if (((a == '%') || (a == 'd') || (a == 'i')
			|| (a == 'u') || (a == 'f') || (a == 'F')
			|| (a == 'e') || (a == 'E') || (a == 'g')
			|| (a == 'G') || (a == 'x') || (a == 'X')
			|| (a == 'o') || (a == 's') || (a == 'c')
			|| (a == 'p') || (a == 'a') || (a == 'A')
			|| (a == 'n') || (a == 'b')))
		return (1);
	else
		return (0);
}

char is_sign(char a) {
	if (((a == '%') || (('a' <= a) && (a <= 'z'))
			|| (('A' <= a) && (a <= 'Z'))))
		return (1);
	else
		return (0);
}

char check_step6(unsigned int *step, unsigned int i,
		t_circular_printf_list *container, t_circular_printf_flags *flags) {
	if ((*step < 5) && is_type(((char*) container->content)[i])) {
		*step = 5;
		flags->parameter = ((char*) container->content)[i];
		return (1);
	}
	return (0);
}

char check_step7(unsigned int *step, unsigned int i,
		t_circular_printf_list *container, t_circular_printf_flags *flags) {
	if ((*step < 5) && is_sign(((char*) container->content)[i])) {
		*step = 5;
		flags->parameter = ((char*) container->content)[i];
		return (1);
	}
	return (0);
}

