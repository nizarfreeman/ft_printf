/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xx_manager_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:23:15 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:56:26 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	count_hex_digits(unsigned int num)
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

int	get_precision_zeros_hex(unsigned int num, t_flags *flg)
{
	int	digits;
	int	zeros;

	digits = count_hex_digits(num);
	if (flg -> precision_width > digits)
		zeros = flg -> precision_width - digits;
	else
		zeros = 0;
	return (zeros);
}

void	put_precision_zeros_hex(unsigned int num, int fd, t_flags *flg)
{
	int	zeros;

	zeros = get_precision_zeros_hex(num, flg);
	while (zeros > 0)
	{
		putchar_fd('0', fd, flg);
		zeros--;
	}
}

void	put_spaces_hex(unsigned int num, int width, int fd, t_flags *flg)
{
	int	digits;
	int	spaces;

	digits = count_hex_digits(num);
	spaces = width - digits;
	if (flg -> precision_width > digits)
		spaces -= (flg -> precision_width - digits);
	if (flg -> hash && num != 0)
		spaces -= 2;
	while (spaces > 0)
	{
		putchar_fd(' ', fd, flg);
		spaces--;
	}
}

void	put_padding(int length, int fd, t_flags *flg, char pad_char)
{
	int	padding;

	padding = 0;
	if (flg -> width > length)
		padding = flg -> width - length;
	while (padding > 0)
	{
		putchar_fd(pad_char, fd, flg);
		padding--;
	}
}
