/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:58:42 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 15:07:17 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(t_mapinfo *map, int y, int x);

/**
 * Recursively marks all connected wall cells (value 1) as visited (value 4)
 * starting from the given coordinates (y, x).
 * Used to mark all contiguous wall cells to prevent revisiting them
 * during the flood fill process.
 */
void	flood_fill_wall(t_mapinfo *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->grid[y][x] != 1)
		return ;
	map->grid[y][x] = 4;
	flood_fill_wall(map, y + 1, x);
	flood_fill_wall(map, y - 1, x);
	flood_fill_wall(map, y, x + 1);
	flood_fill_wall(map, y, x - 1);
}

/**
 * Recursively performs flood fill on open cells (value 0 or 2),
 * marking them as visited (value 3).
 * Returns 1 if an open boundary or invalid cell is found, otherwise 0.
 * Used internally by flood_fill to check for map closure.
 */
static int	flood_fill_open(t_mapinfo *map, int y, int x)
{
	map->grid[y][x] = 3;
	if (flood_fill(map, y + 1, x))
		return (1);
	if (flood_fill(map, y - 1, x))
		return (1);
	if (flood_fill(map, y, x + 1))
		return (1);
	if (flood_fill(map, y, x - 1))
		return (1);
	return (0);
}

/**
 * Main flood fill function that checks map closure and wall connectivity.
 * Returns 1 if the flood fill reaches an invalid cell or open boundary, otherwise 0.
 * Marks visited open cells as 3 and walls as 4.
 */
int	flood_fill(t_mapinfo *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (1);
	if (map->grid[y][x] == 3 || map->grid[y][x] == 4)
		return (0);
	if (map->grid[y][x] == -1)
		return (1);
	if (map->grid[y][x] == 1)
	{
		map->grid[y][x] = 4;
		flood_fill_wall(map, y + 1, x);
		flood_fill_wall(map, y - 1, x);
		flood_fill_wall(map, y, x + 1);
		flood_fill_wall(map, y, x - 1);
		return (0);
	}
	if (map->grid[y][x] == 0 || map->grid[y][x] == 2)
		return (flood_fill_open(map, y, x));
	return (0);
}

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
 * Finds the player start position (cell value 2) and initiates flood fill.
 * Returns 1 if flood fill fails, 2 if no player start is found, otherwise 0.
 */
static int	find_player_and_flood(t_mapinfo *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 2)
			{
				if (flood_fill(map, i, j))
					return (1);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (2);
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
static int	init_help_map(int **grid, int **help_map, int height, int width)
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
static int	flood_it_all_check(t_mapinfo *map, int **help_map, int height)
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

/**
 * Entry point for flood fill validation of the map.
 * Allocates a helper map, copies the grid, and checks if the map is closed and valid.
 * Returns 1 and prints an error message if the map is invalid, otherwise 0.
 */
int	flood_it_all(int **grid, int height, int width)
{
	t_mapinfo	map;
	int			**help_map;

	help_map = allocate_help_map(height, width);
	if (!help_map)
		return (print_error("Malloc failed for help_map", 1));
	init_help_map(grid, help_map, height, width);
	map.grid = help_map;
	map.height = height;
	map.width = width;
	return (flood_it_all_check(&map, help_map, height));
}
