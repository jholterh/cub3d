/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:04:56 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 15:10:03 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Frees the grid memory in case of an error during reallocation.
 *
 * @param parsing_help Pointer to the parsing helper structure containing the grid.
 * @param map_height   The current height of the map (number of lines allocated).
 */
static void	free_grid_on_error(t_parsing_help *parsing_help, int map_height)
{
	int	i;

	if (!parsing_help->grid)
		return;
	i = 0;
	while (i < map_height)
	{
		free(parsing_help->grid[i]);
		i++;
	}
	free(parsing_help->grid);
	parsing_help->grid = NULL;
}

/**
 * Reallocates the grid to accommodate more lines.
 *
 * @param init_data     Pointer to the initialization data structure containing map dimensions.
 * @param parsing_help  Pointer to the parsing helper structure containing the grid.
 * @return              0 on success, or 1 on failure.
 */
static int	realloc_grid(t_init_data *init_data, t_parsing_help *parsing_help)
{
	char	**new_grid;
	int		i;

	new_grid = (char **)malloc(sizeof(char *) * (init_data->map_height + 2));
	if (!new_grid)
		return (1);
	i = 0;
	while (i < init_data->map_height)
	{
		new_grid[i] = parsing_help->grid[i];
		i++;
	}
	new_grid[i] = NULL;
	free(parsing_help->grid);
	parsing_help->grid = new_grid;
	return (0);
}

/**
 * Adds a line to the grid and updates map dimensions.
 *
 * @param init_data     Pointer to the initialization data structure containing map dimensions.
 * @param parsing_help  Pointer to the parsing helper structure containing the grid.
 * @param line          The line to add to the grid.
 * @return              0 on success, or 1 on failure.
 */
static int	add_line_to_grid(t_init_data *init_data,
	t_parsing_help *parsing_help, char *line)
{
	parsing_help->grid[init_data->map_height] = ft_strdup(line);
	if (!parsing_help->grid[init_data->map_height])
	{
		free_grid_on_error(parsing_help, init_data->map_height);
		return (1);
	}
	parsing_help->grid[init_data->map_height + 1] = NULL;
	init_data->map_height++;
	if ((int)ft_strlen(line) > init_data->map_width)
		init_data->map_width = (int)ft_strlen(line);
	return (0);
}

/**
 * Handles a map line by reallocating the grid if needed, adding the line to the grid,
 * and updating map dimensions.
 *
 * @param init_data     Pointer to the initialization data structure containing map dimensions.
 * @param parsing_help  Pointer to the parsing helper structure containing the grid.
 * @param line          The map line to handle.
 * @return              0 on success, or 1 on failure.
 */
int	handle_map_line(t_init_data *init_data,
	t_parsing_help *parsing_help, char *line)
{
	if (realloc_grid(init_data, parsing_help))
		return (1);
	if (add_line_to_grid(init_data, parsing_help, line))
		return (1);
	return (0);
}
