/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_functions.h"
#include "circular_printf.h"
#include <stdio.h>

static void	*memalloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (0);
	ptr = malloc(size);
	if (!ptr)
		return (0);
	bzero(ptr, size);
	return (ptr);
}

t_circular_printf_list	*circular_lstnew_non_cpy(void const *content, size_t content_size)
{
	t_circular_printf_list	*new;

	new = (t_circular_printf_list*)memalloc(sizeof(t_circular_printf_list));
	if (!new)
		return (0);
	if (content)
	{
		new->content = (void *)content;
		new->content_size = content_size;
	}
	return (new);
}

void	circular_lstremove(t_circular_printf_list **alst, t_circular_printf_list *item)
{
	t_circular_printf_list	*new;
	t_circular_printf_list	*top;

	if (!alst || !item)
		return ;
	if (!(*alst))
		return ;
	new = 0;
	top = *alst;
	while (top)
	{
		if (top == item)
			break ;
		new = top;
		top = top->next;
	}
	if (new)
		new->next = top->next;
	else
		*alst = top->next;
	free(top);
}

t_circular_printf_list	*circular_lstnew(void const *content, size_t content_size)
{
	t_circular_printf_list	*new;

	new = (t_circular_printf_list*)memalloc(sizeof(t_circular_printf_list));
	if (!new)
		return (0);
	if (content)
	{
		new->content = memalloc(content_size);
		if (!(new->content))
		{
			free(new);
			return (0);
		}
		memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	return (new);
}

void		circular_lstfree(t_circular_printf_list **alst)
{
	t_circular_printf_list		*tmplst;

	if (!alst)
		return ;
	while (*alst)
	{
		tmplst = (*alst)->next;
		free(*alst);
		*alst = tmplst;
	}
	*alst = 0;
}


void	circular_lstend(t_circular_printf_list **alst, t_circular_printf_list *new)
{
	t_circular_printf_list *pre;
	t_circular_printf_list *lst;

	if (!new)
		return ;
	if (!*alst)
	{
		(*alst) = new;
		return ;
	}
	lst = (*alst);
	while (lst)
	{
		pre = lst;
		lst = lst->next;
	}
	pre->next = new;
}


void	circular_lstdelone(t_circular_printf_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !del)
		return ;
	if (!(*alst))
		return ;
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = 0;
}


void		circular_lstdel(t_circular_printf_list **alst, void (*del)(void*, size_t))
{
	t_circular_printf_list		*tmplst;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		tmplst = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = tmplst;
	}
	*alst = NULL;
}

void	circular_lstadd(t_circular_printf_list **alst, t_circular_printf_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

static unsigned long	strnchr(const char *s, int c, size_t size)
{
	unsigned long	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0 && size--)
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (0);
}

int	circular_lstchr(t_circular_printf_list *lst, char ch, size_t *xy)
{
	size_t	sr;
	size_t	r;

	sr = 0;
	while (lst)
	{
		if ((r = strnchr(lst->content, ch, lst->content_size + 1))
				|| (((char *)lst->content)[0] == '\n'))
		{
			sr += r;
			*xy = sr;
			return (1);
		}
		sr += lst->content_size;
		lst = lst->next;
	}
	*xy = sr;
	return (0);
}


void				set_functions(t_ptrfunc g_tab[])
{
	g_tab['%'] = &my_put_perc;
	g_tab['d'] = &my_put_d;
	g_tab['i'] = &my_put_d;
	g_tab['u'] = &my_put_u;
	g_tab['f'] = &my_put_f;
	g_tab['x'] = &my_put_x;
	g_tab['X'] = &my_put_xx;
	g_tab['o'] = &my_put_o;
	g_tab['s'] = &my_put_s;
	g_tab['c'] = &my_put_c;
	g_tab['p'] = &my_put_p;
}

long long			get_signed_varg(va_list *valist, t_circular_printf_flags *fl)
{
	if ((fl->length & F_SHORT) && (fl->length & F_SHORT2))
		return (long long)((char)va_arg(*valist, int));
	if ((fl->length & F_SHORT))
		return (long long)((short)va_arg(*valist, int));
	if ((fl->length & F_LONG))
		return (long long)va_arg(*valist, long int);
	if ((fl->length & F_LONG) && (fl->length & F_LONG2))
		return (long long)va_arg(*valist, long long int);
	return (long long)va_arg(*valist, int);
}

unsigned long long	get_unsigned_varg(va_list *valist, t_circular_printf_flags *fl)
{
	if ((fl->length & F_SHORT) && (fl->length & F_SHORT2))
		return (long long)((unsigned char)va_arg(*valist, unsigned int));
	if ((fl->length & F_SHORT))
		return (long long)((unsigned short)va_arg(*valist, unsigned int));
	if ((fl->length & F_LONG))
		return (long long)va_arg(*valist, unsigned long int);
	if ((fl->length & F_LONG) && (fl->length & F_LONG2))
		return (long long)va_arg(*valist, unsigned long long int);
	return (long long)va_arg(*valist, unsigned int);
}

long double			get_double_varg(va_list *valist, t_circular_printf_flags *fl)
{
	if ((fl->length & F_UPCASE))
		return (long double)va_arg(*valist, long double);
	return (long double)va_arg(*valist, double);
}

char				*my_put_un(char *buff, va_list *valist, t_circular_printf_flags *fl)
{
	size_t	max;
	char	*p;

	max = BUFF_PRINT - 1;
	buff[(max)--] = 0;
	buff[(max)] = fl->parameter;
	if ((fl->min_width_par == 1) && (fl->flags & (F_ZERO))
			&& !(fl->flags & (F_MINUS)))
	{
		p = put_str_align_zeros(buff, 0, &max, fl->min_width);
	}
	if (fl->flags & F_MINUS)
		p = put_str_align_left(buff, 0, &max, fl->min_width);
	else
		p = put_str_align_right(buff, 0, &max, fl->min_width);
	fl = (t_circular_printf_flags *)valist;
	valist = (va_list *)fl;
	return (p);
}










