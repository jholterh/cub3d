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

int     parsing(int argc, char **argv)
{
    if (argc != 2)
        return (print_error("Usage: %s *.cub", 1));
    if (check_file_format(argv[1]))
        return (1);
    return (0);
}

/*

1. Validate the File Format
    File Extension: Ensure the file ends with .cub. If not, return an error. DONE
    Empty File: Check that the file is not empty. If it is, return an error.
    Line Format: Ensure each line contains valid information or is empty (no invalid characters).
    
2. Parse and Validate Textures
    Texture Identifiers: Look for NO, SO, WE, and EA identifiers. Each must appear exactly once in any order.
    Texture Paths:
    Ensure the texture paths are valid and accessible (e.g., the file exists).
    Store texture paths in the textures_paths array in the following order:
    textures_paths[0]: North (NO)
    textures_paths[1]: South (SO)
    textures_paths[2]: West (WE)
    textures_paths[3]: East (EA)
    Error Handling:
    Missing or duplicate texture identifiers.
    Invalid or missing file paths.
    
3. Parse and Validate Colors
    Floor Color (F):
    Ensure the line starts with F.
    Parse the RGB values (e.g., 220,100,0) and ensure:
    Each value is in the range [0, 255].
    There are exactly three values separated by commas.
    Convert the RGB values into an integer and store in ground_color.
    Ceiling Color (C):
    Same process as F, but store the result in sky_color.
    Error Handling:
    Missing or duplicate F or C identifiers.
    Invalid RGB values or formatting errors.
    
4. Parse and Validate the Map
    Find the Map:
    The map must always be the last element in the file.
    Skip any empty lines or spaces between elements and the map.
    Map Dimensions:
    Determine map_height (number of rows) and map_width (maximum row length).
    Store these values in map_height and map_width.
    Validate Map Characters:
    Allowed characters: 0, 1, N, S, E, W, and spaces.
    Ensure the map contains exactly one player start position (N, S, E, or W).
    Ensure Map is Closed:
    The map must be surrounded by 1 (walls) on all sides.
    Spaces inside the map must not create leaks (e.g., a 0 adjacent to a space is invalid).
    Store Map in grid:
    Allocate a 2D array (int **grid) with dimensions map_height x map_width.
    Convert characters:
    0 → 0 (empty space)
    1 → 1 (wall)
    N, S, E, W → 0 (empty space, but store player position separately)
    Spaces → -1 (to distinguish from valid map elements).
    
5. Parse and Store Player Position
    Find Player Start:
    Locate the character (N, S, E, or W) in the map.
    Store the player’s position in player_pos_x and player_pos_y.
    Determine the initial camera_direction based on the character:
    N → camera_direction = π / 2 (90°)
    S → camera_direction = 3π / 2 (270°)
    E → camera_direction = 0 (0°)
    W → camera_direction = π (180°)
    Error Handling:
    No player start position found.
    More than one player start position.

6. General Error Handling
    Duplicate Identifiers:
    Ensure no identifier (NO, SO, WE, EA, F, C) appears more than once.
    Unknown Identifiers:
    Return an error if any line starts with an unrecognized identifier.
    Empty Lines in the Map:
    Ensure there are no empty lines within the map itself.
    Invalid Characters:
    Return an error if any character outside the allowed set (0, 1, N, S, E, W, spaces) is found.

7. Populate the Struct
    Once all validations are complete, populate the t_init_data struct:

    Textures:
    Assign paths to textures_paths[0] through textures_paths[3].
    Colors:
    Assign floor color to ground_color.
    Assign ceiling color to sky_color.
    Map:
    Assign map_height and map_width.
    Assign the 2D array to grid.
    Player:
    Assign player_pos_x and player_pos_y.
    Assign camera_direction.

8. Example Checklist Flow
    Validate file extension.
    Parse NO, SO, WE, EA textures and validate paths.
    Parse F and C colors and validate RGB values.
    Parse and validate the map:
    Ensure characters are valid.
    Ensure the map is closed.
    Store in grid.
    Locate player position and set direction.
    Populate the t_init_data struct.

*/