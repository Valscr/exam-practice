#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int put_str(const char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (put_str("(null)"));
    while (str[i])
        write(1, &str[i++], 1);
    return (i);
}

int put_digit(long long number, int base, int count)
{
    char    *hexa = "0123456789abcdef";

    if (number < 0)
    {
        count += write(1, "-", 1);
        number *= -1;
    }
    if (number >= base)
       count = put_digit(number / base, base, count);
    count += write(1, &hexa[number % base], 1);
    return (count);
}

int get_type(va_list ap, char c)
{
    int count;

    count = 0;
    if (c == 'd')
        count = put_digit(va_arg(ap, int), 10, count);
    if (c == 's')
        count = put_str(va_arg(ap, char*));
    if (c == 'x')
        count = put_digit(va_arg(ap, unsigned int), 16, count);
    return (count);
}

int ft_printf(const char *in, ... )
{
    int         i;
    int     count;
    va_list     ap;

    i = 0;
    count = 0;
    va_start(ap, in);
    while (in[i])
    {
        if (in[i] == '%' && (in[i + 1] == 's' || in[i + 1] == 'x' || in[i + 1] == 'd'))
            count += get_type(ap, in[++i]);
        else
            count += ft_putchar(in[i]);
        i++;
    }
    va_end(ap);
    return (count);
}

/*int main()
{
    printf("%d\n", ft_printf("%d\n", (int)2147483648));
    ft_printf("%x\n", 123);
    ft_printf("vrai : %d, copie : %d\n", printf("%d\n", -50), ft_printf("%d\n", -50));
    printf("%d\n", printf("%d\n", (int)2147483648));
    printf("%x\n", 123);
    printf("vrai : %d, copie : %d\n", printf("%d\n", -50), ft_printf("%d\n", -50));
}*/