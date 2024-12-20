# Name of the library
NAME = libftprintf.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = ft_printf.c ft_flags.c ft_specifiers.c ft_helpers.c hex_number.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = ft_printf.h

# Rule to create the library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Compile all files
all: $(NAME)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and library
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

# Bonus rule (add bonus files if necessary)
bonus:
	$(MAKE) SRCS="$(SRCS) ft_bonus.c" all

# Dependencies
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus