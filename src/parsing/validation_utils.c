/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:01:07 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 11:02:03 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_paths(char **textures_paths)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (access(textures_paths[i], F_OK) == -1)
			return (print_error("Texture file does not exist.", 1));
		if (access(textures_paths[i], R_OK) == -1)
			return (print_error("Texture file is not readable.", 1));
	}
	return (0);
}

static void	pad_row_if_needed(char **row, int map_width)
{
	int		len;
	int		j;
	char	*new_row;

	len = ft_strlen(*row);
	if (len < map_width)
	{
		new_row = malloc(map_width + 1);
		if (!new_row)
			return ;
		ft_strlcpy(new_row, *row, len + 1);
		j = len;
		while (j < map_width)
			new_row[j++] = ' ';
		new_row[map_width] = '\0';
		free(*row);
		*row = new_row;
	}
}

void	pad_map_rows(char **char_grid, int map_height, int map_width)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		pad_row_if_needed(&char_grid[i], map_width);
		i++;
	}
}

static int	validate_colors(t_parsing_help *parsing_help)
{
	if (extract_colors(parsing_help->ground_color_str,
			parsing_help->ground_color)
		|| extract_colors(parsing_help->sky_color_str,
			parsing_help->sky_color))
		return (1);
	return (0);
}

static int	validate_and_init_grid(t_init_data *init_data,
		t_parsing_help *parsing_help)
{
	init_data->grid = allocate_int_grid(init_data->map_height,
			init_data->map_width);
	if (!init_data->grid)
		return (print_error("Grid allocation failed", 1));
	pad_map_rows(parsing_help->grid, init_data->map_height,
		init_data->map_width);
	return (0);
}

int	validate_textures_parse(t_init_data *init_data,
		t_parsing_help *parsing_help)
{
	if (get_textures(init_data, parsing_help))
		return (1);
	// Uncomment if you want to check texture files exist/readable:
	// if (check_texture_paths(init_data->textures_paths))
	// 	return (1);
	if (validate_colors(parsing_help))
		return (1);
	put_colors_in_int(parsing_help->ground_color, &init_data->ground_color);
	put_colors_in_int(parsing_help->sky_color, &init_data->sky_color);
	if (validate_and_init_grid(init_data, parsing_help))
		return (1);
	if (create_map(parsing_help->grid, init_data->grid, init_data))
		return (1);
	if (flood_it_all(init_data->grid, init_data->map_height,
			init_data->map_width))
		return (1);
	return (0);
}
