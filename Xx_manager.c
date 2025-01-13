/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xx_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:25:56 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:06:39 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	xx_manager(unsigned int num, int fd, t_flags *flg, char c)
{
	if (flg -> precision && num == 0 && flg -> precision_width == 0)
	{
		put_padding(0, fd, flg, ' ');
		return ;
	}
	put_hex_left_padding(flg, fd, num, c);
	if (!(flg -> precision && num == 0 && !flg -> precision_width))
		_put_hex(num, fd, flg, c);
	if (flg -> minus_sign)
		put_spaces_hex(num, flg -> width, fd, flg);
}
