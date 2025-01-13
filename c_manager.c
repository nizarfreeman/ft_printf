/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_manager.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:21:55 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/12 00:40:13 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	c_manager(char c, int fd, t_flags *flg)
{
	if (!flg -> minus_sign)
		put_spaces_s("n", flg -> width, fd, flg);
	putchar_fd(c, fd, flg);
	if (flg->minus_sign)
		put_spaces_s("n", flg -> width, fd, flg);
}
