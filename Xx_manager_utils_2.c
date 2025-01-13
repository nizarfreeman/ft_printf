/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xx_manager_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:13:40 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:59:20 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	handle_hash_prefix(unsigned int num, int fd, t_flags *flg, char format)
{
	if (flg -> hash && num != 0)
	{
		if (format == 'x')
			write(fd, "0x", 2);
		else
			write(fd, "0X", 2);
		flg -> len += 2;
	}
}

void	put_hex_left_padding(t_flags *flg, int fd, unsigned int num, char c)
{
	char	pad_char;
	int		digits;
	int		padding;

	digits = count_hex_digits(num);
	padding = flg -> width - digits;
	if (flg->precision_width > digits)
		padding -= (flg -> precision_width - digits);
	if (flg->hash && num != 0)
		padding -= 2;
	pad_char = ' ';
	if (flg -> zero && !flg -> precision && !flg -> minus_sign)
		pad_char = '0';
	if (pad_char == '0' && flg -> hash && num != 0)
		handle_hash_prefix(num, fd, flg, c);
	if (!flg -> minus_sign)
	{
		while (padding-- > 0)
			putchar_fd(pad_char, fd, flg);
	}
	if (pad_char == ' ' && flg->hash && num != 0)
		handle_hash_prefix(num, fd, flg, c);
	put_precision_zeros_hex(num, fd, flg);
}

void	_put_hex(unsigned int num, int fd, t_flags *flg, char format)
{
	if (format == 'x')
		put_hex(num, fd, flg);
	else if (format == 'X')
		put_hex_up(num, fd, flg);
}
