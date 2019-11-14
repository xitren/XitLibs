/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#ifndef circular_FUNCTIONS_H
#define circular_FUNCTIONS_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define F_SHARP  (1 << 0)
#define F_SPACE  (1 << 1)
#define F_PLUS   (1 << 2)
#define F_MINUS  (1 << 3)
#define F_ZERO   (1 << 4)
#define F_SEPARATOR (1 << 5)
#define F_INCLUDE  (1 << 6)
#define F_UPCASE  (1 << 0)
#define F_SHORT  (1 << 1)
#define F_SHORT2  (1 << 2)
#define F_LONG   (1 << 3)
#define F_LONG2  (1 << 4)
#define PF_RED   "\033[31m"
#define PF_GREEN  "\033[32m"
#define PF_YELLOW  "\033[33m"
#define PF_BLUE  "\033[34m"
#define PF_PURPLE  "\033[35m"
#define PF_CYAN  "\033[36m"
#define PF_EOC   "\033[0m"

typedef struct s_list {
	void *content;
	struct s_list *next;
	size_t content_size;
} t_circular_printf_list;

typedef struct s_flags {
	char parameter;
	unsigned char flags;
	unsigned int min_width;
	char min_width_par;
	unsigned int precision;
	char precision_par;
	unsigned char length;
	size_t tt;
} t_circular_printf_flags;

typedef char *(*t_ptrfunc)(char *buff,
				va_list *ap, t_circular_printf_flags *fl);
char *my_put_un(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_perc(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_d(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_i(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_u(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_f(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_x(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_xx(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_o(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_s(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_c(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
char *my_put_p(char *buff,
				va_list *valist, t_circular_printf_flags *fl);
void set_functions(t_ptrfunc g_tab[]);
long long get_signed_varg(va_list *valist, t_circular_printf_flags *fl);
unsigned long long get_unsigned_varg(va_list *valist, t_circular_printf_flags *fl);
long double get_double_varg(va_list *valist, t_circular_printf_flags *fl);
void set_flags_1(char v[2], t_circular_printf_flags *fl);
void set_flags_2(char v[2], t_circular_printf_flags *fl);
void set_flags_3(char v[2], t_circular_printf_flags *fl);
void set_flags_4(char v[2], t_circular_printf_flags *fl);
char *circular_strfix(char *ret);
void get_last(char *p[3], t_circular_printf_flags *fl, unsigned long cnt[5]);
char *put_str_align(char *buff, size_t *max, t_circular_printf_flags *fl);

char is_type(char a);
char is_sign(char a);
char is_flag(char a);
char is_spec(char a);
char *put_unsnum_to_str(char *buffer, size_t *max,
				char *bptr, unsigned long long n);
char *put_unspnum_to_str(char *buffer, size_t *max,
				char *bptr, unsigned long long n);
char *put_unsnum_cont_to_str(char *buffer, size_t *max,
				char *bptr, unsigned long long n);
char *put_num_to_str(char *buffer, size_t *max,
				char *bptr, long long n);
char *put_zeros_to_str(char *buffer, size_t alr,
				size_t *max, size_t prec);
char *put_str_align_right(char *data, size_t alr,
				size_t *max, size_t min_width);
char *put_str_align_left(char *data, size_t alr,
				size_t *max, size_t min_width);
char *put_str_align_zeros(char *buffer, size_t alr,
				size_t *max, size_t prec);
char *get_base10_string(char flag);
char *get_base8_string(char flag);
char *get_base16x_string(char flag);
char *get_base16xx_string(char flag);
char *put_prefix_x_to_str(char *buffer, size_t *max);
char *put_prefix_xx_to_str(char *buffer, size_t *max);
char *put_prefix_x_mod_to_str(char *buffer, size_t *max);
char *put_prefix_xx_mod_to_str(char *buffer, size_t *max);
char *put_prefix_0_to_str(char *buffer, size_t *max);
char *put_double_to_str(char *buffer, size_t *max,
				double n, char *bptr);
char *put_mantissa_to_str(char *buffer, size_t *max,
				double n, size_t prec);
char *put_str_space_before(char *buffer, size_t *max,
				char f);
char *put_onl_to_str(char *buffer, size_t *max,
				char *bptr, long long n);

void circular_lstremove(t_circular_printf_list **alst, t_circular_printf_list *item);
t_circular_printf_list *circular_lstnew(void const *content, size_t content_size);
t_circular_printf_list *circular_lstnew_non_cpy(void const *content,
				size_t content_size);
void circular_lstiter(t_circular_printf_list *lst, void (*f)(t_circular_printf_list *elem));
void circular_lstdelone(t_circular_printf_list **alst, void (*del)(void *, size_t));
void circular_lstdel(t_circular_printf_list **alst, void (*del)(void *, size_t));
void circular_lstadd(t_circular_printf_list **alst, t_circular_printf_list * new);
void circular_lstend(t_circular_printf_list **alst, t_circular_printf_list * new);
void circular_lstfree(t_circular_printf_list **alst);

char *get_not(char *buff, size_t *max, double pre_calcs);

#endif






