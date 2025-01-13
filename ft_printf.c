/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:52:11 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 10:55:51 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printf(char *s, ...)
{
	va_list		r;
	int			len;
	int			fd;

	fd = 1;
	if (!s)
		return (-1);
	va_start(r, s);
	len = process_string(s, r, fd);
	va_end(r);
	return (len);
}
