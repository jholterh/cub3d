/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:58:42 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/22 11:51:12 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Allocates a 2D integer array for use as a helper map.
 * Returns a pointer to the allocated 2D array, or NULL on failure.
 */
int	**allocate_help_map(int height, int width)
{
	int	**help_map;
	int	i;
	int	j;

	help_map = malloc(height * sizeof(int *));
	if (!help_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		help_map[i] = malloc(width * sizeof(int));
		if (!help_map[i])
		{
			j = 0;
			while (j < i)
			{
				free(help_map[j]);
				j++;
			}
			free(help_map);
			return (NULL);
		}
		i++;
	}
	return (help_map);
}

/**
 * Frees a previously allocated 2D integer helper map.
 */
void	free_help_map(int **help_map, int height)
{
	int	i;

	if (!help_map)
		return ;
	i = 0;
	while (i < height)
	{
		free(help_map[i]);
		i++;
	}
	free(help_map);
}

/**
 * Checks if the map is closed by searching for any remaining open or wall cells.
 * Returns 1 if open or wall cells are found, otherwise 0.
 */
static int	check_map_closed(t_mapinfo *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 0 || map->grid[i][j] == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * Copies the contents of the original grid into the helper map.
 * Returns 0 on success.
 */
int	init_help_map(int **grid, int **help_map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			help_map[i][j] = grid[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * Performs the full flood fill check and validates the map.
 * Returns 1 and prints an error message if the map is invalid, otherwise 0.
 */
int	flood_it_all_check(t_mapinfo *map, int **help_map, int height)
{
	int	player_status;

	player_status = find_player_and_flood(map);
	if (player_status == 1)
	{
		free_help_map(help_map, height);
		return (print_error("Flood fill failed", 1));
	}
	if (player_status == 2)
	{
		free_help_map(help_map, height);
		return (print_error("No player start found", 1));
	}
	if (check_map_closed(map))
	{
		free_help_map(help_map, height);
		return (print_error("Map is not closed or has loose walls", 1));
	}
	free_help_map(help_map, height);
	return (0);
}
