/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:14:24 by jholterh          #+#    #+#             */
/*   Updated: 2025/07/12 16:47:56 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     main(int argc, char **argv)
{
    if (parsing(argc, argv))
        return (print_error("found", 10));
    else
        return (print_error("was not found", 1));
}