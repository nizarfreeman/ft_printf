/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_manager_unsigned_utils_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:35:45 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:52:12 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	count_digits_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

void	put_zeros_unsigned(unsigned int num, int width, int fd, t_flags *flg)
{
	int	digits_count;
	int	zeros;

	digits_count = count_digits_unsigned(num);
	zeros = width - digits_count;
	while (zeros > 0)
	{
		putchar_fd('0', fd, flg);
		zeros--;
	}
}

int	get_precision_zeros_unsigned(unsigned int num, t_flags *flg)
{
	int	digits;
	int	zeros;

	digits = count_digits_unsigned(num);
	if (flg -> precision_width > digits)
		zeros = flg -> precision_width - digits;
	else
		zeros = 0;
	return (zeros);
}

void	handle_precision_spaces_unsigned(unsigned int num,
		t_flags *flg, int *spaces)
{
	int	precision_zeros;

	precision_zeros = get_precision_zeros_unsigned(num, flg);
	*spaces -= precision_zeros;
	if (flg -> precision && num == 0 && !flg -> precision_width)
		(*spaces)++;
}

void	put_spaces_unsigned(unsigned int num, int width, int fd, t_flags *flg)
{
	int	digits_count;
	int	spaces;

	digits_count = count_digits_unsigned(num);
	spaces = width - digits_count;
	if (flg -> precision_width > digits_count)
		spaces -= (flg -> precision_width - digits_count);
	while (spaces > 0)
	{
		putchar_fd(' ', fd, flg);
		spaces--;
	}
}
