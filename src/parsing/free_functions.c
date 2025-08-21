/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:50:31 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 15:09:14 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Frees the textures and color strings in the init_data and parsing_help structures.
void	free_textures_and_colors(t_init_data *init_data,
    t_parsing_help *parsing_help)
{
    int	i;

    i = 0;
    while (i < 4)
    {
        if (init_data->textures_paths[i])
            free(init_data->textures_paths[i]);
        i++;
    }
    if (parsing_help->ground_color_str)
        free(parsing_help->ground_color_str);
    if (parsing_help->sky_color_str)
        free(parsing_help->sky_color_str);
}

// Frees the memory allocated for the map grid (array of strings).
void	free_map_grid(char **grid, int map_height)
{
    int	i;

    if (!grid)
        return ;
    i = 0;
    while (i < map_height)
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}

// Frees the memory allocated for the integer grid (2D array of ints).
void	free_int_grid(int **grid, int height)
{
    int	i;

    if (!grid)
        return ;
    i = 0;
    while (i < height)
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}

// Cleans up all allocated memory after parsing, including grids, textures, and helper structures.
int	parsing_cleanup(t_init_data *init_data,
    t_parsing_help *parsing_help, int exit_code)
{
    int	map_height;

    map_height = 0;
    if (init_data)
        map_height = init_data->map_height;
    if (parsing_help->grid)
        free_map_grid(parsing_help->grid, map_height);
    free_textures_and_colors(init_data, parsing_help);
    ft_strfree(parsing_help->data);
    if (init_data)
        free_int_grid(init_data->grid, map_height);
    free(parsing_help);
    free(init_data);
    return (exit_code);
}
