/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"
#include "circular_functions.h"
#include "circular_printf_parser.h"
#include <unistd.h>

static void ft_putstrnn(circular_buff_t* r_buff, char const *s, size_t n)
{
	if (s)
	{
		if (n)
			circular_buff_write(r_buff, s, n);
		else
			circular_buff_write(r_buff, s, strlen(s));
	}
}

static void ft_putstr(circular_buff_t* r_buff, char const *s)
{
	if (s)
		circular_buff_write(r_buff, s, strlen(s));
}

static void ft_lstprint(circular_buff_t* r_buff, t_circular_printf_list *lst)
{
	circular_buff_write(r_buff, ((char*) lst->content), lst->content_size);
}

static void run_lst(circular_buff_t* r_buff,
		t_circular_printf_list *lst, t_ptrfunc g_tab[],
		va_list *valist)
{
	t_circular_printf_flags flags;
	char buff[BUFF_PRINT];
	char *p;

	while (lst != 0)
	{
		bzero(&flags, sizeof (t_circular_printf_flags));
		parse_key(lst, &flags);
		if (flags.parameter != 0)
		{
			if (g_tab[(int) flags.parameter] != 0)
			{
				p = (g_tab[(int) flags.parameter])(buff, valist, &flags);
				ft_putstrnn(r_buff, p, flags.tt);
			} else
			{
				p = my_put_un(buff, valist, &flags);
				ft_putstr(r_buff, p);
			}
		} else
			ft_lstprint(r_buff, lst);
		lst = lst->next;
	}
}

int circular_printf(circular_buff_t* buff, const char *format, ...)
{
	t_circular_printf_list *lst;
	t_ptrfunc g_tab[255];
	va_list valist;

	lst = 0;
	bzero(g_tab, sizeof (g_tab));
	set_functions(g_tab);
	va_start(valist, format);
	lst = part_to_lst(format);
	run_lst(buff, lst, g_tab, &valist);
	circular_lstfree(&lst);
	va_end(valist);
	return (0);
}






















