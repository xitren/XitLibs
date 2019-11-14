/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#include "circular_printf.h"
#include "circular_functions.h"
#include "circular_printf_parser.h"

void parse_key(t_circular_printf_list *container, t_circular_printf_flags *flags) {
	unsigned int i;
	unsigned int step;

	if (container->content_size == 0)
		return;
	if (((char*) container->content)[0] != '%')
		return;
	i = 0;
	step = 0;
	bzero(flags, sizeof (t_circular_printf_flags));
	while (++i <= container->content_size) {
		check_step1(&step, i, container, flags);
		check_step2(&step, i, container, flags);
		check_step3(&step, i, container, flags);
		if (check_step4(&step, i, container, flags))
			continue;
		if (check_step5(&step, i, container, flags))
			continue;
		if (check_step6(&step, i, container, flags))
			break;
		if (check_step7(&step, i, container, flags))
			break;
	}
}

void find_sub(const char *f, t_circular_printf_list **lst, unsigned int r_s[3]) {
	char flag;

	flag = 0;
	r_s[1] = r_s[0] + 1;
	while ((f[r_s[1]] != 0) && (!(is_sign(f[r_s[1]]) && !is_spec(f[r_s[1]])
			&& !ISPOINT(f[r_s[1]]) && !is_flag(f[r_s[1]]) &&
			!ISDIGIT(f[r_s[1]]) && !flag) && !(flag && is_sign(f[r_s[1]])))) {
		r_s[1]++;
		if (is_spec(f[r_s[1]])) {
			flag = 1;
			if ((f[r_s[1] + 1] == 'h') || (f[r_s[1] + 1] == 'l'))
				r_s[1] += 2;
			else
				r_s[1]++;
		}
	}
	if (f[r_s[1]] == 0)
		return;
	circular_lstend(lst, circular_lstnew_non_cpy(f + r_s[2], r_s[0] - r_s[2]));
	circular_lstend(lst, circular_lstnew_non_cpy(f + r_s[0], r_s[1] - r_s[0] + 1));
	r_s[2] = r_s[1] + 1;
	r_s[0] = r_s[1];
}

t_circular_printf_list *part_to_lst(const char *f) {
	unsigned int r_s[4];
	t_circular_printf_list *lst;

	r_s[0] = 0;
	r_s[2] = 0;
	lst = 0;
	while (f[r_s[0]] != 0) {
		if (f[r_s[0]] == '%')
			find_sub(f, &lst, r_s);
		r_s[0]++;
	}
	circular_lstend(&lst, circular_lstnew_non_cpy(f + r_s[2], r_s[0] - r_s[2]));
	return (lst);
}


