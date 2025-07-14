/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_ten_con.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:16:12 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 14:47:27 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	base_ten_con(unsigned long long number, char *base)
{
	unsigned long long	base_len;
	unsigned long long	div;
	unsigned long long	res;
	int					counter;

	base_len = ft_strlen(base);
	div = 1;
	counter = 0;
	if (number == 0)
	{
		write(1, &base[0], 1);
		return (1);
	}
	while (number / div > base_len - 1)
		div *= base_len;
	while (div > 0)
	{
		res = number / div;
		write(1, &base[res], 1);
		counter++;
		number %= div;
		div /= base_len;
	}
	return (counter);
}
