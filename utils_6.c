/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:07:41 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:04:27 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	is_flag(char c)
{
	if (c == '+' || c == ' ' || c == '#' || c == '-' || c == '0')
		return (1);
	return (0);
}

int	valid_format(char *s)
{
	if (!s || !*s)
		return (0);
	while (*s && is_flag(*s))
		s++;
	while (*s && *s >= '0' && *s <= '9')
		s++;
	if (*s && *s == '.')
	{
		s++;
		while (*s && *s >= '0' && *s <= '9')
			s++;
	}
	if (*s && is_flag(*s))
		return (0);
	if (*s && catch_specifier(*s))
		return (1);
	return (0);
}

int	handle_percent(char **s, t_flags *flg, int fd)
{
	char	*str;
	int		count;
	int		should_error;
	int		pairs;

	str = *s;
	count = 0;
	should_error = 0;
	while (*str == '%')
	{
		count++;
		str++;
	}
	if (*str == '\0' && (count % 2) == 1)
		should_error = 1;
	pairs = count / 2;
	while (pairs -- > 0)
		putchar_fd('%', fd, flg);
	*s = str - (count % 2);
	if (should_error)
		return (-1);
	return (count % 2);
}
