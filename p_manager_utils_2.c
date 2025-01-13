/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_manager_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:51:34 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:57:56 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	put_pointer(void *p, int fd, t_flags *flg)
{
	unsigned long	addr;

	if (p == NULL)
	{
		putstr_fd("(nil)", fd, flg);
		return ;
	}
	addr = (unsigned long)p;
	putstr_fd("0x", fd, flg);
	put_pointer_precision(addr, flg, fd);
	if (!(flg -> precision && addr == 0 && flg -> precision_width == 0))
		print_hex_pointer(addr, fd, flg);
}
