/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:03:47 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/19 14:37:30 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// finds last occurance of a char in a string

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		s_len;

	s_len = ft_strlen(s);
	str = (char *)s;
	while (s_len >= 0)
	{
		if (str[s_len] == (char)c)
			return (str + s_len);
		s_len--;
	}
	return (NULL);
}
