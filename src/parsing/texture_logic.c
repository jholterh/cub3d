/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:02:35 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/22 12:07:55 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if the line contains a color identifier and parses it if found
int	parse_color_types(t_parse_helper *helper, char *line,
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
int	check_and_parse_line(t_init_data *init_data,
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

// Handles logic for processing map lines and detecting section transitions
int	process_map_logic(t_parsing_help *parsing_help, int *i,
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

// Pads a single map row with spaces if it's shorter than map_width
void	pad_row_if_needed(char **row, int map_width)
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
