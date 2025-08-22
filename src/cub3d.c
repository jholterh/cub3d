/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:14:24 by jholterh          #+#    #+#             */
/*   Updated: 2025/08/22 11:37:20 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_init_data		*init_data;

	if (parsing(argc, argv, &init_data))
		return (print_error("found", 10));
	printf(COLOR_GREEN "Parsing completed successfully.\n" COLOR_RESET);
	free_init_data(init_data);
	return (0);
}
