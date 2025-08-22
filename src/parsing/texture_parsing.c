/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:41:43 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/22 12:06:34 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parses a texture line, checks for duplicates,
// extracts and stores the texture path
int	parse_texture_line(t_parse_helper *helper)
{
	char	*tmp;

	if (*(helper->count) > 0)
		return (print_error("Duplicate texture identifier", 1));
	(*(helper->count))++;
	tmp = extract_data(helper->line, helper->type);
	if (!tmp)
		return (print_error("Invalid texture path", 1));
	helper->init_data->textures_paths[helper->index] = ft_strdup(tmp);
	free(tmp);
	if (!helper->init_data->textures_paths[helper->index])
		return (print_error("Memory error", 1));
	return (0);
}

// Parses a color line, checks for duplicates,
// extracts and stores the color string
int	parse_color_line(t_parse_helper *helper)
{
	char	*tmp;

	if (*(helper->count) > 0)
		return (print_error("Duplicate color identifier", 1));
	(*(helper->count))++;
	tmp = extract_data(helper->line, helper->type);
	if (!tmp)
		return (print_error("Invalid color value", 1));
	*(helper->color_str) = ft_strdup(tmp);
	free(tmp);
	if (!*(helper->color_str))
		return (print_error("Memory error", 1));
	return (0);
}

// Initializes the helper struct for texture parsing
void	setup_texture_helper(t_parse_helper *helper, char *type,
		int *count, int index)
{
	helper->type = type;
	helper->count = count;
	helper->index = index;
	helper->color_str = NULL;
}

// Initializes the helper struct for color parsing
void	setup_color_helper(t_parse_helper *helper, char *type,
		int *count, char **color_str)
{
	helper->type = type;
	helper->count = count;
	helper->color_str = color_str;
	helper->index = 0;
}

// Checks if the line contains a texture identifier and parses it if found
int	parse_texture_types(t_parse_helper *helper, char *line,
		int *map_found, int *counts)
{
	if (!*map_found && check_for_type(line, "NO "))
	{
		setup_texture_helper(helper, "NO ", &counts[0], 0);
		return (parse_texture_line(helper));
	}
	else if (!*map_found && check_for_type(line, "SO "))
	{
		setup_texture_helper(helper, "SO ", &counts[1], 1);
		return (parse_texture_line(helper));
	}
	else if (!*map_found && check_for_type(line, "WE "))
	{
		setup_texture_helper(helper, "WE ", &counts[2], 2);
		return (parse_texture_line(helper));
	}
	else if (!*map_found && check_for_type(line, "EA "))
	{
		setup_texture_helper(helper, "EA ", &counts[3], 3);
		return (parse_texture_line(helper));
	}
	return (-1);
}
