/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_manager.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:56:09 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:04:44 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	p_manager(void *p, t_flags *flg, int fd)
{
	int		len;
	char	pad_char;

	if (!p)
		flg -> zero = 0;
	len = get_pointer_length(p, flg);
	if (flg -> zero && !flg -> precision && !flg -> minus_sign)
		pad_char = '0';
	else
		pad_char = ' ';
	if (pad_char != '0')
		put_pointer_prefix(flg, fd);
	if (!flg -> minus_sign)
		put_padding(len, fd, flg, pad_char);
	if (pad_char == '0')
		put_pointer_prefix(flg, fd);
	put_pointer(p, fd, flg);
	if (flg -> minus_sign)
		put_padding(len, fd, flg, ' ');
}
