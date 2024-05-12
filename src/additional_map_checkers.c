/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_map_checkers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:20:29 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/02 01:39:24 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_rectangular_shape(t_map *map)
{
	size_t		expected_width;
	int			i;

	expected_width = strlen(map->data[0]);
	i = 0;
	while (i < map->height)
	{
		if (strlen(map->data[i]) != expected_width)
			return (false);
		i++;
	}
	return (true);
}

// bool check_rectangular_shape(t_map *map) {
//     size_t expected_width = strlen(map->data[0]);

//     for (int i = 0; i < map->height; i++) {
//         if (strlen(map->data[i]) != expected_width)
//             return (false);
//     }
//     return (true);
// }