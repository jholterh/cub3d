#include "cub3d.h"

// Checks if the texture files exist and are readable.
// Returns 0 if all files are valid, otherwise prints an error and returns 1.
static int check_texture_paths(char **textures_paths)
{
    int i;

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








// Validates and parses texture paths, color values, and map data from parsing_help into init_data.
// Returns 0 on success, or prints an error and returns 1 on failure.
int validate_textures_parse(t_init_data *init_data, t_parsing_help *parsing_help)
{
    char **data;

    data = parsing_help->data;

    if (get_textures(init_data, parsing_help))
    {
        return (1);
    }

    // if (check_texture_paths(init_data->textures_paths))
    // {
    //     return (1);
    // }

    if (extract_colors(parsing_help->ground_color_str, parsing_help->ground_color) || 
        extract_colors(parsing_help->sky_color_str, parsing_help->sky_color))
    {
        free(parsing_help->ground_color_str);
        free(parsing_help->sky_color_str);
        return (1);
    }

    put_colors_in_int(parsing_help->ground_color, &init_data->ground_color);
    put_colors_in_int(parsing_help->sky_color, &init_data->sky_color);
    free(parsing_help->ground_color_str);
    free(parsing_help->sky_color_str);
    init_data->grid = allocate_int_grid(init_data->map_height, init_data->map_width);
    if (!init_data->grid)
        return print_error("Grid allocation failed", 1);
    if (create_map(parsing_help->grid, init_data->grid, init_data))
        return (1);
    if (prepare_flood_fill(init_data->grid, init_data->map_height, init_data->map_width))
        return (1);
    printf("Textures:\n");
    printf("NO: %s\n", init_data->textures_paths[0]);
    printf("SO: %s\n", init_data->textures_paths[1]);
    printf("WE: %s\n", init_data->textures_paths[2]);
    printf("EA: %s\n", init_data->textures_paths[3]);
    printf("Ground Color: %d, %d, %d\n", parsing_help->ground_color[0], parsing_help->ground_color[1], parsing_help->ground_color[2]);
    printf("Sky Color: %d, %d, %d\n", parsing_help->sky_color[0], parsing_help->sky_color[1], parsing_help->sky_color[2]);

    printf("Red: %d, Green: %d, Blue: %d\n",
       (init_data->ground_color >> 16) & 0xFF,
       (init_data->ground_color >> 8) & 0xFF,
       init_data->ground_color & 0xFF);

    return (0);
}