#include "cub3d.h"

// Frees the grid memory in case of an error during reallocation.
static void	free_grid_on_error(t_parsing_help *parsing_help, int map_height)
{
	int	j;

	j = 0;
	while (j < map_height)
	{
		free(parsing_help->grid[j]);
		j++;
	}
	free(parsing_help->grid);
	parsing_help->grid = NULL;
}

// Reallocates the grid to accommodate more lines.
// Returns 0 on success, or 1 on failure.
static int	realloc_grid(t_init_data *init_data, t_parsing_help *parsing_help)
{
	char	**new_grid;

	new_grid = realloc(parsing_help->grid,
			(init_data->map_height + 50) * sizeof(char *));
	if (!new_grid)
	{
		free_grid_on_error(parsing_help, init_data->map_height);
		return (print_error("Realloc failed", 1));
	}
	parsing_help->grid = new_grid;
	return (0);
}

// Adds a line to the grid and updates map dimensions.
// Returns 0 on success, or 1 on failure.
static int	add_line_to_grid(t_init_data *init_data, t_parsing_help *parsing_help, char *line)
{
	int	line_width;

	parsing_help->grid[init_data->map_height] = ft_strdup(line);
	if (!parsing_help->grid[init_data->map_height])
	{
		free_grid_on_error(parsing_help, init_data->map_height);
		return (print_error("Memory allocation failed for map line", 1));
	}
	line_width = ft_strlen(line);
	if (line_width > init_data->map_width)
		init_data->map_width = line_width;
	init_data->map_height++;
	return (0);
}

// Handles a map line by reallocating the grid if needed,
// adding the line to the grid, and updating map dimensions.
int	handle_map_line(t_init_data *init_data, t_parsing_help *parsing_help, char *line)
{
	if (init_data->map_height % 50 == 0)
	{
		if (realloc_grid(init_data, parsing_help))
			return (1);
	}
	if (add_line_to_grid(init_data, parsing_help, line))
		return (1);
	return (0);
}