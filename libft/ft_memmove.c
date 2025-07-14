/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:48:29 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/19 14:33:06 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// same as memcpy but can handle overlapping memory

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d < s)
	{
		i = -1;
		while (++i < num)
			d[i] = s[i];
	}
	else if (d > s)
	{
		i = num;
		while (i-- > 0)
			d[i] = s[i];
	}
	return (dst);
}
