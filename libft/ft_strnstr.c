/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:09:08 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/26 14:49:30 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// finds the first occurance of a string in a string

#include "libft.h"

static char	*check_needle(const char *haystack, const char *needle, 
							size_t i, size_t len)
{
	size_t	j;
	size_t	n_len;

	j = 0;
	n_len = ft_strlen(needle);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[j])
		{
			j++;
			if (j == n_len)
				return ((char *)(haystack + i - j + 1));
		}
		else
		{
			if (j > 0)
				i -= j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	return (check_needle(haystack, needle, i, len));
}
