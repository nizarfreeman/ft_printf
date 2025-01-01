#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
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
	int	minus_width;
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

void	putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	putnbr_fd(int n, int fd)
{
	long	num;

	if (fd < 0)
		return ;
	num = (long) n;
	if (num < 0)
	{
		putchar_fd('-', fd);
		num *= -1;
	}
	if (num >= 10)
		putnbr_fd(num / 10, fd);
	putchar_fd((num % 10) + '0', fd);
}

void	putnbr_fd_unsigned(unsigned int n, int fd)
{
	if (fd < 0)
		return ;
	if (n >= 10)
		putnbr_fd_unsigned(n / 10, fd);
	putchar_fd((n % 10) + '0', fd);
}

void	putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return;
	}	
	while (*s)
	{
		putchar_fd(*s, fd);
		s++;
	}
}

void	put_hex(unsigned int num, int fd)
{
	char			*s;

	s = "0123456789abcdef";
	if (num > 15)
		put_hex(num / 16, fd);
	putchar_fd(s[num % 16], fd);
}

void	put_hex_up(unsigned int num, int fd)
{
	char			*s;

	s = "0123456789ABCDEF";
	if (num > 15)
		put_hex_up(num / 16, fd);
	putchar_fd(s[num % 16], fd);
}

void	put_hex_address(unsigned long i, int fd)
{
	char	*s;

	s = "0123456789abcdef";
	if (i > 15)
		put_hex_address(i / 16, fd);
	putchar_fd(s[i % 16], fd);
}

void	put_address(void *p, int fd)
{
	unsigned long	a;

	if (p == NULL)
	{
		write(fd, "(nil)", 5);
		return ;
	}
	a = (unsigned long)p;
	write(fd, "0x", 2);
	put_hex_address(a, fd);
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

void	put_spaces(int num, int width, int fd)
{
	int	digits_count;
	int	spaces;
		
	digits_count = count_digits(num, fd);
	spaces = width - digits_count;
	if (num < 0)
		spaces--;
	while (spaces > 0)
	{
		write(fd, " ", 1);
		spaces--;
	}
}

void	d_manager(int num, int fd, flags *flg)
{
	if (flg -> plus_sign && num >= 0)
	{
		write(fd, "+", 1); 
		flg -> minus_width -= 1;
	}
	else if (flg -> space && num >= 0)
	{	
		write(fd, " ", 1);
		flg -> minus_width -= 1;
	}
	if (!flg -> minus_sign)
		put_spaces(num, flg -> minus_width, fd);
	putnbr_fd(num, fd);
	if (flg -> minus_sign)
	{
		put_spaces(num, flg -> minus_width, fd);
	}
}

void	put_spaces_s(char *s, int width, int fd)
{
	int	spaces;

	spaces = width - ft_strlen(s);
	if (!s)
		spaces -= 6;
	while (spaces > 0)
	{
		write(fd, " ", 1);
		spaces--;
	}
}

void	s_manager(char *s, int fd, flags *flg)
{
	if (!flg -> minus_sign)
		put_spaces_s(s, flg -> minus_width, fd);
	putstr_fd(s, fd);
	if (flg -> minus_sign)
		put_spaces_s(s, flg -> minus_width, fd);
}

void	c_manager(char c, int fd, flags *flg)
{
	if (!flg -> minus_sign)
		put_spaces_s("s", flg -> minus_width, fd);
	putchar_fd(c, fd);
	if (flg -> minus_sign)
		put_spaces_s("s", flg -> minus_width, fd);
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

void	_put_hex(unsigned int num, int fd, flags *flg, char format)
{
	if (format == 'x' && flg -> hash)
		write(fd, "0x", 2);
	else if (format == 'X' && flg -> hash)
		write(1, "0X", 2);
	if (format == 'x')
		put_hex(num, fd);
	else if(format == 'X')
		put_hex_up(num , fd);
}

void	Xx_manager(unsigned int num, int fd, flags *flg, char format)
{
	int count;

	count = count_expec_hex_chars(num);
	if (flg -> hash)
		count += 2;
	if (!flg -> minus_width)
		put_spaces_xX(count, flg -> minus_width, fd);
	if (format == 'X')
		put_hex_up(num, fd);
	if (format == 'x')
		put_hex(num, fd);
	if (flg -> minus_width)
		put_spaces_xX(count, flg -> minus_width, fd);
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
		d_manager(va_arg(*r2, int), fd, flg);
	else if (c == 'u')	
		d_manager(va_arg(*r2, unsigned int), fd, flg);
	else if (c == 'x' || c == 'X')
		Xx_manager(va_arg(*r2, unsigned int), fd, flg, c);
	else if (c == 'p')
		(va_arg(*r2, void *), fd);
}

void	advance_s(char **s)
{
	(*s) += 2;
}

void	put_(char **s)
{
	int	fd;

	fd = 1;
	putchar_fd(**s, fd);
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
	(*flg) -> minus_width = ft_atoi(*s);
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
		(*flg) -> minus_width = ft_atoi(*s);
		skip_width(s);
	}
	(*s)--;
}

void	process_string(char *s, va_list r)
{
	va_list	  r2;
	flags	*flg = malloc(sizeof(flags));

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
				putchar_fd('%', 1);
				advance_s(&s);
			}
			else
			{
				putchar_fd('%', 1);
				s++;
			}
		}
		else
			put_(&s);
	}
	free(flg);
	va_end(r2);
}

