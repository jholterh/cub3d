/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:16:26 by jholterh          #+#    #+#             */
/*   Updated: 2025/07/12 16:59:09 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

// Define color constants
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_RESET "\033[0m"

typedef struct s_init_data
{
    char    **textures_paths;
    int     sky_color;
    int     ground_color;
    int     player_pos_x;
    int     player_pos_y;
    double  camera_direction;
    int     map_height;
    int     map_width;
    int     **grid;
}   t_init_data;

//PARSING
// utils
int     print_error(const char *error_msg, const int return_code);

// start
int     parsing(int argc, char **argv);

// file format
int     check_file_format(char *file);

#endif