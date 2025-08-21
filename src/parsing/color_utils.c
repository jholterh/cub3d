/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:49:41 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/21 08:49:42 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	extract_colors(char *color_str, int *color)
{
	char	**rgb_values;
	int		i;

	rgb_values = ft_split(color_str, ',');
	if (!rgb_values || ft_strlen2((const char **)rgb_values) != 3)
	{
		ft_strfree(rgb_values);
		return (print_error("Invalid color format", 1));
	}
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(rgb_values[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			ft_strfree(rgb_values);
			return (print_error("Color values must be between 0 and 255", 1));
		}
		i++;
	}
	ft_strfree(rgb_values);
	return (0);
}

void	put_colors_in_int(int *seperate_colors, int *colors)
{
	*colors = ((seperate_colors[0] & 0xFF) << 16)
		| ((seperate_colors[1] & 0xFF) << 8)
		| (seperate_colors[2] & 0xFF);
}
