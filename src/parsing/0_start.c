/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:32:12 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 15:03:15 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes the parsing_help structure and allocates memory for its arrays.
// Returns 0 on success, or an error code if allocation fails.
int	init_parsing_help(t_parsing_help *parsing_help)
{
	int	i;

	parsing_help->data = NULL;
	parsing_help->grid = NULL;
	parsing_help->ground_color_str = NULL;
	parsing_help->sky_color_str = NULL;
	parsing_help->ground_color[0] = -1;
	parsing_help->ground_color[1] = -1;
	parsing_help->ground_color[2] = -1;
	parsing_help->sky_color[0] = -1;
	parsing_help->sky_color[1] = -1;
	parsing_help->sky_color[2] = -1;
	parsing_help->data = malloc(50 * sizeof(char *));
	if (!parsing_help->data)
		return (print_error("Malloc failed for data", 1));
	parsing_help->grid = malloc(50 * sizeof(char *));
	if (!parsing_help->grid)
	{
		free(parsing_help->data);
		parsing_help->data = NULL;
		return (print_error("Malloc failed for grid", 1));
	}
	return (0);
}

// Initializes the init_data structure with default values.
void	init_struct(t_init_data *init_data)
{
	init_data->textures_paths[0] = NULL;
	init_data->textures_paths[1] = NULL;
	init_data->textures_paths[2] = NULL;
	init_data->textures_paths[3] = NULL;
	init_data->sky_color = -1;
	init_data->ground_color = -1;
	init_data->player_pos_x = -1;
	init_data->player_pos_y = -1;
	init_data->camera_direction = -1.0;
	init_data->map_height = 0;
	init_data->map_width = 0;
	init_data->grid = NULL;
}

// Initializes parsing by checking arguments, allocating structures, and validating the file.
// Returns 0 on success, or an error code if any step fails.
static int	parsing_init(int argc, char **argv, t_init_data **init_data,
	t_parsing_help **parsing_help)
{
	*init_data = NULL;
	*parsing_help = NULL;
	if (argc != 2)
		return (print_error("Usage: ./cub3d <file.cub>", 1));
	*parsing_help = malloc(sizeof(t_parsing_help));
	if (!*parsing_help)
		return (print_error("Malloc failed for parsing_help", 1));
	if (init_parsing_help(*parsing_help))
		return (parsing_cleanup(NULL, *parsing_help, 1));
	if ((*parsing_help)->data)
		free((*parsing_help)->data);
	if (check_file_format(argv[1], &(*parsing_help)->data))
		return (parsing_cleanup(NULL, *parsing_help, 1));
	*init_data = malloc(sizeof(t_init_data));
	if (!*init_data)
		return (print_error("Malloc failed for init_data", 1)
			+ parsing_cleanup(NULL, *parsing_help, 0));
	init_struct(*init_data);
	return (0);
}

// Main entry point for parsing. Initializes structures, validates textures, and cleans up.
// Returns 1 on error, or 0 on success.
int	parsing(int argc, char **argv)
{
	t_init_data		*init_data;
	t_parsing_help	*parsing_help;

	if (parsing_init(argc, argv, &init_data, &parsing_help))
		return (1);
	if (validate_textures_parse(init_data, parsing_help))
	{
		printf(COLOR_RED "This is where it exits.\n" COLOR_RESET);
		return (parsing_cleanup(init_data, parsing_help, 1));
	}
	return (parsing_cleanup(init_data, parsing_help, 0));
}
