#include "ft_printf.h"

// Dispatches the correct handler based on the specifier
int handle_specifier(const char **format, va_list args, t_flags flags) {
    int printed_chars = 0;

    if (**format == 'c')
        printed_chars = handle_char(args);
    else if (**format == 's')
        printed_chars = handle_string(args);
    else if (**format == 'd' || **format == 'i')
        printed_chars = handle_integer(args, flags);
    else if (**format == 'u')
        printed_chars = handle_unsigned(args);
    else if (**format == 'x')
        printed_chars = handle_hex(args, flags, 0); // Lowercase hexadecimal
    else if (**format == 'X')
        printed_chars = handle_hex(args, flags, 1);
    else if(**format == 'p')
        printed_chars = handle_ptr(args);
    else if (**format == '%')
        printed_chars = ft_putchar('%');
    (*format)++;
    return printed_chars;
}

int handle_char(va_list args) {
    char c = (char)va_arg(args, int);
    return ft_putchar(c);
}

int handle_string(va_list args) {
    char *str = va_arg(args, char *);
    return ft_putstr(str);
}

int handle_integer(va_list args, t_flags flags) {
    int value = va_arg(args, int);
    int printed_chars = 0;

    if (flags.plus && value >= 0)
        printed_chars += ft_putchar('+');
    else if (flags.space && value >= 0)
        printed_chars += ft_putchar(' ');

    printed_chars += ft_putnbr((long)value);
    return printed_chars;
}

int handle_unsigned(va_list args) {
    unsigned int value = va_arg(args, unsigned int);
    return ft_putnbr((long)value); // Cast to long for unsigned
}

int handle_hex(va_list args, t_flags flags, int uppercase) {
    unsigned int value = va_arg(args, unsigned int);
    if (flags.hash && value != 0)
    {
        if(uppercase)
            ft_putstr("0X");
        else if(!uppercase)
            ft_putstr("0x");
    }
    return ft_puthex(value, uppercase);
}

int handle_ptr(va_list args)
{
    return ft_putptr(va_arg(args, uintptr_t));
}