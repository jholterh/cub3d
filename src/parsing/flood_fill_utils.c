#include "cub3d.h"

// Flood fill walls: marks all connected 1s as 4, uses (y, x) as (row, col)
void flood_fill_wall(int **grid, int height, int width, int y, int x) {
    if (y < 0 || y >= height || x < 0 || x >= width)
        return; // Out of bounds

    if (grid[y][x] != 1)
        return;

    grid[y][x] = 4;

    flood_fill_wall(grid, height, width, y + 1, x);
    flood_fill_wall(grid, height, width, y - 1, x);
    flood_fill_wall(grid, height, width, y, x + 1);
    flood_fill_wall(grid, height, width, y, x - 1);
}

// Main flood fill: returns 1 on error (e.g., leak), 0 on success
int flood_fill(int **grid, int height, int width, int y, int x)
{
    if (y < 0 || y >= height || x < 0 || x >= width)
        return 1; // Out of bounds = leak

    if (grid[y][x] == 3 || grid[y][x] == 4)
        return 0; // Already visited/marked

    if (grid[y][x] == -1)
        return 1; // Leak: reached uninitialized/outside space

    if (grid[y][x] == 1) {
        grid[y][x] = 4;
        flood_fill_wall(grid, height, width, y + 1, x);
        flood_fill_wall(grid, height, width, y - 1, x);
        flood_fill_wall(grid, height, width, y, x + 1);
        flood_fill_wall(grid, height, width, y, x - 1);
        return 0;
    }

    // FIX: Flood from both 0 (open) and 2 (player start)
    if (grid[y][x] == 0 || grid[y][x] == 2) {
        grid[y][x] = 3; // Mark as visited
        if (flood_fill(grid, height, width, y + 1, x)) return 1;
        if (flood_fill(grid, height, width, y - 1, x)) return 1;
        if (flood_fill(grid, height, width, y, x + 1)) return 1;
        if (flood_fill(grid, height, width, y, x - 1)) return 1;
        return 0;
    }

    return 0; // Not open space
}






int **allocate_help_map(int height, int width)
{
	int **help_map = malloc(height * sizeof(int *));
	if (!help_map)
		return NULL;
	for (int i = 0; i < height; i++)
	{
		help_map[i] = malloc(width * sizeof(int));
		if (!help_map[i])
		{
			for (int j = 0; j < i; j++)
				free(help_map[j]);
			free(help_map);
			return NULL;
		}
	}
	return help_map;
}

void free_help_map(int **help_map, int height)
{
	if (!help_map)
		return;
	for (int i = 0; i < height; i++)
		free(help_map[i]);
	free(help_map);
}

int flood_it_all(int **grid, int height, int width)
{
    int **help_map = allocate_help_map(height, width);
    if (!help_map)
        return print_error("Malloc failed for help_map", 1);

    // Initialize the helper map
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            help_map[i][j] = grid[i][j];

    // Flood fill from player start position 2
    int found_player = 0;
    for (int i = 0; i < height && !found_player; i++)
        for (int j = 0; j < width && !found_player; j++)
            if (help_map[i][j] == 2) {
                if (flood_fill(help_map, height, width, i, j)) {
                    free_help_map(help_map, height);
                    return print_error("Flood fill failed", 1);
                }
                found_player = 1;
            }

    if (!found_player) {
        free_help_map(help_map, height);
        return print_error("No player start found", 1);
    }

// Only allow -1, 2, 4. Error if any 0 or 1 remains.
for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
        if (help_map[i][j] == 0 || help_map[i][j] == 1) {
            free_help_map(help_map, height);
            return print_error("Map is not closed or has loose walls", 1);
        }


    free_help_map(help_map, height);
    return 0; // Success!
}
