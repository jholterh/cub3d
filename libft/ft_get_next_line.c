/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:07:46 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/27 17:35:03 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	append_to_finalstring(char **final_line, char data)
{
	int	line_len;

	line_len = ft_strlen(*final_line);
	*final_line = ft_realloc(*final_line, line_len + 2, line_len + 1);
	if (!*final_line)
		return ;
	(*final_line)[line_len] = data;
	(*final_line)[line_len + 1] = '\0';
}

int	check_input(char **final_line, char *buffer, char *hold, int opt)
{
	int		i;
	char	*str;

	if (opt == 1)
		str = hold;
	else
		str = buffer;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			append_to_finalstring(final_line, str[i]);
			i++;
			ft_memcpy(hold, str + i, ft_strlen(str + i) + 1);
			return (1);
		}
		append_to_finalstring(final_line, str[i]);
		i++;
	}
	if (opt == 1)
		hold[0] = '\0';
	return (0);
}

static char	*read_errors(char *final_line, char *buffer, ssize_t bytes_read)
{
	if (final_line[0] == '\0' && bytes_read == 0)
	{
		free(final_line);
		free(buffer);
		return (NULL);
	}
	if (bytes_read == -1)
	{
		free(buffer);
		free(final_line);
		return (NULL);
	}
	free(buffer);
	return (final_line);
}

static char	*read_process(int fd, char *final_line, char *buffer, char *hold)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (check_input(&final_line, buffer, hold, 2) == 1)
		{
			free(buffer);
			return (final_line);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (read_errors(final_line, buffer, bytes_read));
}

char	*ft_get_next_line(int fd)
{
	char		*buffer;
	char		*final_line;
	static char	hold[BUFFER_SIZE + 1];

	final_line = (char *)malloc(1);
	if (!final_line)
		return (NULL);
	final_line[0] = '\0';
	if (check_input(&final_line, NULL, hold, 1) == 1)
		return (final_line);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(final_line);
		return (NULL);
	}
	return (read_process(fd, final_line, buffer, hold));
}
