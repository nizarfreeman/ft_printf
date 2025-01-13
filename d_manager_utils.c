/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_manager_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:19:06 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/10 16:21:38 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	get_digit_count(int num)
{
	int	digits_count;

	if (num < 0)
		num = -num;
	digits_count = count_digits(num);
	return (digits_count);
}

void	put_zeros(int num, int width, int fd, t_flags *flg)
{
	int	digits_count;
	int	zeros;

	digits_count = get_digit_count(num);
	zeros = width - digits_count;
	if (num < 0)
		zeros--;
	while (zeros > 0)
	{
		write(fd, "0", 1);
		flg -> len += 1;
		zeros--;
	}
}

void	handle_sign(int num, int fd, t_flags *flg)
{
	if (num < 0)
	{
		write(fd, "-", 1);
		flg -> len += 1;
	}
	else if (flg -> plus_sign)
	{
		write(fd, "+", 1);
		flg -> len += 1;
		flg -> width--;
	}
	else if (flg -> space)
	{
		write(fd, " ", 1);
		flg -> len += 1;
		flg -> width--;
	}
}

int	get_precision_zeros(int num, t_flags *flg)
{
	int	digits;
	int	zeros;

	digits = get_digit_count(num);
	if (flg -> precision_width > digits)
		zeros = flg -> precision_width - digits;
	else
		zeros = 0;
	return (zeros);
}

void	handle_precision_spaces(int num, t_flags *flg, int *spaces)
{
	int	precision_zeros;

	precision_zeros = get_precision_zeros(num, flg);
	*spaces -= precision_zeros;
	if (flg -> precision && num == 0 && !flg -> precision_width)
		(*spaces)++;
}
