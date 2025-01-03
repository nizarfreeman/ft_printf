#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
# define L_MAX 9223372036854775807ULL
# define L_MIN 9223372036854775808ULL

typedef struct flags_struct
{
	int	plus_sign;
	int	minus_sign;
	int	space;
	int	hash;
	int	precision;
	int	zero;
	int	width;
	int len;
}	flags;

/* === atoi == */

static void	skip_spaces(const char	**s)
{
	while ((**s >= 9 && **s <= 13) || **s == ' ')
		(*s)++;
}

static void	sign_check(const char **s, int *flag, int *double_sign)
{
	if (**s == '-' || **s == '+')
	{
		if (*(*s + 1) == '+' || (*(*s + 1)) == '-')
		{
			*double_sign = 1;
			return ;
		}
		if (**s == '-')
			*flag = 1;
		(*s)++;
	}
}

static int	ll_check(unsigned long long res, int flag)
{
	if (res > L_MAX)
	{
		if (flag == 1)
			return (0);
		else
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *s)
{
	unsigned long long	res;
	int					flag;
	int					double_sign;
	int					check;

	flag = 0;
	double_sign = 0;
	skip_spaces(&s);
	sign_check(&s, &flag, &double_sign);
	if (double_sign)
		return (0);
	res = 0;
	check = 0;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		check = ll_check(res, flag);
		if (check != 1)
			return (check);
		s++;
	}
	if (flag)
		return ((int)(-res));
	return ((int)res);
}

size_t	ft_strlen(const char *s)
{
	const char	*p;

	if (!s)
		return (0);
	p = s;
	while (*s)
		s++;
	return (s - p);
}

/* === atoi === */

void	putchar_fd(char c, int fd, flags *flg)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
	flg -> len += 1;
}

void	putnbr_fd(long long n, int fd, flags *flg)
{
	long long	num;

	if (fd < 0)
		return ;
	num = n;
	if (num < 0)
	{
		putchar_fd('-', fd, flg);
		num *= -1;
	}
	if (num >= 10)
		putnbr_fd(num / 10, fd, flg);
	putchar_fd((num % 10) + '0', fd, flg);
}

void	putnbr_fd_unsigned(unsigned int n, int fd, flags *flg)
{
	if (fd < 0)
		return ;
	if (n >= 10)
		putnbr_fd_unsigned(n / 10, fd, flg);
	putchar_fd((n % 10) + '0', fd, flg);
}

void	putstr_fd(char *s, int fd, flags *flg)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		flg -> len += 6;
		return;
	}	
	while (*s)
	{
		putchar_fd(*s, fd, flg);
		s++;
	}
}

void	put_hex(unsigned int num, int fd, flags *flg)
{
	char			*s;

	s = "0123456789abcdef";
	if (num > 15)
		put_hex(num / 16, fd, flg);
	putchar_fd(s[num % 16], fd, flg);
}

void	put_hex_up(unsigned int num, int fd, flags *flg)
{
	char			*s;

	s = "0123456789ABCDEF";
	if (num > 15)
		put_hex_up(num / 16, fd, flg);
	putchar_fd(s[num % 16], fd, flg);
}

void	put_hex_address(unsigned long i, int fd, flags* flg)
{
	char	*s;

	s = "0123456789abcdef";
	if (i > 15)
		put_hex_address(i / 16, fd, flg);
	putchar_fd(s[i % 16], fd, flg);
}

void	put_address(void *p, int fd, flags* flg, int zero)
{
	unsigned long	a;

	if (p == NULL)
	{
		write(fd, "(nil)", 5);
		flg -> len += 5;
		return ;
	}
	a = (unsigned long)p;
	write(fd, "0x", 2);
	flg -> len += 2;
	put_hex_address(a, fd, flg);
}

int	count_expec_formats(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1))
			if (*(s + 1) == 'c' || *(s + 1) == 's' || *(s + 1) == 'p' 
				|| *(s + 1) == 'd' || *(s + 1) == 'i'
				|| *(s + 1) == 'u' || *(s + 1) == 'x' 
				|| *(s + 1) == 'X' || *(s + 1) == '%')
				count++;
		s++;
	}
	return (count);
}

