/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:28:00 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/19 14:29:38 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// writes len bytes with the value to the string

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (len > 0)
	{
		*(p++) = (unsigned char)value;
		len--;
	}
	return (ptr);
}
