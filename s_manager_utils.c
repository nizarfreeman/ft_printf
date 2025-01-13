/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_manager_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:15:51 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:55:25 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	put_spaces_s(char *s, int width, int fd, t_flags *flg)
{
	int	spaces;
	int	str_len;

	if (!s)
		str_len = 6;
	else
		str_len = ft_strlen(s);
	if (!s && flg -> precision && flg -> precision_width < 6)
		str_len = 0;
	else if (flg -> precision && flg -> precision_width >= 0
		&& flg -> precision_width < str_len)
		str_len = flg -> precision_width;
	spaces = width - str_len;
	if (spaces > 0)
	{
		while (spaces > 0)
		{
			putchar_fd(' ', fd, flg);
			spaces--;
		}
	}
}

void	putstr_fd_prec(char *s, int fd, t_flags *flg)
{
	int	i;

	if (!s)
	{
		if (!flg -> precision || flg -> precision_width >= 6)
			putstr_fd("(null)", fd, flg);
		return ;
	}
	i = 0;
	if (flg -> precision && flg -> precision_width >= 0)
	{
		while (s[i] && i < flg -> precision_width)
		{
			putchar_fd(s[i], fd, flg);
			i++;
		}
	}
	else
		putstr_fd(s, fd, flg);
}