int	count_digits(int n, int specifier)
{
    int	count;

	count = 0;
	if (n == 0) 
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	count_expec_hex_chars(int num)
{
	int	length;

	length = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		num = -num;
	while (num > 0)
	{
		num /= 16;
		length++;
	}
	return (length);
}

void	put_spaces(int num, int width, int fd, flags *flg)
{
	int	digits_count;
	int	spaces;

	digits_count = count_digits(num, fd);
	spaces = width - digits_count;
	if (flg -> space || flg -> plus_sign)
		spaces--;
	if (num < 0)
		spaces--;
	while (spaces > 0)
	{
		write(fd, " ", 1);
		flg -> len += 1;
		spaces--;
	}
}

int	get_digit_count(int num)
{
	int	digits_count;
	
	if (num < 0)
		num = -num;
	digits_count = count_digits(num, 1);
	return (digits_count);
}

void	put_zeros(int num, int width, int fd, flags *flg)
{
	int	digits_count;
	int	zeros;
	
	digits_count = get_digit_count(num);
	zeros = width - digits_count;
	if (num < 0)
		zeros--;
	while (zeros > 0)
	{
		write(fd, "0", 1);
		flg -> len += 1;
		zeros--;
	}
}

void	handle_sign(int num, int fd, flags *flg)
{
	if (num < 0)
	{
		write(fd, "-", 1);
		flg -> len += 1;
	}
	else if (flg->plus_sign)
	{
		write(fd, "+", 1);
		flg -> len += 1;
		flg -> width--;
	}
	else if (flg->space)
	{
		write(fd, " ", 1);
		flg -> len += 1;
		flg -> width--;
	}
}

void	print_number(int num, int fd, flags *flg)
{
    long number = num;
    if (number < 0)
        number = -number;
    putnbr_fd(number, fd, flg);
}

void d_manager(long num, int fd, flags *flg, int specifier)
{
	if (specifier == 'u')
		flg -> plus_sign = 0;
	if (!flg->minus_sign)
	{
		if (flg->zero)
		{
			handle_sign(num, fd, flg);
			put_zeros(num, flg->width, fd, flg);
		}
        else
        {
            put_spaces(num, flg->width, fd, flg);
            handle_sign(num, fd, flg);
        }
    }
    else
        handle_sign(num, fd, flg);
    if (specifier == 'u')
        putnbr_fd_unsigned(num, fd, flg);
    else
        print_number(num, fd, flg);
    if (flg->minus_sign)
        put_spaces(num, flg->width, fd, flg);
}

void	put_spaces_s(char *s, int width, int fd, flags *flg)
{
	int	spaces;

	spaces = width - ft_strlen(s);
	if (!s)
		spaces -= 6;
	while (spaces > 0)
	{
		write(fd, " ", 1);
		flg -> len += 1;
		spaces--;
	}
}

void	put_spaces_xX(int count, int width, int fd)
{
	int	spaces;

	spaces = width - count;
	while (spaces > 0)
	{
		write(fd, " ", 1);
		spaces--;
	}
}

// void    s_manager(char *s, int fd, flags *flg)
// {
//     char padding = (flg->zero && !flg->minus_sign) ? '0' : ' ';
//     int len = ft_strlen(s);
//     int padding_len = (flg->width > len) ? flg->width - len : 0;

//     if (!flg->minus_sign)
//         while (padding_len--)
//         {
//             write(fd, &padding, 1);
//             flg->len++;
//         }
//     putstr_fd(s, fd, flg);   
//     if (flg->minus_sign)
//         while (padding_len--)
//         {
//             write(fd, " ", 1);  // Always spaces for left alignment
//             flg->len++;
//         }
// }

void	s_manager(char *s, int fd, flags *flg)
{
	if (!flg -> minus_sign)
		put_spaces_s(s, flg -> width, fd, flg);
	putstr_fd(s, fd, flg);
	if (flg -> minus_sign)
		put_spaces_s(s, flg -> width, fd, flg);
}

void    c_manager(char c, int fd, flags *flg)
{

	flg -> zero = 0;
    char padding = (flg->zero && !flg->minus_sign) ? '0' : ' ';
    int padding_len = (flg->width > 1) ? flg->width - 1 : 0;

    if (!flg->minus_sign)
        while (padding_len--)
        {
            write(fd, &padding, 1);
            flg->len++;
        }
    
    putchar_fd(c, fd, flg);
    
    if (flg->minus_sign)
        while (padding_len--)
        {
            write(fd, " ", 1);
            flg->len++;
        }
}

// void	c_manager(char c, int fd, flags *flg)
// {
// 	if (!flg -> minus_sign)
// 		put_spaces_s("s", flg -> width, fd, flg);
// 	putchar_fd(c, fd, flg);
// 	if (flg -> minus_sign)
// 		put_spaces_s("s", flg -> width, fd, flg);
// }

void	put_padding(int length, int width, int fd, flags *flg, char pad_char)
{
	int	padding;

	padding = 0;
	if (width > length)
		padding = width - length;
	while (padding > 0)
	{
		write(fd, &pad_char, 1);
		flg->len++;
		padding--;
	}
}

void	handle_hash_prefix(unsigned int num, int fd, flags *flg, char format)
{
	if (flg->hash && num != 0)
	{
		if (format == 'x')
			write(fd, "0x", 2);
		else
			write(fd, "0X", 2);
		flg->len += 2;
	}
}

void	_put_hex(unsigned int num, int fd, flags *flg, char format)
{
	if (format == 'x')
		put_hex(num, fd, flg);
	else if (format == 'X')
		put_hex_up(num, fd, flg);
}

void	Xx_manager(unsigned int num, int fd, flags *flg, char format)
{
	int	count;

	flg -> len -= 6;
	count = count_expec_hex_chars(num);
	if (flg->hash && num != 0)
		count += 2; // Include "0x" or "0X" prefix
	flg->len += count;
	if (!flg->minus_sign && (!flg->zero || !flg->hash))
		put_padding(count, flg->width, fd, flg, ' ');
	handle_hash_prefix(num, fd, flg, format);
	if (!flg->minus_sign && flg->zero)
		put_padding(count, flg->width, fd, flg, '0');
	_put_hex(num, fd, flg, format);
	if (flg->minus_sign)
		put_padding(count, flg->width, fd, flg, ' ');
}

// void p_manager(void *p, flags *flg, int fd)
// {
//     int len;

//     if (p == NULL)
//         len = 5; // Length of "(nil)"
//     else
//     {
//         len = 2; // For "0x"
//         len += count_expec_hex_chars((unsigned long)p);
//     }

//     if (!flg->minus_sign)
//         put_padding(len, flg->width, fd, flg, ' ');

//     put_address(p, fd, flg);

//     if (flg->minus_sign)
//         put_padding(len, flg->width, fd, flg, ' ');
// }

void	put_padding_p(flags *flg, int len, int fd)
{
	int	zeros;

	if (flg -> space)
   	{
   		write(1, " ", 1);
   		flg -> len -= 1;
   		flg -> width -= 1;
    }
	if (!flg -> minus_sign)
    {
    	if (flg -> zero)
        {
            zeros = flg -> width - len;
            write(1, "0x", 2);
            zeros -= 2;
            while (zeros-- > 0)
            {
                write(fd, "0", 1);
                flg -> len++;
            }
        }
        else
            put_spaces_xX(len, flg -> width, fd);
    }
}

void p_manager(void *p, flags *flg, int fd)
{
    int len;

    if (p == NULL)
    {
     	flg -> len += 5;
        len = 5;
    }
    else
    	len = 14;
    put_padding_p(flg, len, fd);
    put_address(p, fd, flg, flg -> zero);
    if (flg -> minus_sign) 
        put_spaces_xX(len, flg -> width, fd);
    flg -> len += len - 14;
}

void	put_format(char c, va_list *r2, flags *flg)
{
	int	fd;

	fd = 1;
	if (c == 'c')
		c_manager((char)va_arg(*r2, int), fd, flg);
	else if (c == 's')
		s_manager(va_arg(*r2, char *), fd, flg);
	else if (c == 'd' || c == 'i')
		d_manager(va_arg(*r2, long), fd, flg, c);
	else if (c == 'u')	
		d_manager(va_arg(*r2, unsigned int), fd, flg, c);
	else if (c == 'x' || c == 'X')
		Xx_manager(va_arg(*r2, unsigned int), fd, flg, c);
	else if (c == 'p')
		p_manager(va_arg(*r2, void *), flg, fd);
}

void	advance_s(char **s)
{
	(*s) += 2;
}

void	put_(char **s, flags *flg)
{
	int	fd;

	fd = 1;
	putchar_fd(**s, fd, flg);
	if (!**s)
		return ;
	(*s)++;
}

int	catch_flags(char *s)
{
	if (!*(s + 1))
		return (0);
	s++;
	if (*s == '+' || *s == ' ' || *s == '#')
		return (1);
	return (0);
}

int	catch_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p' 
		|| c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' 
		|| c == 'X')
		return (1);
	return (0);
}

