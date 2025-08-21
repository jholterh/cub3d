/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:41:43 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 15:00:03 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Helper struct to pass parsing context and data between functions
typedef struct s_parse_helper
{
	char			*type;
	int				*count;
	int				index;
	char			**color_str;
	t_init_data		*init_data;
	t_parsing_help	*parsing_help;
	char			*line;
}	t_parse_helper;

// Parses a texture line, checks for duplicates, extracts and stores the texture path
static int	parse_texture_line(t_parse_helper *helper)
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

// Parses a color line, checks for duplicates, extracts and stores the color string
static int	parse_color_line(t_parse_helper *helper)
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
static void	setup_texture_helper(t_parse_helper *helper, char *type,
		int *count, int index)
{
	helper->type = type;
	helper->count = count;
	helper->index = index;
	helper->color_str = NULL;
}

// Initializes the helper struct for color parsing
static void	setup_color_helper(t_parse_helper *helper, char *type,
		int *count, char **color_str)
{
	helper->type = type;
	helper->count = count;
	helper->color_str = color_str;
	helper->index = 0;
}

// Checks if the line contains a texture identifier and parses it if found
static int	parse_texture_types(t_parse_helper *helper, char *line,
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

// Checks if the line contains a color identifier and parses it if found
static int	parse_color_types(t_parse_helper *helper, char *line,
		int *map_found, int *counts)
{
	if (!*map_found && check_for_type(line, "F "))
	{
		setup_color_helper(helper, "F ", &counts[4],
			&helper->parsing_help->ground_color_str);
		return (parse_color_line(helper));
	}
	else if (!*map_found && check_for_type(line, "C "))
	{
		setup_color_helper(helper, "C ", &counts[5],
			&helper->parsing_help->sky_color_str);
		return (parse_color_line(helper));
	}
	return (-1);
}

// Checks and parses a line for texture, color, or map data
static int	check_and_parse_line(t_init_data *init_data,
		t_parsing_help *parsing_help, char *line, int *map_found)
{
	static int		counts[6] = {0, 0, 0, 0, 0, 0};
	t_parse_helper	helper;
	int				result;

	helper.init_data = init_data;
	helper.parsing_help = parsing_help;
	helper.line = line;
	result = parse_texture_types(&helper, line, map_found, counts);
	if (result != -1)
		return (result);
	result = parse_color_types(&helper, line, map_found, counts);
	if (result != -1)
		return (result);
	if (check_for_type(line, "1") || check_for_type(line, "0"))
		return (*map_found = 1, handle_map_line(init_data, parsing_help, line));
	else if (check_line_invalid(line))
		return (print_error("Line contains invalid characters", 1));
	return (0);
}

// Checks if a line is empty or contains only whitespace
static int	check_empty_line(char *line)
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
static int	check_map_over_line(char *line)
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

// Handles logic for processing map lines and detecting section transitions
static int	process_map_logic(t_parsing_help *parsing_help, int *i,
		int *map_found, int *map_over)
{
	if (*map_found && !*map_over)
	{
		if (check_empty_line(parsing_help->data[*i]))
		{
			*map_over = 1;
			(*i)++;
			return (1);
		}
	}
	if (*map_over)
	{
		if (check_map_over_line(parsing_help->data[*i]))
			return (-1);
		(*i)++;
		return (1);
	}
	return (0);
}

// Validates that all required textures and colors have been parsed
static int	validate_textures(t_init_data *init_data,
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

// Main function to process all lines for textures, colors, and map data
int	get_textures(t_init_data *init_data, t_parsing_help *parsing_help)
{
	int	i;
	int	map_found;
	int	map_over;
	int	result;

	i = 0;
	map_found = 0;
	map_over = 0;
	while (parsing_help->data[i])
	{
		result = process_map_logic(parsing_help, &i, &map_found, &map_over);
		if (result == -1)
			return (1);
		if (result == 1)
			continue ;
		if (check_and_parse_line(init_data, parsing_help,
				parsing_help->data[i], &map_found))
			return (1);
		i++;
	}
	return (validate_textures(init_data, parsing_help));
}
