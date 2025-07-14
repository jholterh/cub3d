/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:14:54 by jholterh          #+#    #+#             */
/*   Updated: 2025/03/06 18:48:20 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t new_size, size_t old_size)
{
	void	*ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(p);
		return (NULL);
	}
	if (p == NULL)
		return (malloc(new_size));
	ptr = malloc(new_size);
	if (!ptr)
		return (NULL);
	if (new_size < old_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	ft_memcpy(ptr, p, copy_size);
	free(p);
	return (ptr);
}

void	**ft_realloc2(void **p, size_t new_size, size_t old_size)
{
	void	**ptr;
	size_t	copy_size;
	size_t	num_elements_old;
	size_t	num_elements_new;

	if (new_size == 0)
	{
		ft_strfree((char **)p);
		return (NULL);
	}
	if (p == NULL)
		return (malloc(new_size));
	ptr = malloc(new_size);
	if (!ptr)
		return (NULL);
	num_elements_old = old_size / sizeof(void *);
	num_elements_new = new_size / sizeof(void *);
	if (num_elements_new < num_elements_old)
		copy_size = num_elements_new;
	else
		copy_size = num_elements_old;
	ft_memcpy2(ptr, (const void **)p, copy_size * sizeof(void *));
	ft_strfree((char **)p);
	return (ptr);
}
