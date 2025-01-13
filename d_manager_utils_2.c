/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_manager_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:22:27 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:00:14 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	put_spaces(int num, int width, int fd, t_flags *flg)
{
	int	digits_count;
	int	spaces;

	digits_count = count_digits(num);
	spaces = width - digits_count;
	if (flg -> minus_sign && flg -> plus_sign)
		spaces++;
	if (flg -> minus_sign & flg -> plus_sign && flg -> precision_width
		&& flg -> width && flg -> precision)
		spaces++;
	if (num < 0 || flg -> plus_sign || flg -> space)
		spaces--;
	if (flg -> precision_width > digits_count)
		spaces -= (flg -> precision_width - digits_count);
	if (flg->precision && num == 0 && !flg ->precision_width)
		spaces++;
	while (spaces > 0)
	{
		write(fd, " ", 1);
		flg->len += 1;
		spaces--;
	}
}

void	put_precision_zeros(int num, int fd, t_flags *flg)
{
	int	zeros;

	zeros = get_precision_zeros(num, flg);
	while (zeros > 0)
	{
		write(fd, "0", 1);
		flg -> len += 1;
		zeros--;
	}
}

void	print_number(int num, int fd, t_flags *flg)
{
	long	number;

	number = num;
	if (number < 0)
		number = -number;
	if (!(flg -> precision && number == 0 && !flg -> precision_width))
		putnbr_fd(number, fd, flg);
}

void	put_d_left_padding(t_flags *flg, int fd, int num)
{
	if (!flg -> minus_sign)
	{
		if (flg -> zero && !flg -> precision)
		{
			handle_sign(num, fd, flg);
			put_zeros(num, flg -> width, fd, flg);
		}
		else
		{
			put_spaces(num, flg -> width, fd, flg);
			handle_sign(num, fd, flg);
			put_precision_zeros(num, fd, flg);
		}
	}
	else
	{
		handle_sign(num, fd, flg);
		put_precision_zeros(num, fd, flg);
	}
}
