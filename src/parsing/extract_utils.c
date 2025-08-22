/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:54:03 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/22 11:45:22 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Extracts and validates a substring from 'str'
// after skipping 'type_len' characters.
// Ensures only spaces follow the extracted word,
// otherwise prints an error and returns NULL.
static char	*extract_and_validate(char *str, int type_len)
{
	int		start;
	int		end;
	char	*result;

	str += type_len;
	while (*str && *str == ' ')
		str++;
	start = 0;
	while (str[start] && str[start] != ' ')
		start++;
	end = start;
	while (str[end])
	{
		if (str[end] != ' ')
		{
			printf("invalid char: '%c' in line: %s\n", str[end], str);
			return (NULL);
		}
		end++;
	}
	result = malloc(start + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, start + 1);
	return (result);
}

// Extracts data from 'str' if it starts with 'type', skipping leading spaces.
// Returns the extracted and validated substring, or NULL if not matching.
char	*extract_data(char *str, char *type)
{
	int	type_len;

	type_len = ft_strlen(type);
	while (*str && *str == ' ')
		str++;
	if (ft_strncmp(str, type, type_len) == 0)
		return (extract_and_validate(str, type_len));
	return (NULL);
}

// Checks if the line 'str' contains the specified 'type' at the start
// (ignoring leading spaces).
// Returns 1 if found, 0 otherwise.
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

// Checks if the line 'line' contains any non-space character.
// Prints a message and returns 1 if invalid, 0 if only spaces.
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
