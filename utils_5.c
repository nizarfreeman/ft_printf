/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:00:16 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:58:21 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	put_format(char c, va_list *r2, t_flags *flg, int fd)
{
	if (!fd)
		return ;
	if (c == 'c')
		c_manager((char)va_arg(*r2, int), fd, flg);
	else if (c == 's')
		s_manager(va_arg(*r2, char *), fd, flg);
	else if (c == 'd' || c == 'i')
		d_manager(va_arg(*r2, long), fd, flg);
	else if (c == 'u')
		d_manager_unsigned(va_arg(*r2, unsigned int), fd, flg);
	else if (c == 'x' || c == 'X')
		xx_manager(va_arg(*r2, unsigned int), fd, flg, c);
	else if (c == 'p')
		p_manager(va_arg(*r2, void *), flg, fd);
}

void	advance_s(char **s)
{
	(*s) += 2;
}

void	put_(char **s, t_flags *flg)
{
	int	fd;

	fd = 1;
	putchar_fd(**s, fd, flg);
	if (!**s)
		return ;
	(*s)++;
}

int	catch_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i'
		|| c == 'u' || c == 'x'
		|| c == 'X')
		return (1);
	return (0);
}

void	skip_width(char **s)
{
	while (**s >= '0' && **s <= '9')
	{
		(*s)++;
	}
}
