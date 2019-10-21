/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"
#include "circular_functions.h"

static long double	circular_pow10(unsigned int p)
{
	long double ret;

	ret = 1;
	while (p--)
		ret *= 10;
	return (ret);
}

void	fix_mantissa(double *mant, double end,
	size_t prec, unsigned long long *nmant)
{
	if (end > 0.5)
	{
		if (++(*nmant) >= circular_pow10(prec))
		{
			(*nmant) = 0;
			++(*mant);
		}
	}
	else if (end < 0.5)
		;
	else if (((*nmant) == 0U)
		|| ((*nmant) & 1U))
		++(*nmant);
}

char	*put_mantissa_to_str(char *buffer, size_t *max,
		double n, size_t prec)
{
	double				mant;
	double				end;
	unsigned long long	nmant;
	size_t				old[2];

	old[0] = *max;
	old[1] = prec;
	while ((prec-- > 16))
		buffer[(*max)--] = '0';
	(*max)++;
	mant = (n - (long long)n) * circular_pow10(prec);
	nmant = (unsigned long long)mant;
	end = mant - nmant;
	fix_mantissa(&mant, end, prec, &nmant);
	put_unsnum_cont_to_str(buffer, max, "0123456789", nmant);
	while (((old[1] - 1) > (old[0] - (*max) + 1)))
		buffer[--(*max)] = '0';
	return (buffer + (*max));
}

char	*put_double_to_str(char *buffer, size_t *max,
		double n, char *bptr)
{
	char	sign;

	sign = 0;
	if (n < +0.0)
	{
		sign = 1;
		n = -n;
	}
	put_unsnum_cont_to_str(buffer, max, bptr + 1, (unsigned long long)n);
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

char	*put_zeros_to_str(char *buffer, size_t alr, size_t *max, size_t prec)
{
	char	sign;

	sign = buffer[(*max)];
	if (alr == 0)
	{
		if ((sign == '-' || sign == '+'))
			alr = strlen(buffer + (*max) + 1);
		else
			alr = strlen(buffer + (*max));
	}
	if (prec > alr)
		prec -= alr;
	else
		return (buffer + (*max));
	if (!(buffer[(*max)] == '-' || buffer[(*max)] == '+'))
		(*max)--;
	while ((prec-- > 0) && ((*max) > 0))
		buffer[(*max)--] = '0';
	if ((sign == '-' || sign == '+'))
		buffer[(*max)--] = sign;
	return (buffer + ++(*max));
}






