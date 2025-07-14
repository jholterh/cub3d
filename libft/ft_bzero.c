/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:48:17 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/19 14:30:12 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// same as memset but its always zeros.

#include "libft.h"

void	ft_bzero(void *ptr, size_t len)
{
	ft_memset(ptr, 0, len);
}
