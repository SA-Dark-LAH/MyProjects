#include "ft_printf.h"

int	hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len ++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_hex(unsigned int num, int uppercase)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, uppercase);
		ft_put_hex(num % 16, uppercase);
	}
	else
	{
		if (num <= 9)
			ft_putchar((num + '0'));
		else
		{
			if (uppercase == 0)
				ft_putchar((num - 10 + 'a'));
			if (uppercase == 1)
				ft_putchar((num - 10 + 'A'));
		}
	}
}

int	ft_puthex(unsigned int num, int uppercase)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(num, uppercase);
	return (5);
}