/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:02:22 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/11 14:53:03 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	parse_width(char **s, t_flags **flg, int *is_first_num)
{
	if (**s >= '1' && **s <= '9' && *is_first_num)
	{
		(*flg)->width = ft_atoi(*s);
		skip_width(s);
		*is_first_num = 0;
		return (1);
	}
	return (0);
}

void	parse_precision(char **s, t_flags **flg, int *is_first_num)
{
	(*flg)->precision = 1;
	(*s)++;
	if (**s >= '0' && **s <= '9')
	{
		(*flg)->precision_width = ft_atoi(*s);
		skip_width(s);
		(*s)--;
	}
	*is_first_num = 0;
}

void	parse_other_flags(char **s, t_flags **flg, int *is_first_num)
{
	if (**s == '+')
		(*flg)->plus_sign = 1;
	else if (**s == ' ')
		(*flg)->space = 1;
	else if (**s == '#')
		(*flg)->hash = 1;
	else if (**s == '-')
		(*flg)->minus_sign = 1;
	else if (**s == '0' && is_first_num)
		(*flg)->zero = 1;
}

int	loop_condition(char **s, int *is_first_num)
{
	if (**s && (**s == '+' || **s == ' ' || **s == '#'
			|| **s == '-' || **s == '.' || **s == '0'
			|| (is_first_num && **s >= '1' && **s <= '9')))
		return (1);
	return (0);
}

void	parse_flags(t_flags **flg, char **s)
{
	int	is_first_num;

	is_first_num = 1;
	(*s)++;
	while (loop_condition(s, &is_first_num))
	{
		if (parse_width(s, flg, &is_first_num))
			continue ;
		parse_other_flags(s, flg, &is_first_num);
		if (**s == '.')
		{
			parse_precision(s, flg, &is_first_num);
			continue ;
		}
		(*s)++;
	}
	if (**s >= '0' && **s <= '9' && !(*flg)->width)
	{
		(*flg)->width = ft_atoi(*s);
		skip_width(s);
	}
	(*s)--;
}
