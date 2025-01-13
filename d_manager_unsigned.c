/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_manager_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:09:47 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/10 17:09:56 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	d_manager_unsigned(unsigned int num, int fd, t_flags *flg)
{
	put_unsigned_left_padding(flg, fd, num);
	print_number_unsigned(num, fd, flg);
	if (flg -> minus_sign)
		put_spaces_unsigned(num, flg -> width, fd, flg);
}
