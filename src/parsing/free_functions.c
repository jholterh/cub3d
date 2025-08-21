/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:50:31 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 15:00:45 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// This function frees the textures and colors in the init_data structure
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

// This function frees the grid in the parsing help structure
// It iterates through each row and frees the memory allocated for it
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

// This function frees the integer grid in the init_data structure
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

// This function handles the cleanup process after parsing
// It frees the allocated memory for init_data and parsing_help
// it also frees the grid and textures/colors
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