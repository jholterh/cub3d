/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:58:42 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 09:02:53 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(t_mapinfo *map, int y, int x);

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
