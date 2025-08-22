/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:00:27 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/22 12:08:16 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if a line is empty or contains only whitespace
int	check_empty_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\n')
			return (0);
		j++;
	}
	return (1);
}

// Checks if there is any invalid data after the map section
int	check_map_over_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\n')
			return (print_error("Invalid data after map section", 1));
		j++;
	}
	return (0);
}

// Validates that all required textures and colors have been parsed
int	validate_textures(t_init_data *init_data,
		t_parsing_help *parsing_help)
{
	if (init_data->textures_paths[0] == NULL
		|| init_data->textures_paths[1] == NULL
		|| init_data->textures_paths[2] == NULL
		|| init_data->textures_paths[3] == NULL
		|| parsing_help->ground_color_str == NULL
		|| parsing_help->sky_color_str == NULL)
		return (print_error("Invalid texture identifiers", 1));
	return (0);
}
