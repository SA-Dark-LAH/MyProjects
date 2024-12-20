#include "ft_printf.h"

// Parse flags like '#', '+', and ' '
t_flags parse_flags(const char **format) {
    t_flags flags = {0, 0, 0}; // Initialize flags

    while (**format == '#' || **format == '+' || **format == ' ') {
        if (**format == '#')
            flags.hash = 1;
        else if (**format == '+')
            flags.plus = 1;
        else if (**format == ' ')
            flags.space = 1;
        (*format)++; // Move to the next character
    }
    return flags;
}