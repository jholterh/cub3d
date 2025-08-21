/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_file_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:21:51 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 08:46:49 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	safe_file_realloc(char ***data, int *i)
{
	char	**tmp;
	int		j;

	tmp = (char **)ft_realloc2((void **)*data, *i, *i + 50);
	if (!tmp)
	{
		print_error("Realloc failed", 1);
		j = *i;
		while (--j >= 0)
			free((*data)[j]);
		free(*data);
		return (1);
	}
	*data = tmp;
	return (0);
}

static void	remove_newline(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '\n')
			str[j] = '\0';
		j++;
	}
}

static int	safe_file(const int fd, char ***data)
{
	int		i;
	char	*line;

	i = 0;
	*data = malloc(50 * sizeof(char *));
	if (!*data)
		return (print_error("Malloc failed", 1));
	while (1)
	{
		line = ft_get_next_line(fd);
		if (line == NULL)
			break ;
		(*data)[i] = line;
		remove_newline((*data)[i]);
		i++;
		if (i % 50 == 0)
		{
			if (safe_file_realloc(data, &i))
				return (1);
		}
	}
	(*data)[i] = NULL;
	return (0);
}

int	check_file_format(char *file, char ***data)
{
	int	str_len;
	int	fd;
	int	i;

	if (!file)
		return (print_error("File is NULL", 1));
	str_len = ft_strlen(file);
	if (str_len < 4 || ft_strncmp(file + str_len - 4, ".cub", 4))
		return (print_error("Filetype needs to be .cub", 1));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error("File could not be opened", 1));
	if (safe_file(fd, data))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (!(*data)[0] || !(*data)[0][0])
	{
		ft_strfree(*data);
		return (print_error("File is empty", 1));
	}
	return (0);
}