int	full_format_check(char *s)
{
	if (!*(s + 1))
		return (0);
	s++;
	while (*s == '+' || *s == ' ' || *s == '#')
		s++;
	return (catch_specifier(*s));
}

void	minus_flag_manager(char **s, flags **flg)
{
	(*flg) -> minus_sign = 1;
	(*s)++;
	(*flg) -> width = ft_atoi(*s);
	while (**s >= '0' && **s <= '9')
		(*s)++;
	(*s)--;
}

void	skip_width(char **s)
{
	while (**s >= '0' && **s <= '9')
	{
		(*s)++;
	}
}

void	get_flags(flags **flg, char **s)
{
	(*s)++;
	while ( **s && (**s == '+' || **s == ' ' || **s == '#' || **s == '-' || **s == '.' || **s == '0'))
	{
		if (**s == '+')
			(*flg) -> plus_sign = 1;
		if (**s == ' ')
			(*flg) -> space = 1;
		if (**s == '#')
			(*flg) -> hash = 1;
		if (**s == '-')
			(*flg) -> minus_sign = 1;
		if (**s == '.')
			(*flg) -> precision = 1;
		if (**s == '0')
			(*flg) -> zero = 1;
		(*s)++;
	}
	if (**s >= '0' && **s <= '9')
	{
		(*flg) -> width = ft_atoi(*s);
		skip_width(s);
	}
	(*s)--;
}

int	process_string(char *s, va_list r)
{
	va_list	  r2;
	flags	*flg = malloc(sizeof(flags));
	int	ret;

	ret = 0;
	memset(flg, 0, sizeof(flags));
	va_copy(r2, r);
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			get_flags(&flg, &s);
			if (catch_specifier(*(s + 1)))
			{
				put_format(*(s + 1), &r2, flg);
				advance_s(&s);
			}
			else if (*(s + 1) == '%')
			{
				putchar_fd('%', 1, flg);
				advance_s(&s);
			}
			else
			{
				putchar_fd('%', 1, flg);
				s++;
			}
		}
		else
			put_(&s, flg);
	}
	ret = flg -> len;
	free(flg);
	va_end(r2);
	return (ret);
}

int ft_printf(char *s, ...)
{
    va_list r;
    int len;

    if (!s)
        return (0);
    va_start(r, s);
    len = process_string(s, r);
    va_end(r);
    return (len);
}

#include <limits.h>

int main(int argc, char const *argv[])
{
	char ii = 'd';
	char *p = &ii;
	int i = ft_printf("|%020p|\n", p);
	printf("|%020p|\n", p);
	printf("%d\n", i - 3);
	return 0;
}
