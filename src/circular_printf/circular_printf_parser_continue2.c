/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"
#include "circular_functions.h"

char is_flag(char a)
{
	if (((a == '#') || (a == '0') || (a == '-')
			|| (a == '+') || (a == ' ') || (a == '\'')
			|| (a == 'I')))
		return (1);
	else
		return (0);
}

char is_spec(char a)
{
	if (((a == 'l') || (a == 'h') || (a == 'j')
			|| (a == 'z') || (a == 't') || (a == 'L')))
		return (1);
	else
		return (0);
}

char *circular_strfix(char *ret)
{
	char *rr;

	if (ret[0] == '0' && ret[1] == '0' && (rr = strrchr(ret, 'x')))
	{
		*rr = '0';
		ret[1] = 'x';
	}
	if (ret[0] == '0' && ret[1] == '0' && (rr = strrchr(ret, 'X')))
	{
		*rr = '0';
		ret[1] = 'X';
	}
	return (ret);
}


