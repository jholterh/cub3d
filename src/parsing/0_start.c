/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:32:12 by jholterh          #+#    #+#             */
/*   Updated: 2025/07/12 16:52:11 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_parsing_help(t_parsing_help *parsing_help)
{
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
        return (print_error("Malloc failed for grid", 1));
    }

    return (0);
}

// Initialize main structure
void init_struct(t_init_data *init_data)
{
    init_data->textures_paths[0] = NULL; // NO
    init_data->textures_paths[1] = NULL; // SO
    init_data->textures_paths[2] = NULL; // WE
    init_data->textures_paths[3] = NULL; // EA

    init_data->sky_color = -1;
    init_data->ground_color = -1;

    init_data->player_pos_x = -1;
    init_data->player_pos_y = -1;
    init_data->camera_direction = -1.0;

    init_data->map_height = 0;
    init_data->map_width = 0;

    init_data->grid = NULL;
}

// Parsing function
int parsing(int argc, char **argv)
{
    t_init_data     *init_data = NULL;
    t_parsing_help  *parsing_help = NULL;

    // Check argument count
    if (argc != 2)
        return (print_error("Usage: ./cub3d <file.cub>", 1));

    // Allocate and initialize parsing_help
    parsing_help = malloc(sizeof(t_parsing_help));
    if (!parsing_help)
        return (print_error("Malloc failed for parsing_help", 1));

    if (init_parsing_help(parsing_help))
    {
        free(parsing_help);
        return (1);
    }

    // Check file format
    if (check_file_format(argv[1], &parsing_help->data))
    {
        ft_strfree(parsing_help->data);
        free(parsing_help->grid);
        free(parsing_help);
        return (1);
    }

    // Allocate and initialize init_data
    init_data = malloc(sizeof(t_init_data));
    if (!init_data)
    {
        ft_strfree(parsing_help->data);
        free(parsing_help->grid);
        free(parsing_help);
        return (print_error("Malloc failed for init_data", 1));
    }

    init_struct(init_data);

    // Validate textures and parse data
    if (validate_textures_parse(init_data, parsing_help))
    {
        ft_strfree(parsing_help->data);
        free(parsing_help->grid);
        free(parsing_help);
        free(init_data);
        return (1);
    }

    // Free parsing_help after validation
    ft_strfree(parsing_help->data);
    free(parsing_help->grid);
    free(parsing_help);

    // Free init_data if no longer needed
    free(init_data);

    return (0);
}
