#include "cub3d.h"

// Parses and validates a texture identifier from a line.
// Updates the texture path and ensures no duplicates.
static int	parse_texture(t_init_data *init_data, char *line, char *type, int *count, int index)
{
	if (*count > 0)
		return (print_error("Duplicate texture identifier", 1));
	(*count)++;
	init_data->textures_paths[index] = extract_data(line, type);
	if (!init_data->textures_paths[index])
		return (print_error("Invalid texture path", 1));
	return (0);
}

// Parses texture identifiers (NO, SO, WE, EA) and updates the texture paths.
static int	parse_texture_line(t_init_data *init_data, char *line, char *type, int *count, int index)
{
	if (*count > 0)
		return (print_error("Duplicate texture identifier", 1));
	(*count)++;
	init_data->textures_paths[index] = extract_data(line, type);
	if (!init_data->textures_paths[index])
		return (print_error("Invalid texture path", 1));
	return (0);
}

// Parses color identifiers (F, C) and updates the corresponding color strings.
static int	parse_color_line(t_parsing_help *parsing_help, char *line, char *type, int *count, char **color_str)
{
	if (*count > 0)
		return (print_error("Duplicate color identifier", 1));
	(*count)++;
	*color_str = extract_data(line, type);
	if (!*color_str)
		return (print_error("Invalid color value", 1));
	return (0);
}

// Determines the type of the current line and delegates processing to helpers.
static int	check_and_parse_line(t_init_data *init_data, t_parsing_help *parsing_help, char *line, int *map_found)
{
	static int	no_count = 0, so_count = 0, we_count = 0, ea_count = 0, c_count = 0, f_count = 0;

	if (!*map_found && check_for_type(line, "NO "))
		return (parse_texture_line(init_data, line, "NO ", &no_count, 0));
	else if (!*map_found && check_for_type(line, "SO "))
		return (parse_texture_line(init_data, line, "SO ", &so_count, 1));
	else if (!*map_found && check_for_type(line, "WE "))
		return (parse_texture_line(init_data, line, "WE ", &we_count, 2));
	else if (!*map_found && check_for_type(line, "EA "))
		return (parse_texture_line(init_data, line, "EA ", &ea_count, 3));
	else if (!*map_found && check_for_type(line, "F "))
		return (parse_color_line(parsing_help, line, "F ", &f_count, &parsing_help->ground_color_str));
	else if (!*map_found && check_for_type(line, "C "))
		return (parse_color_line(parsing_help, line, "C ", &c_count, &parsing_help->sky_color_str));
	else if (check_for_type(line, "1") || check_for_type(line, "0"))
	{
		*map_found = 1;
		return (handle_map_line(init_data, parsing_help, line));
	}
	else if (check_line_invalid(line))
		return (print_error("Line contains invalid characters", 1));
	return (0);
}


// Parses the input data lines to extract texture paths and color strings,
// fills the map grid, and checks for duplicates and validity.
// Returns 0 on success, or prints an error and returns 1 on failure.
int	get_textures(t_init_data *init_data, t_parsing_help *parsing_help)
{
	int	i;
	int	map_found;

	i = 0;
	map_found = 0;
	while (parsing_help->data[i])
	{
		if (check_and_parse_line(init_data, parsing_help, parsing_help->data[i], &map_found))
			return (1);
		i++;
	}
	if (init_data->textures_paths[0] == NULL || init_data->textures_paths[1] == NULL
		|| init_data->textures_paths[2] == NULL || init_data->textures_paths[3] == NULL
		|| parsing_help->ground_color_str == NULL || parsing_help->sky_color_str == NULL)
		return (print_error("Invalid texture identifiers", 1));
	return (0);
}