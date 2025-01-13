/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:13:27 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:03:40 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	putchar_fd(char c, int fd, t_flags *flg)
{
	write(fd, &c, 1);
	flg -> len += 1;
}

void	putnbr_fd(long long n, int fd, t_flags *flg)
{
	long long	num;

	num = n;
	if (num < 0)
	{
		putchar_fd('-', fd, flg);
		num *= -1;
	}
	if (num >= 10)
		putnbr_fd(num / 10, fd, flg);
	putchar_fd((num % 10) + '0', fd, flg);
}

void	putnbr_fd_unsigned(unsigned int n, int fd, t_flags *flg)
{
	if (n >= 10)
		putnbr_fd_unsigned(n / 10, fd, flg);
	putchar_fd((n % 10) + '0', fd, flg);
}

void	putstr_fd(char *s, int fd, t_flags *flg)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		flg -> len += 6;
		return ;
	}
	while (*s)
	{
		putchar_fd(*s, fd, flg);
		s++;
	}
}
