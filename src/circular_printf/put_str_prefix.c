/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"

char *put_prefix_x_to_str(char *buffer, size_t *max)
{
	if ((*max) > 0)
		buffer[--(*max)] = 'x';
	if ((*max) > 0)
		buffer[--(*max)] = '0';
	return (buffer + (*max));
}

char *put_prefix_xx_to_str(char *buffer, size_t *max)
{
	if ((*max) > 0)
		buffer[--(*max)] = 'X';
	if ((*max) > 0)
		buffer[--(*max)] = '0';
	return (buffer + (*max));
}

char *put_prefix_xx_mod_to_str(char *buffer, size_t *max)
{
	char *p;

	p = buffer + (*max) - 1;
	while (*(++p) != 0)
		if ((*p) == 'X')
			(*p) = '0';
	if (buffer[(*max)] == '0')
	{
		++(*max);
		if (buffer[(*max)] == '0' || buffer[(*max)] == 'X')
			++(*max);
	}
	if ((*max) > 0)
		buffer[--(*max)] = 'X';
	if ((*max) > 0)
		buffer[--(*max)] = '0';
	return (buffer + (*max));
}

char *put_prefix_x_mod_to_str(char *buffer, size_t *max)
{
	char *p;

	p = buffer + (*max) - 1;
	while (*(++p) != 0)
		if ((*p) == 'x')
			(*p) = '0';
	if (buffer[(*max)] == '0' && buffer[(*max) + 1] != 0)
	{
		++(*max);
		if (buffer[(*max)] == '0' || buffer[(*max)] == 'x')
			++(*max);
	}
	if ((*max) > 0)
		buffer[--(*max)] = 'x';
	if ((*max) > 0)
		buffer[--(*max)] = '0';
	return (buffer + (*max));
}

char *put_prefix_0_to_str(char *buffer, size_t *max)
{
	if ((buffer[(*max)] != '0') && ((*max) > 0))
		buffer[--(*max)] = '0';
	return (buffer + (*max));
}



