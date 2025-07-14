/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:05:21 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/20 16:39:57 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copies string and allocates memory for it

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s1);
	str = (char *)malloc((s_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
