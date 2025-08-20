#include "cub3d.h"

// Recursively checks for map leaks using flood fill. Returns 1 if a leak is found, 0 otherwise.
static int flood_fill(int **help_map, int height, int width, int pos_x, int pos_y)
{
    if (pos_x < 0 || pos_x >= width || pos_y < 0 || pos_y >= height)
        return 1; // Leak found (out of bounds)
    if (help_map[pos_y][pos_x] == 1 || help_map[pos_y][pos_x] == 2)
        return 0; // Wall or already visited
    help_map[pos_y][pos_x] = 2; // Mark as visited

    if (flood_fill(help_map, height, width, pos_x + 1, pos_y)) return 1;
    if (flood_fill(help_map, height, width, pos_x - 1, pos_y)) return 1;
    if (flood_fill(help_map, height, width, pos_x, pos_y + 1)) return 1;
    if (flood_fill(help_map, height, width, pos_x, pos_y - 1)) return 1;
    return 0;
}

// Allocates memory for the helper map.
// Returns the allocated map or NULL if allocation fails.
static int	**allocate_help_map(int height, int width)
{
	int	**help_map;
	int	i;

	help_map = malloc(height * sizeof(int *));
	if (!help_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		help_map[i] = malloc(width * sizeof(int));
		if (!help_map[i])
		{
			while (--i >= 0)
				free(help_map[i]);
			free(help_map);
			return (NULL);
		}
		i++;
	}
	return (help_map);
}

// Processes a single cell in the grid and updates the helper map and player position.
// Returns 0 on success, or 1 if an error occurs (e.g., multiple player positions).
static int	process_cell(int **grid, int **help_map, int i, int j, int *start_x, int *start_y)
{
	if (grid[i][j] == 0)
		help_map[i][j] = 0;
	else if (grid[i][j] == 1)
		help_map[i][j] = 1;
	else if (grid[i][j] == 2)
	{
		help_map[i][j] = 0;
		*start_x = j;
		*start_y = i;
	}
	return (0);
}

// Iterates through the grid to initialize the helper map and find the player's start position.
// Returns 0 on success, or 1 if no player start is found.
static int	initialize_help_map(int **grid, int **help_map, int height, int width,
		int *start_x, int *start_y)
{
	int	i;
	int	j;

	*start_x = -1;
	*start_y = -1;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (process_cell(grid, help_map, i, j, start_x, start_y))
				return (1);
			j++;
		}
		i++;
	}
	if (*start_x == -1 || *start_y == -1)
		return (print_error("No player start", 1));
	return (0);
}


// Frees the memory allocated for the helper map.
static void	free_help_map(int **help_map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(help_map[i]);
		i++;
	}
	free(help_map);
}

int is_flying_wall(int **map, int x, int y, int height, int width) {
    // Only call this for map[y][x] == 1
    int connected = 0;
    // Check up
    if (y > 0 && (map[y-1][x] == 1 || map[y-1][x] == 2)) connected = 1;
    // Check down
    if (y < height-1 && (map[y+1][x] == 1 || map[y+1][x] == 2)) connected = 1;
    // Check left
    if (x > 0 && (map[y][x-1] == 1 || map[y][x-1] == 2)) connected = 1;
    // Check right
    if (x < width-1 && (map[y][x+1] == 1 || map[y][x+1] == 2)) connected = 1;
    return !connected;
}


// Prepares a helper map and runs flood fill to verify the map is closed (no leaks).
// Returns 0 if map is closed, or prints an error and returns 1 if not.
int	prepare_flood_fill(int **grid, int height, int width)
{
	int	**help_map;
	int	start_x;
	int	start_y;
	int	result;

	help_map = allocate_help_map(height, width);
	if (!help_map)
		return (print_error("Malloc failed", 1));
	if (initialize_help_map(grid, help_map, height, width, &start_x, &start_y))
	{
		free_help_map(help_map, height);
		return (1);
	}
	result = 0;
	if (flood_fill(help_map, height, width, start_x, start_y))
		result = print_error("Flood fill failed: map is not closed", 1);
	// Scan the whole help_map for flying walls
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (help_map[y][x] == 1 && is_flying_wall(help_map, x, y, height, width)) {
				result = print_error("Flying wall detected", 1);
				break;
			}
		}
	}

	free_help_map(help_map, height);
	return (result);
}
