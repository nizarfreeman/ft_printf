/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_manager.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:32:37 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:59:35 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	d_manager(int num, int fd, t_flags *flg)
{
	put_d_left_padding(flg, fd, num);
	print_number(num, fd, flg);
	if (flg -> minus_sign)
		put_spaces(num, flg -> width, fd, flg);
}