int	ft_printf(char *s, ...)
{
	va_list	r;

	if (!s)
		return (0);
	va_start(r, s);
	process_string(s, r);
	va_end(r);
	return (0);
}

int main()
{
	int a = 4;
	int *p = &a;
	ft_printf("|%-12x|\n", 255);
	printf("|%-12x|\n",255);

	//ft_printf("|%-p|\n", p);
	return (0);
}

// int main()
// {
//     // Basic left alignment tests
//     printf("=== Basic Left Alignment Tests ===\n");
//     printf("Printf:    |%-3d|\n", 42);
//     ft_printf("ft_Printf: |%-3d|\n", 42);
    
//     printf("\nPrintf:    |%-5d|\n", 42);
//     ft_printf("ft_Printf: |%-5d|\n", 42);
    
//     printf("\nPrintf:    |%-2d|\n", 42);
//     ft_printf("ft_Printf: |%-2d|\n", 42);

//     // Left alignment with positive numbers and plus flag
//     printf("\n=== Left Alignment with Plus Flag ===\n");
//     printf("Printf:    |%-+5d|\n", 42);
//     ft_printf("ft_Printf: |%-+5d|\n", 42);
    
//     printf("\nPrintf:    |%-+3d|\n", 42);
//     ft_printf("ft_Printf: |%-+3d|\n", 42);

//     // Left alignment with negative numbers
//     printf("\n=== Left Alignment with Negative Numbers ===\n");
//     printf("Printf:    |%-5d|\n", -42);
//     ft_printf("ft_Printf: |%-5d|\n", -42);
    
//     printf("\nPrintf:    |%-3d|\n", -42);
//     ft_printf("ft_Printf: |%-3d|\n", -42);

//     // Left alignment with space flag
//     printf("\n=== Left Alignment with Space Flag ===\n");
//     printf("Printf:    |%- 5d|\n", 42);
//     ft_printf("ft_Printf: |%- 5d|\n", 42);
    
//     printf("\nPrintf:    |%- 5d|\n", -42);
//     ft_printf("ft_Printf: |%- 5d|\n", -42);

//     // Edge cases
//     printf("\n=== Edge Cases ===\n");
//     printf("Printf:    |%-1d|\n", 42);
//     ft_printf("ft_Printf: |%-1d|\n", 42);
    
//     printf("\nPrintf:    |%-+1d|\n", 42);
//     ft_printf("ft_Printf: |%-+1d|\n", 42);
    
//     printf("\nPrintf:    |%-5d|\n", 0);
//     ft_printf("ft_Printf: |%-5d|\n", 0);

//     return (0);
// }
