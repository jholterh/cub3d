/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:17:04 by jholterh          #+#    #+#             */
/*   Updated: 2025/07/12 16:34:34 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     print_error(const char *error_msg, const int return_code)
{
    printf(COLOR_RED "ERROR: %s\n" COLOR_RESET, error_msg);
    return (return_code);
}