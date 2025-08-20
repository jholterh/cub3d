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


void pad_map_rows(char **char_grid, int map_height, int map_width)
{
    int i, len, j;
    char *new_row;

    for (i = 0; i < map_height; i++)
    {
        len = ft_strlen(char_grid[i]);
        if (len < map_width)
        {
            new_row = malloc(map_width + 1);
            if (!new_row)
                continue; // handle allocation failure as you wish
            ft_strlcpy(new_row, char_grid[i], len + 1); // Copy original content
            // Fill the rest with spaces
            for (j = len; j < map_width; j++)
                new_row[j] = ' ';
            new_row[map_width] = '\0';
            free(char_grid[i]);
            char_grid[i] = new_row;
        }
    }
}

    int flood_fill(int **grid, int x, int y, int height, int width)
    {
        if (x < 0 || x >= height || y < 0 || y >= width)
            return 0;
        if (grid[x][y] == 1) // Wall
            return 0;
        if (grid[x][y] == 0) // Open space reachable from outside: INVALID!
            return 1;
        if (grid[x][y] == 5) // Already visited
            return 0;

        grid[x][y] = 5; // Mark as visited

        // Recursively fill adjacent cells; if any return 1, propagate error
        if (flood_fill(grid, x - 1, y, height, width)) return 1;
        if (flood_fill(grid, x + 1, y, height, width)) return 1;
        if (flood_fill(grid, x, y - 1, height, width)) return 1;
        if (flood_fill(grid, x, y + 1, height, width)) return 1;

        return 0;
    }


    int flood_fill_outside(int **grid, int height, int width)
    {
        int i, j;

        // Start from left and right edges
        for (i = 0; i < height; i++) {
            if (grid[i][0] != 1 && flood_fill(grid, i, 0, height, width))
                return print_error("Invalid map: 0 is reachable from outside", 1);
            if (grid[i][width - 1] != 1 && flood_fill(grid, i, width - 1, height, width))
                return print_error("Invalid map: 0 is reachable from outside", 1);
        }

        // Start from top and bottom edges
        for (j = 0; j < width; j++) {
            if (grid[0][j] != 1 && flood_fill(grid, 0, j, height, width))
                return print_error("Invalid map: 0 is reachable from outside", 1);
            if (grid[height - 1][j] != 1 && flood_fill(grid, height - 1, j, height, width))
                return print_error("Invalid map: 0 is reachable from outside", 1);
        }

        return 0; // Valid map
    }







// Validates and parses texture paths, color values, and map data from parsing_help into init_data.
// Returns 0 on success, or prints an error and returns 1 on failure.
int validate_textures_parse(t_init_data *init_data, t_parsing_help *parsing_help)
{
    char **data;

    data = parsing_help->data;

    if (get_textures(init_data, parsing_help))
        return (1);

    // if (check_texture_paths(init_data->textures_paths))
    //     return (1);

    if (extract_colors(parsing_help->ground_color_str, parsing_help->ground_color) ||
        extract_colors(parsing_help->sky_color_str, parsing_help->sky_color))
    {
        // DO NOT free ground_color_str or sky_color_str here!
        return (1);
    }

    put_colors_in_int(parsing_help->ground_color, &init_data->ground_color);
    put_colors_in_int(parsing_help->sky_color, &init_data->sky_color);

    // DO NOT free ground_color_str or sky_color_str here!

    init_data->grid = allocate_int_grid(init_data->map_height, init_data->map_width);
    if (!init_data->grid)
        return print_error("Grid allocation failed", 1);

    pad_map_rows(parsing_help->grid, init_data->map_height, init_data->map_width);

    if (create_map(parsing_help->grid, init_data->grid, init_data))
        return (1);

    if (prepare_flood_fill(init_data->grid, init_data->map_height, init_data->map_width))
        return (1);
    if (flood_fill_outside(init_data->grid, init_data->map_height, init_data->map_width))
        return (print_error("Invalid map: 0 is reachable from outside", 1));
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
