#include "cub3d.h"

// Extracts the data value following a given type identifier in the string,
// skipping leading spaces. Returns a newly allocated string with the data,
// or NULL if the line is invalid or the type does not match.
static char *extract_and_validate(char *str, int type_len)
{
    int i = 0;
    int start, end;

    str += type_len;
    while (*str && *str == ' ')
        str++;

    start = 0;
    while (str[start] && str[start] != ' ')
        start++;

    end = start;

    // Check for invalid chars after the valid part
    while (str[end])
    {
        if (str[end] != ' ')
        {
            printf("invalid char: '%c' in line: %s\n", str[end], str);
            return (NULL);
        }
        end++;
    }

    // Copy only the valid substring
    char *result = malloc(start + 1);
    if (!result)
        return (NULL);
    ft_strlcpy(result, str, start + 1);
    return result;
}


char    *extract_data(char *str, char *type)
{
    int type_len;

    type_len = ft_strlen(type);
    while (*str && *str == ' ')
        str++;
    if (ft_strncmp(str, type, type_len) == 0)
        return (extract_and_validate(str, type_len));
    return (NULL);
}



// Checks if the given string starts with the specified type identifier,
// ignoring any leading spaces. Returns 1 if it matches, 0 otherwise.
int	check_for_type(char *str, char *type)
{
	int	type_len;

	type_len = ft_strlen(type);
	while (*str && *str == ' ')
		str++;
	if (ft_strncmp(str, type, type_len) == 0)
		return (1);
	return (0);
}


// Checks if a line contains only spaces. If any other character is found,
// prints a warning and returns 1 (invalid), otherwise returns 0 (valid).
int	check_line_invalid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			printf("evil letter: %c\n", line[i]);
			return (1);
		}
		i++;
	}
	printf("line is fine\n");
	return (0);
}