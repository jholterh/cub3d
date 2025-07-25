## cub3d

Cub3D Parsing Utilities
This repository contains a set of utility functions designed to parse and validate input data for a 3D game environment. The code processes texture identifiers, color values, and map data, ensuring the integrity and correctness of the input. These utilities are crucial for building a valid game world and ensuring the player has a smooth experience.

# Features
1. Texture Parsing
Purpose: Extracts and validates texture identifiers (e.g., NO, SO, WE, EA) and ensures there are no duplicates.
Key Functions:
parse_texture_line: Parses texture paths and validates them.
check_texture_paths: Verifies that texture files exist and are readable.

2. Color Parsing
Purpose: Extracts RGB color values for the ground and sky (e.g., F and C identifiers).
Key Functions:
parse_color_line: Validates and extracts color strings.
extract_colors: Converts comma-separated RGB values to integers.
put_colors_in_int: Combines RGB values into a single hexadecimal integer.

3. Map Parsing and Validation
Purpose: Processes the game map grid, validates player start positions, and ensures the map is enclosed (no leaks).
Key Functions:
create_map: Converts a 2D character grid into a 2D integer grid for the game engine.
set_player_position: Validates and sets the player's starting position.
prepare_flood_fill: Uses a flood-fill algorithm to check for map leaks.

4. Memory Management
Purpose: Ensures efficient memory allocation and cleanup for grids and helper structures.
Key Functions:
allocate_int_grid: Allocates memory for the game grid.
free_grid_on_error: Cleans up allocated memory in case of errors.
allocate_help_map and free_help_map: Manage helper map memory for flood-fill validation.
Code Workflow
Input Parsing

Input data is processed line by line to identify texture paths, colors, and map data.
Functions like check_and_parse_line and get_textures handle this process.
Validation

Duplicate texture identifiers and invalid characters are flagged.
Texture paths are checked for existence and readability.
RGB values are validated to ensure they fall within the range of 0-255.
Map Handling

The map grid is constructed and validated.
Player positions are identified and set.
A flood-fill algorithm ensures the map is enclosed and free of leaks.
Error Handling

Comprehensive error messages are printed for invalid inputs or memory allocation failures.
Memory is freed appropriately to avoid leaks.