/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#ifndef circular_PRINTF_PARSER_H
# define circular_PRINTF_PARSER_H

# include "circular_functions.h"

char	check_step1(unsigned int *step, unsigned int i,
				t_circular_printf_list *container, t_circular_printf_flags *flags);
char	check_step2(unsigned int *step, unsigned int i,
				t_circular_printf_list *container, t_circular_printf_flags *flags);
char	check_step3(unsigned int *step, unsigned int i,
				t_circular_printf_list *container, t_circular_printf_flags *flags);
char	check_step4(unsigned int *step, unsigned int i,
				t_circular_printf_list *container, t_circular_printf_flags *flags);
char	check_step5(unsigned int *step, unsigned int i,
				t_circular_printf_list *container, t_circular_printf_flags *flags);
char	check_step6(unsigned int *step, unsigned int i,
				t_circular_printf_list *container, t_circular_printf_flags *flags);
char	check_step7(unsigned int *step, unsigned int i,
				t_circular_printf_list *container, t_circular_printf_flags *flags);
void	parse_key(t_circular_printf_list *container, t_circular_printf_flags *flags);
void	find_sub(const char *f, t_circular_printf_list **lst, unsigned int r_s[3]);
t_circular_printf_list	*part_to_lst(const char *f);

#endif


