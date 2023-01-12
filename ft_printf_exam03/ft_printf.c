/*
Assignment name : ft_printf
Expected files : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end

Write a function named ft_printf that will mimic the real printf but it will manage only the following conversions:
s (string), d (decimal) and x (lowercase hexademical).

Your function must be declared as follows:
	int ft_printf(const char *, ... );

Examples of the function output:
	call: ft_printf("%s\n", "toto"); out: toto$
	call: ft_printf("Magic %s is %d", "number", 42); out: Magic number is 42%
	call: ft_printf("Hexadecimal for %d is %x\n", 42, 42); out: Hexadecimal for 42 is 2a$
*/

#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	count = 0;
	while (*str)
	{
		count += ft_putchar(*str);
		str++;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	int	count;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	count = 0;
	if (n < 0)
	{
		n *= -1;
		count += ft_putchar('-');
	}
	if (n > 9)
		count += ft_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	ft_putuhexnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_putuhexnbr(n / 16);
	count += ft_putchar("0123456789abcdef"[n % 16]);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == 's')
				count += ft_putstr(va_arg(ap, char *));
			else if (*str == 'd')
				count += ft_putnbr(va_arg(ap, int));
			else if (*str == 'x')
				count += ft_putuhexnbr(va_arg(ap, unsigned int));
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(ap);
	return (count);
}
