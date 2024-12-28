#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct flags_struct
{
	int	plus_sign;
	int	minus_sign;
	int	space;
	int	hash;
	int	precision;
	int	zero;
}	flags;

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

void	put_hex(int i, int fd)
{
	char			*s;
	unsigned int	num;

	num = (unsigned int)i;
	s = "0123456789abcdef";
	if (num > 15)
		put_hex(num / 16, fd);
	putchar_fd(s[num % 16], fd);
}

void	put_hex_up(int i, int fd)
{
	char			*s;
	unsigned int	num;

	num = (unsigned int)i;
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

void	put_format(char c, va_list *r2)
{
	int	fd;

	fd = 1;
	if (c == 'c')
		putchar_fd((char)va_arg(*r2, int), fd);
	else if (c == 's')
		putstr_fd(va_arg(*r2, char *), fd);
	else if (c == 'd' || c == 'i')
		putnbr_fd(va_arg(*r2, int), fd);
	else if (c == 'u')
		putnbr_fd_unsigned(va_arg(*r2, unsigned int), fd);
	else if (c == 'x')
		put_hex(va_arg(*r2, unsigned int), fd);
	else if (c == 'X')
		put_hex_up(va_arg(*r2, unsigned int), fd);
	else if (c == 'p')
		put_address(va_arg(*r2, void *), fd);
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

int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0) 
		return (count);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
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
	//printf("%c\n\n", *s);
	while (catch_flags(s))
	{
		printf("%c\n", *s);
		s++;
	}
	s++;
	printf("%c\n\n", *s);
	if (catch_specifier(*s))
		return (1);
	printf("%c\n\n", *s);
	return (0);
}

void	get_flags(flags **flg, char **s)
{
	printf("%c\n\n", **s);
	if (!full_format_check(*s))
		return ;
	(*s)++;
	while (**s && catch_flags(*s))
	{
		if (**s == '+')
			(*flg)->plus_sign = 1;
		if (**s == ' ')
			(*flg)->space = 1;
		if (**s == '#')
			(*flg)->hash = 1;
		(*s)++;
	}
	//printf("waaaaaaaaaaaaaaaaaaa %d\n", (*flg) -> plus_sign);
}

void	process_string(char *s, va_list r)
{
	va_list	  r2;
	flags	*flg;

	flg = malloc(sizeof(flags));
	memset(flg, 0, sizeof(flags));
	va_copy(r2, r);
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			get_flags(&flg, &s);
			if (catch_specifier(*(s + 1)))
			{
				put_format(*(s + 1), &r2);
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
	//printf("%d\n", (*flg) -> plus_sign);
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

int main(void)
{
	int *p;
	//ft_printf("%d for %% %d  %s waaaa %x 2555\n", 19, 2005, "nizar", 15);
	//printf("%d for %% %d  %s waaaa %x 2555\n", 19, 2005, "nizar", 15);
	ft_printf("%+ id\n", 15);
	//printf("|%-3d|", 0);
}
