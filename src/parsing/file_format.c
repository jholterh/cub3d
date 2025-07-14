/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:21:51 by jholterh          #+#    #+#             */
/*   Updated: 2025/07/12 17:11:17 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     check_file_format(char *file)
{
    int     str_len;
    int     fd;
    int     i;
    char    *line;
    char    **data;
    
    if (!file)
        return (print_error("File is NULL", 1));
    str_len = ft_strlen(file);
    if (str_len < 4 || ft_strncmp(file + str_len - 4, ".cub", 4))
        return (print_error("Filetype needs to be .cub", 1));
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (print_error("File could not be opened", 1));
    data = malloc(sizeof(char *));
    if (!data)
        return (print_error("Malloc failed", 1));
    i = 1;
    while (1)
    {
        line = ft_get_next_line(fd);
        data[i - 1] = line;
        i++;
        if (!line)
            break ;
        data = ft_realloc2(data, i, i - 1);
        if (!data)
            return (print_error("Malloc failed", 1));
    }
    return (0);
}
