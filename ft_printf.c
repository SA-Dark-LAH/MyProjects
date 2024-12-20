#include "ft_printf.h"

// Main ft_printf function
int ft_printf(const char *format, ...)
{
    
    va_list args;
    int printed_chars = 0;

    va_start(args, format);
    while (*format) {
        if (*format == '%')
        {
            format++;
            t_flags flags = parse_flags(&format);
            printed_chars += handle_specifier(&format, args, flags); // Add printed chars
        }
        else
        {
            printed_chars += ft_putchar(*format); // Print regular character
            format++;
        }
    }
    va_end(args);
    return printed_chars;
}