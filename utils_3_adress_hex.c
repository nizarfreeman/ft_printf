/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_adress_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:15:21 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:05:58 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	put_hex(unsigned int num, int fd, t_flags *flg)
{
	char	*s;

	s = "0123456789abcdef";
	if (num > 15)
		put_hex(num / 16, fd, flg);
	putchar_fd(s[num % 16], fd, flg);
}

void	put_hex_up(unsigned int num, int fd, t_flags *flg)
{
	char	*s;

	s = "0123456789ABCDEF";
	if (num > 15)
		put_hex_up(num / 16, fd, flg);
	putchar_fd(s[num % 16], fd, flg);
}

void	put_hex_address(unsigned long i, int fd, t_flags *flg)
{
	char	*s;

	s = "0123456789abcdef";
	if (i > 15)
		put_hex_address(i / 16, fd, flg);
	putchar_fd(s[i % 16], fd, flg);
}

void	put_address(void *p, int fd, t_flags *flg)
{
	unsigned long	a;

	if (p == NULL)
	{
		write(fd, "(nil)", 5);
		flg -> len += 5;
		return ;
	}
	a = (unsigned long)p;
	write(fd, "0x", 2);
	flg -> len += 2;
	put_hex_address(a, fd, flg);
}
