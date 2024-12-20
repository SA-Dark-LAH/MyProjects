#include "ft_printf.h"

// Print a single character and return 1 (for printf count)
int ft_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

// Print a string and return the number of characters printed
int ft_putstr(char *str)
{
   int len ;
   
   len = 0 ;
   if (!str)
   {
        len = ft_putstr("(null)");
        return len;
    }
    while (*str)
        len += ft_putchar(*str++);
    return (len);
}

// Print a signed/unsigned number and return the number of characters printed
int ft_putnbr(long n)
{ 
    char s[20]; // Buffer for digits
    int i ;
    int count ;

    i = 0 ;
    count = 0 ;
    if (n == 0)
    return (ft_putchar('0'), 1);
    if (n < 0)
    {
        count += ft_putchar('-');
        n = -n;
    }
    while (n)
    {
        s[i++] = (n % 10) + '0';
        n /= 10;
    }
    while (--i >= 0)
    {
        ft_putchar(s[i]);
        count++;
    }
    return (count);
}