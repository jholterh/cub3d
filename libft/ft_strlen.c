/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:59:54 by jholterh          #+#    #+#             */
/*   Updated: 2025/02/21 13:28:39 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// finds length of str

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlen2(const char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
