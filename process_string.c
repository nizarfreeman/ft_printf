/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 09:50:35 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:02:42 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	reset_flags(t_flags *flg)
{
	int	len;

	len = flg -> len;
	ft_memset(flg, 0, sizeof(t_flags));
	flg -> len = len;
}

void	handle_format(char **s, t_flags *flg, va_list *r2, int fd)
{
	if (valid_format(*s + 1))
	{
		reset_flags(flg);
		parse_flags(&flg, s);
		if (catch_specifier(*(*s + 1)))
		{
			put_format(*(*s + 1), r2, flg, fd);
			advance_s(s);
		}
	}
	else
	{
		putchar_fd(**s, fd, flg);
		(*s)++;
	}
}

void	process_string_main_loop(char **s, t_flags *flg, va_list *r2, int fd)
{
	int	percent_result;

	while (**s)
	{
		if (**s == '%')
		{
			percent_result = handle_percent(s, flg, fd);
			if (percent_result == -1)
			{
				flg -> len = -1;
				return ;
			}
			if (percent_result == 1)
				handle_format(s, flg, r2, fd);
		}
		else
			put_(s, flg);
	}
}

int	process_string(char *s, va_list r, int fd)
{
	va_list		r2;
	t_flags		*flg;
	int			ret;

	ret = 0;
	flg = malloc(sizeof(t_flags));
	ft_memset(flg, 0, sizeof(t_flags));
	va_copy(r2, r);
	process_string_main_loop(&s, flg, &r2, fd);
	ret = flg -> len;
	free(flg);
	va_end(r2);
	return (ret);
}
