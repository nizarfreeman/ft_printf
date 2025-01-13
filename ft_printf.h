/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:20:28 by nfaska            #+#    #+#             */
/*   Updated: 2025/01/12 00:39:48 by nfaska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_flags_struct
{
	int	plus_sign;
	int	minus_sign;
	int	space;
	int	hash;
	int	precision;
	int	precision_width;
	int	zero;
	int	width;
	int	len;
}	t_flags;

void	reset_flags(t_flags *flg);
void	skip_spaces(const char	**s);
void	sign_check(const char **s, int *flag, int *double_sign);
void	*ft_memset(void *s, int c, size_t n);
void	putchar_fd(char c, int fd, t_flags *flg);
void	putnbr_fd(long long n, int fd, t_flags *flg);
void	putnbr_fd_unsigned(unsigned int n, int fd, t_flags *flg);
void	putstr_fd(char *s, int fd, t_flags *flg);
void	put_hex(unsigned int num, int fd, t_flags *flg);
void	put_hex_up(unsigned int num, int fd, t_flags *flg);
void	put_hex_address(unsigned long i, int fd, t_flags *flg);
void	put_address(void *p, int fd, t_flags *flg);
void	d_manager_unsigned(unsigned int num, int fd, t_flags *flg);
void	put_format(char c, va_list *r2, t_flags *flg, int fd);
void	advance_s(char **s);
void	put_(char **s, t_flags *flg);
void	skip_width(char **s);
void	xx_manager(unsigned int num, int fd, t_flags *flg, char c);
void	put_precision_zeros_hex(unsigned int num, int fd, t_flags *flg);
void	put_spaces_hex(unsigned int num, int width, int fd, t_flags *flg);
void	put_padding(int length, int fd, t_flags *flg, char pad_char);
void	handle_hash_prefix(unsigned int num, int fd, t_flags *flg, char format);
void	put_hex_left_padding(t_flags *flg, int fd, unsigned int num, char c);
void	_put_hex(unsigned int num, int fd, t_flags *flg, char format);
void	c_manager(char c, int fd, t_flags *flg);
void	d_manager(int num, int fd, t_flags *flg);
void	put_zeros_unsigned(unsigned int num, int width, int fd, t_flags *flg);
void	handle_precision_spaces_unsigned(unsigned int num,
			t_flags *flg, int *spaces);
void	put_spaces_unsigned(unsigned int num, int width, int fd, t_flags *flg);
void	put_precision_zeros_unsigned(unsigned int num, int fd, t_flags *flg);
void	print_number_unsigned(unsigned int num, int fd, t_flags *flg);
void	put_unsigned_left_padding(t_flags *flg, int fd, unsigned int num);
void	put_zeros(int num, int width, int fd, t_flags *flg);
void	handle_sign(int num, int fd, t_flags *flg);
void	handle_precision_spaces(int num, t_flags *flg, int *spaces);
void	put_spaces(int num, int width, int fd, t_flags *flg);
void	put_precision_zeros(int num, int fd, t_flags *flg);
void	print_number(int num, int fd, t_flags *flg);
void	put_d_left_padding(t_flags *flg, int fd, int num);
void	parse_precision(char **s, t_flags **flg, int *is_first_num);
void	parse_other_flags(char **s, t_flags **flg, int *is_first_num);
void	parse_flags(t_flags **flg, char **s);
void	p_manager(void *p, t_flags *flg, int fd);
void	print_hex_pointer(unsigned long addr, int fd, t_flags *flg);
void	put_pointer_prefix(t_flags *flg, int fd);
void	put_pointer_precision(unsigned long addr, t_flags *flg, int fd);
void	put_pointer(void *p, int fd, t_flags *flg);
void	handle_format(char **s, t_flags *flg, va_list *r2, int fd);
void	process_string_main_loop(char **s, t_flags *flg, va_list *r2, int fd);
void	s_manager(char *s, int fd, t_flags *flg);
void	put_spaces_s(char *s, int width, int fd, t_flags *flg);
void	putstr_fd_prec(char *s, int fd, t_flags *flg);

int		ll_check(unsigned long long res, int flag);
int		ft_atoi(const char *s);
int		catch_specifier(char c);
int		count_digits(int n);
int		count_expec_hex_chars(int num);
int		is_flag(char c);
int		valid_format(char *s);
int		handle_percent(char **s, t_flags *flg, int fd);
int		count_hex_digits(unsigned int num);
int		get_precision_zeros_hex(unsigned int num, t_flags *flg);
int		count_digits_unsigned(unsigned int n);
int		get_precision_zeros_unsigned(unsigned int num, t_flags *flg);
int		get_digit_count(int num);
int		get_precision_zeros(int num, t_flags *flg);
int		parse_width(char **s, t_flags **flg, int *is_first_num);
int		loop_condition(char **s, int *is_first_num);
int		ft_printf(char *s, ...);
int		count_pointer_digits(unsigned long num);
int		get_pointer_length(void *p, t_flags *flg);
int		process_string(char *s, va_list r, int fd);

size_t	ft_strlen(const char *s);

#endif
