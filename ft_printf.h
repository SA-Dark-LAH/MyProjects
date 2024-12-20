#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>

// Flag structure to store '#', '+', and ' ' (space) flags
typedef struct s_flags {
    int hash;
    int plus;
    int space;
} t_flags;

// Main functions
int ft_printf(const char *format, ...);

// Flag parsing
t_flags parse_flags(const char **format);

// Specifier handling
int handle_specifier(const char **format, va_list args, t_flags flags);
int handle_char(va_list args);
int handle_string(va_list args);
int handle_integer(va_list args, t_flags flags);
int handle_unsigned(va_list args);
int handle_hex(va_list args, t_flags flags, int uppercase);

// Helper functions
int ft_putchar(char c);
int ft_putstr(char *str);
int ft_putnbr(long n);

//hex
int			hex_len(unsigned int num);
void	ft_put_hex(unsigned int num, int uppercase);
int	ft_puthex(unsigned int num, int uppercase);


#endif