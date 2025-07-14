/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:48:04 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/26 14:48:51 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// converts a str into an int

#include "libft.h"

static int	isspace3(char c)
{
	if (c == '\t' || c == '\v' || c == '\r'
		|| c == '\n' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	solution;
	int	sign;

	i = 0;
	solution = 0;
	while (isspace3(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		solution = solution * 10 + str[i] - '0';
		i++;
	}
	return (solution * sign);
}
