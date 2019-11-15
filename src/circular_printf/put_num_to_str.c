/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"

char *put_unsnum_to_str(char *buffer, size_t *max,
		char *bptr, unsigned long long n)
{
	size_t base;

	(*max)--;
	buffer[(*max)--] = 0;
	base = strlen(bptr);
	while ((n >= base) && ((*max) > 0))
	{
		buffer[(*max)--] = bptr[n % base];
		n = n / base;
	}
	if ((*max) > 0)
		buffer[(*max)] = bptr[n];
	return (buffer + (*max));
}

char *put_unsnum_cont_to_str(char *buffer, size_t *max,
		char *bptr, unsigned long long n)
{
	size_t base;

	(*max)--;
	base = strlen(bptr);
	while ((n >= base) && ((*max) > 0))
	{
		buffer[(*max)--] = bptr[n % base];
		n = n / base;
	}
	if ((*max) > 0)
		buffer[(*max)] = bptr[n];
	return (buffer + (*max));
}

char *put_num_to_str(char *buffer, size_t *max,
		char *bptr, long long n)
{
	char sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	put_unsnum_to_str(buffer, max, bptr + 1, (unsigned long long) n);
	if ((*max) > 0)
		if ((bptr[0] == '-' || bptr[0] == '+'))
		{
			if (sign)
				buffer[--(*max)] = '-';
			else if (bptr[0] == '+')
				buffer[--(*max)] = '+';
		}
	return (buffer + (*max));
}

char *put_onl_to_str(char *buffer, size_t *max,
		char *bptr, long long n)
{
	char sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	if ((*max) > 0)
		if ((bptr[0] == '-' || bptr[0] == '+'))
		{
			if (sign)
				buffer[--(*max)] = '-';
			else if (bptr[0] == '+')
				buffer[--(*max)] = '+';
		}
	return (buffer + (*max));
}

char *put_unspnum_to_str(char *buffer, size_t *max,
		char *bptr, unsigned long long n)
{
	size_t base;

	(*max)--;
	buffer[(*max)--] = 0;
	base = strlen(bptr);
	while ((n >= base) && ((*max) > 0))
	{
		buffer[(*max)--] = bptr[n % base];
		n = n / base;
	}
	buffer[(*max)] = bptr[n];
	return (buffer + (*max));
}


