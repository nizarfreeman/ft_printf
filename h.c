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
		return ;
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

void	put_special(char **s)
{
	int		fd;
	char		 c; 

	fd = 1;
	if (*(*s + 1))
	{
		(*s)++;
		c = **s;
		if (c == 'n' || c == '\'' || c == '\"' || c == '\\')
		{
			if (c == 'n')
				c = '\n';
			putchar_fd(c, fd);
			(*s)++;
		}
		else
			putchar_fd('\\', fd);
	}
}

void	put_(char **s)
{
	int	fd;

	fd = 1;
	putchar_fd(**s, fd);
	(*s)++;
}

void	process_string(char *s, va_list r)
{
	va_list	r2;

	va_copy(r2, r);
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			if (*(s + 1) == 'c' || *(s + 1) == 's' || *(s + 1) == 'p' 
				|| *(s + 1) == 'd' || *(s + 1) == 'i'
				|| *(s + 1) == 'u' || *(s + 1) == 'x' 
				|| *(s + 1) == 'X')
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
				put_(&s);
		}
		else if (*s == '\\')
			put_special(&s);
		else
			put_(&s);
	}
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

/*void test_comparison(const char* test_name, char* format, ...)
{
    va_list args1, args2;
    int result1, result2;

    printf("\n=== Test: %s ===\n", test_name);
    printf("Format string: \"%s\"\n", format);

    printf("Original printf output: ");
    va_start(args1, format);
    result1 = vprintf(format, args1);
    va_end(args1);
    printf("\n");

    printf("Your ft_printf output: ");
    va_start(args2, format);
    result2 = vprintf(format, args2);
    va_end(args2);
    printf("\n");

    printf("Original printf return: %d\n", result1);
    printf("Your ft_printf return: %d\n", result2);
}

int main(void)
{
    char *str = "test string";
    char c = 'X';
    void *ptr = &c;
    int num = 42;

    printf("\n=== BASIC TESTS ===\n");

    // Test %c
    ft_printf("Char test: %c\n", 'A');
    printf("Char test: %c\n", 'A');

    // Test %s
    ft_printf("String test: %s\n", "Hello World");
    printf("String test: %s\n", "Hello World");

    // Test %d and %i
    ft_printf("Integer tests: %d %i\n", 42, -42);
    printf("Integer tests: %d %i\n", 42, -42);

    // Test %u
    ft_printf("Unsigned test: %u\n", 4294967295);
    printf("Unsigned test: %u\n", 4294967295);

    // Test %x and %X
    ft_printf("Hex tests: %x %X\n", 255, 255);
    printf("Hex tests: %x %X\n", 255, 255);

    // Test %p
    ft_printf("Pointer test: %p\n", &ptr);
    printf("Pointer test: %p\n", &ptr);

    // Test %%
    ft_printf("Percent test: %%\n");
    printf("Percent test: %%\n");

    printf("\n=== EDGE CASES ===\n");

    // NULL string
    ft_printf("NULL string test: %s\n", NULL);
    printf("NULL string test: %s\n", NULL);

    // NULL pointer
    ft_printf("NULL pointer test: %p\n", NULL);
    printf("NULL pointer test: %p\n", NULL);

    // Integer limits
    ft_printf("Int MIN: %d\n", INT_MIN);
    printf("Int MIN: %d\n", INT_MIN);
    ft_printf("Int MAX: %d\n", INT_MAX);
    printf("Int MAX: %d\n", INT_MAX);

    // Special characters
    ft_printf("Special chars: \n \' \" \\\n");
    printf("Special chars: \n \' \" \\\n");

    printf("\n=== COMPLEX COMBINATIONS ===\n");

    // Multiple conversions in one string
    ft_printf("Combined test: %c %s %d %i %u %x %X %p %%\n",
             'Z', "test", -42, 42, 42, 42, 42, ptr);
    printf("Combined test: %c %s %d %i %u %x %X %p %%\n",
           'Z', "test", -42, 42, 42, 42, 42, ptr);

    // Adjacent conversions
    ft_printf("Adjacent conversions: %d%d%d\n", 1, 2, 3);
    printf("Adjacent conversions: %d%d%d\n", 1, 2, 3);

    printf("\n=== STRESS TESTS ===\n");

    // Long string
    char long_str[1000];
    memset(long_str, 'A', 999);
    long_str[999] = '\0';
    ft_printf("Long string: %s\n", long_str);
    printf("Long string: %s\n", long_str);

    // Many conversions
    ft_printf("%d %d %d %d %d %d %d %d %d %d\n",
             1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    printf("%d %d %d %d %d %d %d %d %d %d\n",
           1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    printf("\n=== SPECIAL FORMATTING TESTS ===\n");

    // Empty string
    ft_printf("");
    printf("");

    // Just a newline
    ft_printf("\n");
    printf("\n");

    // Mixed special characters
    ft_printf("Mixed special: \'\"\\\n");
    printf("Mixed special: \'\"\\\n");

    printf("\n=== INVALID FORMAT TESTS ===\n");

    // Invalid format specifiers
    ft_printf("Invalid specifier test: %k\n");
    printf("Invalid specifier test: %k\n");

    // Incomplete format specifier
    ft_printf("Incomplete format test: %\n");
    
    return (0);
}*/

void test_title(char *title)
{
    printf("\n\033[1;34m=== %s ===\033[0m\n", title);
}

