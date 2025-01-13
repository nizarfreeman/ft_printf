/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_manager.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:21:06 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 15:05:22 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	s_manager(char *s, int fd, t_flags *flg)
{
	if (flg -> precision && flg -> precision_width == 0)
	{
		put_spaces_s(s, flg -> width, fd, flg);
		return ;
	}
	if (!flg -> minus_sign)
		put_spaces_s(s, flg -> width, fd, flg);
	putstr_fd_prec(s, fd, flg);
	if (flg -> minus_sign)
		put_spaces_s(s, flg -> width, fd, flg);
}
