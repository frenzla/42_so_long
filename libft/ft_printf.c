/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:15:51 by alarose           #+#    #+#             */
/*   Updated: 2024/06/09 10:15:30 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	ft_putchar(int c, int *count)
{
	char	cc;

	cc = (char)c;
	write(1, &cc, 1);
	(*count)++;
	return (1);
}

static int	ft_putstr(char *str, int *count)
{
	if (!str)
		ft_putstr("(null)", count);
	else
		while (*str)
			ft_putchar(*str++, count);
	return (1);
}

static int	p_hex(unsigned int nb, char x, int *count)
{
	if (nb >= 16)
		p_hex(nb / 16, x, count);
	if (x == 'x')
		ft_putchar(HEX_LOWER[nb % 16], count);
	else
		ft_putchar(HEX_UPPER[nb % 16], count);
	return (1);
}

static int	p_p(unsigned long nb, char x, int *count)
{
	if (nb == 0)
	{
		ft_putstr("(nil)", count);
		return (1);
	}
	if (nb < 16)
		ft_putstr("0x", count);
	if (nb >= 16)
		p_p(nb / 16, x, count);
	if (x == 'x')
	{
		ft_putchar(HEX_LOWER[nb % 16], count);
		return (1);
	}
	else
	{
		ft_putchar(HEX_UPPER[nb % 16], count);
		return (1);
	}
	return (0);
}

static int	p_int(int n, int *count)
{
	if (n == INT_MIN)
		return (ft_putstr("-2147483648", count), 1);
	if (n < 0)
	{
		ft_putchar('-', count);
		n = -n;
	}
	if (n >= 10)
		p_int(n / 10, count);
	ft_putchar(n % 10 + '0', count);
	return (1);
}

static int	p_u(unsigned int u, int *count)
{
	if (u >= 10)
		p_u(u / 10, count);
	ft_putchar(u % 10 + '0', count);
	return (1);
}

static int	check_n_print(va_list args, char c, int *count)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int), count));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *), count));
	if (c == 'p')
		return (p_p(va_arg(args, unsigned long), 'x', count));
	if (c == 'd' || c == 'i')
		return (p_int(va_arg(args, int), count));
	if (c == 'u')
		return (p_u(va_arg(args, unsigned int), count));
	if (c == 'x')
		return (p_hex(va_arg(args, unsigned int), 'x', count));
	if (c == 'X')
		return (p_hex(va_arg(args, unsigned int), 'X', count));
	if (c == '%')
		return (ft_putchar('%', count));
	return (0);
}

static char	is_in_set(char c)
{
	int	i;

	i = 0;
	while (SET[i])
	{
		if (c == SET[i])
			return (SET[i]);
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	char	type;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	if (str == NULL)
		return (va_end(args), -1);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			return (-1);
		if (str[i] == '%' && is_in_set(str[i + 1]))
		{
			type = str[i + 1];
			check_n_print(args, type, &count);
			i += 2;
		}
		else
			ft_putchar(str[i++], &count);
	}
	va_end(args);
	return (count);
}
