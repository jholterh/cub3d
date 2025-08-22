/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:09:14 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/22 10:19:04 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Sets the player's position and camera direction based on the map character.
 * Returns 1 and prints an error if multiple player positions are found.
 */
static int	set_player_position(t_init_data *init_data, int *pos, char c)
{
	if (init_data->player_pos_x != -1)
		return (print_error("Multiple player start positions found", 1));
	init_data->player_pos_x = pos[1];
	init_data->player_pos_y = pos[0];
	if (c == 'N')
		init_data->camera_direction = 1.5707963267948966;
	else if (c == 'S')
		init_data->camera_direction = 4.71238898038469;
	else if (c == 'E')
		init_data->camera_direction = 0.0;
	else if (c == 'W')
		init_data->camera_direction = 3.141592653589793;
	return (0);
}

/*
 * Processes a single character from the map, updating the int grid and player position.
 * Returns 1 on error, 0 otherwise.
 */
static int	process_char(char **char_grid, int **int_grid,
	t_init_data *init_data, int *pos)
{
	char	c;

	c = char_grid[pos[0]][pos[1]];
	if (c == '1')
		int_grid[pos[0]][pos[1]] = 1;
	else if (c == '0')
		int_grid[pos[0]][pos[1]] = 0;
	else if (c == ' ')
		int_grid[pos[0]][pos[1]] = -1;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		int_grid[pos[0]][pos[1]] = 2;
		if (set_player_position(init_data, pos, c))
			return (1);
	}
	else
		return (print_error("Invalid character in map", 1));
	return (0);
}

/*
 * Converts the character map to an integer grid and sets the player position.
 * Returns 1 on error, 0 on success.
 */
int	create_map(char **char_grid, int **int_grid, t_init_data *init_data)
{
	int	i;
	int	j;
	int	pos[2];

	if (!char_grid || !int_grid)
		return (print_error("Invalid grid pointers", 1));
	i = 0;
	while (i < init_data->map_height)
	{
		j = 0;
		while (j < init_data->map_width)
		{
			pos[0] = i;
			pos[1] = j;
			if (process_char(char_grid, int_grid, init_data, pos))
				return (1);
			j++;
		}
		i++;
	}
	if (init_data->player_pos_x == -1)
		return (print_error("No player start position found", 1));
	return (0);
}

/*
 * Allocates a 2D integer grid of the given height and width.
 * Returns a pointer to the grid, or NULL on allocation failure.
 */
int	**allocate_int_grid(int height, int width)
{
	int	**grid;
	int	i;
	int	j;

	grid = malloc(height * sizeof(int *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = ft_calloc(width, sizeof(int));
		if (!grid[i])
		{
			j = i;
			while (--j >= 0)
				free(grid[j]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	return (grid);
}
