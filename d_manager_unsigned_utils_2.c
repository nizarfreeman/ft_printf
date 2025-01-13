/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_manager_unsigned_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:08:50 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:57:41 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	put_precision_zeros_unsigned(unsigned int num, int fd, t_flags *flg)
{
	int	zeros;

	zeros = get_precision_zeros_unsigned(num, flg);
	while (zeros > 0)
	{
		putchar_fd('0', fd, flg);
		zeros--;
	}
}

void	print_number_unsigned(unsigned int num, int fd, t_flags *flg)
{
	if (!(flg -> precision && num == 0 && !flg -> precision_width))
		putnbr_fd_unsigned(num, fd, flg);
}

void	put_unsigned_left_padding(t_flags *flg, int fd, unsigned int num)
{
	if (!flg -> minus_sign)
	{
		if (flg -> zero && !flg -> precision)
			put_zeros_unsigned(num, flg -> width, fd, flg);
		else
		{
			put_spaces_unsigned(num, flg -> width, fd, flg);
			put_precision_zeros_unsigned(num, fd, flg);
		}
	}
	else
		put_precision_zeros_unsigned(num, fd, flg);
}
