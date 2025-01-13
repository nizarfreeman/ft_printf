/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_manager_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:30:52 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:54:52 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	count_pointer_digits(unsigned long num)
{
	int	length;

	length = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 16;
		length++;
	}
	return (length);
}

void	print_hex_pointer(unsigned long addr, int fd, t_flags *flg)
{
	char	*hex;
	char	buffer[16];
	int		i;

	hex = "0123456789abcdef";
	i = 0;
	if (addr == 0)
	{
		putchar_fd('0', fd, flg);
		return ;
	}
	while (addr > 0)
	{
		buffer[i++] = hex[addr % 16];
		addr /= 16;
	}
	while (--i >= 0)
	{
		write(fd, &buffer[i], 1);
		flg -> len++;
	}
}

int	get_pointer_length(void *p, t_flags *flg)
{
	unsigned long	len;
	unsigned long	digits;
	unsigned long	addr;

	if (p == NULL)
		return (5);
	addr = (unsigned long)p;
	digits = count_pointer_digits(addr);
	len = 2;
	if (flg -> precision && flg -> precision_width > (int)digits)
		len += flg -> precision_width;
	else
		len += digits;
	if (flg -> plus_sign || flg -> space)
		len++;
	return (len);
}

void	put_pointer_prefix(t_flags *flg, int fd)
{
	if (flg -> plus_sign)
		putchar_fd('+', fd, flg);
	else if (flg->space)
		putchar_fd(' ', fd, flg);
}

void	put_pointer_precision(unsigned long addr, t_flags *flg, int fd)
{
	int	digits;
	int	zeros;

	digits = count_pointer_digits(addr);
	if (flg -> precision && flg -> precision_width > digits)
	{
		zeros = flg -> precision_width - digits;
		while (zeros--)
			putchar_fd('0', fd, flg);
	}
}
