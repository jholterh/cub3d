/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:17:07 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/19 14:38:46 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compares two strings with another

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while ((*str1 || *str2) && n-- > 0)
	{
		if (*str1 > *str2)
			return (*str1 - *str2);
		if (*str1 < *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}
