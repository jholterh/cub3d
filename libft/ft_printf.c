/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:13:33 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 14:49:45 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_function(char identifier, va_list args)
{
	char	buffer[2];

	if (identifier == 'i' || identifier == 'd')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (identifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (identifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (identifier == 'u')
		return (base_ten_con(va_arg(args, unsigned int), "0123456789"));
	else if (identifier == 'x')
		return (base_ten_con(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (identifier == 'X')
		return (base_ten_con(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (identifier == '%')
		return (write(1, "%", 1));
	else if (identifier == 'p')
		return (print_pointer(va_arg(args, void *)));
	buffer[0] = '%';
	buffer[1] = identifier;
	return (write(1, buffer, 2));
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;
	int		counter;

	va_start(args, s);
	i = -1;
	counter = 0;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			counter += find_function(s[i + 1], args);
			i++;
		}
		else
		{
			write(1, &s[i], 1);
			counter++;
		}
	}
	va_end(args);
	return (counter);
}
