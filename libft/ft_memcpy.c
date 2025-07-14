/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:29:21 by jholterh          #+#    #+#             */
/*   Updated: 2025/03/06 18:49:31 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copies maximum n bytes from src to dest

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst || !src)
		return (dst);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (num > 0)
	{
		*(d++) = *(s++);
		num--;
	}
	return (dst);
}

void	**ft_memcpy2(void **dst, const void **src, size_t num)
{
	size_t	i;

	if (!dst || !src)
		return (dst);
	i = 0;
	while (i < num / sizeof(void *))
	{
		dst[i] = malloc(sizeof(void *));
		if (dst[i] && src[i])
			ft_memcpy(dst[i], src[i], sizeof(void *));
		i++;
	}
	return (dst);
}