void compare_printf(char *format, ...)
{
    va_list args1, args2;
    int ret1, ret2;

    va_start(args1, format);
    va_start(args2, format);

    printf("format: \"%s\"\n", format);
    printf("orig: ");
    ret1 = vprintf(format, args1);
    printf("\nmine: ");
    ret2 = vprintf(format, args2);
    printf("\norig ret: %d\n", ret1);
    printf("mine ret: %d\n", ret2);

    va_end(args1);
    va_end(args2);
}

int main(void)
{
    // Test variables
    char            c = 'A';
    char            *str = "test";
    char            *null_str = NULL;
    void            *ptr = &c;
    void            *null_ptr = NULL;
    int             num = 42;
    unsigned int    unum = UINT_MAX;

    test_title("CHARACTER TESTS");
    compare_printf("%c", 'x');                    // Basic char
    compare_printf("%c", 0);                      // Null char
    compare_printf("%c", 127);                    // DEL char
    compare_printf("%c%c%c", '1', '2', '3');     // Multiple chars
    compare_printf("a%cb%cc", 'X', 'Y');         // Chars with text

    test_title("STRING TESTS");
    compare_printf("%s", "Hello");                // Basic string
    compare_printf("%s", "");                     // Empty string
    compare_printf("%s", null_str);               // NULL string
    compare_printf("%s%s", "Hello", "World");     // Multiple strings
    compare_printf("The%sTest", "String");        // String with text

    test_title("POINTER TESTS");
    compare_printf("%p", ptr);                    // Basic pointer
    compare_printf("%p", null_ptr);               // NULL pointer
    compare_printf("%p%p", ptr, ptr);             // Multiple pointers
    compare_printf("Ptr:%p", ptr);                // Pointer with text
    compare_printf("%p", (void *)0x0);            // Zero address
    compare_printf("%p", (void *)-1);             // Maximum address

    test_title("INTEGER TESTS");
    compare_printf("%d", 0);                      // Zero
    compare_printf("%d", -0);                     // Negative zero
    compare_printf("%d", INT_MAX);                // Maximum int
    compare_printf("%d", INT_MIN);                // Minimum int
    compare_printf("%d", -42);                    // Negative number
    compare_printf("Value:%d", 42);               // Int with text

    test_title("INTEGER TESTS (i)");
    compare_printf("%i", 0);                      // Zero
    compare_printf("%i", -0);                     // Negative zero
    compare_printf("%i", INT_MAX);                // Maximum int
    compare_printf("%i", INT_MIN);                // Minimum int
    compare_printf("%i", -42);                    // Negative number
    compare_printf("Value:%i", 42);               // Int with text

    test_title("UNSIGNED TESTS");
    compare_printf("%u", 0);                      // Zero
    compare_printf("%u", UINT_MAX);               // Maximum unsigned
    compare_printf("%u", 42);                     // Basic unsigned
    compare_printf("Value:%u", UINT_MAX);         // Unsigned with text

    test_title("HEXADECIMAL TESTS (lowercase)");
    compare_printf("%x", 0);                      // Zero
    compare_printf("%x", UINT_MAX);               // Maximum value
    compare_printf("%x", 0xabcdef);               // Hex number
    compare_printf("%x", -42);                    // Negative number
    compare_printf("Hex:%x", 0xff);               // Hex with text

    test_title("HEXADECIMAL TESTS (uppercase)");
    compare_printf("%X", 0);                      // Zero
    compare_printf("%X", UINT_MAX);               // Maximum value
    compare_printf("%X", 0xABCDEF);               // Hex number
    compare_printf("%X", -42);                    // Negative number
    compare_printf("Hex:%X", 0xFF);               // Hex with text

    test_title("PERCENT SIGN TESTS");
    compare_printf("%%");                         // Single percent
    compare_printf("%%%%");                       // Multiple percent
    compare_printf("100%%");                      // Percent with text

    test_title("MIXED FORMAT TESTS");
    compare_printf("%d%x%X%u", 42, 42, 42, 42);   // Multiple numbers
    compare_printf("%s%c%p", "Hi", '!', ptr);     // Different types
    compare_printf("Test%d%s%c", 42, "Hi", '!');  // Mixed with text

    test_title("SPECIAL CHARACTER TESTS");
    compare_printf("\\n");                        // Newline
    compare_printf("\\'");                        // Single quote
    compare_printf("\\\"");                       // Double quote
    compare_printf("\\\\");                       // Backslash
    compare_printf("\\k");                        // Invalid escape

    test_title("EDGE CASE COMBINATIONS");
    compare_printf("%c%c%c%c%c", 'H', 'e', 'l', 'l', 'o');  // Many chars
    compare_printf("%s%s%s", "A", "", null_str);             // String combinations
    compare_printf("%d%i%u%x%X", INT_MIN, INT_MAX, UINT_MAX, 0xdead, 0xBEEF); // Number combinations
    compare_printf("%p%p%p", ptr, null_ptr, (void *)0xdeadbeef); // Pointer combinations
    compare_printf("%%%%%%%%%%");                            // Many percent signs
    compare_printf("Mix\\n%s\\\"Quote\\\'%d\\\\%x", "test", 42, 255); // Everything

    test_title("INVALID FORMAT TESTS");
    compare_printf("%");                          // Single percent
    compare_printf("%k");                         // Invalid specifier
    compare_printf("% ");                         // Space after percent
    compare_printf("%9");                         // Number after percent

    return (0);
}

