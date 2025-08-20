#include "cub3d.h"

// Sets the player's position and direction based on the character.
// Returns 0 on success, or 1 if multiple player positions are found.
static int	set_player_position(t_init_data *init_data, int i, int j, char c)
{
	if (init_data->player_pos_x != -1)
		return (print_error("Multiple player start positions found", 1));
	init_data->player_pos_x = j;
	init_data->player_pos_y = i;
	if (c == 'N')
		init_data->camera_direction = 1.5707963267948966;
	else if (c == 'S')
		init_data->camera_direction = 4.71238898038469;
	else if (c == 'E')
		init_data->camera_direction = 0.0;
	else if (c == 'W')
		init_data->camera_direction = 3.141592653589793;
	return (0);
}


// Processes a single character in the map, updating the int grid and player data.
// Returns 0 on success, or 1 on failure.
static int	process_char(char **char_grid, int **int_grid, t_init_data *init_data, int i, int j)
{
	if (char_grid[i][j] == '1')
		int_grid[i][j] = 1; // Wall
	else if (char_grid[i][j] == '0')
		int_grid[i][j] = 0; // Empty space
    else if (char_grid[i][j] == ' ')
        int_grid[i][j] = -1;
	else if (char_grid[i][j] == 'N' || char_grid[i][j] == 'S' ||
			 char_grid[i][j] == 'E' || char_grid[i][j] == 'W')
	{
		int_grid[i][j] = 2; // Player start position
		if (set_player_position(init_data, i, j, char_grid[i][j]))
			return (1);
	}
	else
		return (print_error("Invalid character in map", 1));
	return (0);
}

// Converts a 2D char map grid to a 2D int grid, setting wall, empty, and player positions.
// Also sets player position and direction in init_data.
// Returns 0 on success, or prints an error and returns 1 on failure.
int create_map(char **char_grid, int **int_grid, t_init_data *init_data)
{
    int i, j;

    if (!char_grid || !int_grid)
        return (print_error("Invalid grid pointers", 1));

    for (i = 0; i < init_data->map_height; i++)
    {
        for (j = 0; j < init_data->map_width; j++)
        {
            if (process_char(char_grid, int_grid, init_data, i, j))
                return (1);
        }
    }

    if (init_data->player_pos_x == -1)
        return (print_error("No player start position found", 1));

    return (0);
}




// Allocates a 2D integer grid of the given height and width.
// Returns pointer to the grid, or NULL on failure.
int **allocate_int_grid(int height, int width)
{
    int **grid = malloc(height * sizeof(int *));
    int i = 0;

    if (!grid)
        return NULL;

    while (i < height)
    {
        grid[i] = ft_calloc(width, sizeof(int));
        if (!grid[i])
        {
            // Free already-allocated rows on failure
            int j = i;
            while (--j >= 0)
                free(grid[j]);
            free(grid);
            return NULL;
        }
        i++;
    }
    return grid;
}
