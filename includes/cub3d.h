/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:16:26 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 14:51:48 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"

// Define color constants
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_RESET "\033[0m"

typedef struct s_init_data
{
    char    *textures_paths[4];
    int     sky_color;
    int     ground_color;
    int     player_pos_x;
    int     player_pos_y;
    double  camera_direction;
    int     map_height;
    int     map_width;
    int     **grid;
}   t_init_data;

typedef struct s_parsing_help
{
    char    **data;
    char    *ground_color_str;
    int     ground_color[3];
    char    *sky_color_str;
    int     sky_color[3];
    char    **grid;
}   t_parsing_help;

typedef struct s_mapinfo
{
	int	**grid;
	int	height;
	int	width;
}	t_mapinfo;


//PARSING
// utils
int     print_error(const char *error_msg, const int return_code);

// start
int     parsing(int argc, char **argv);

// file format
int     check_file_format(char *file, char ***data);


// Extraction and utility
int	check_line_invalid(char *line);
char    *extract_data(char *str, char *type);
int	check_for_type(char *str, char *type);


// Grid and map building
int	handle_map_line(t_init_data *init_data, t_parsing_help *parsing_help, char *line);
int **allocate_int_grid(int height, int width);
int	create_map(char **char_grid, int **int_grid, t_init_data *init_data);

// Flood fill (map closure)
int flood_it_all(int **grid, int height, int width);

// textures
int	get_textures(t_init_data *init_data, t_parsing_help *parsing_help);

// Color utilities
void put_colors_in_int(int *seperate_colors, int *colors);
int  extract_colors(char *color_str, int *color);

// Validation and parsing
int validate_textures_parse(t_init_data *init_data, t_parsing_help *parsing_help);

// Free functions
void free_textures_and_colors(t_init_data *init_data, t_parsing_help *parsing_help);
void free_map_grid(char **grid, int map_height);
void free_int_grid(int **grid, int height);
int parsing_cleanup(t_init_data *init_data, t_parsing_help *parsing_help, int exit_code);

#endif