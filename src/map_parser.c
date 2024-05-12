/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:43:13 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:47:00 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
int exit_x = -1, exit_y = -1; // Global variables to store the exit coordinates

void	count_elements(t_map *map, int i, int *counts)
{
	int					j;
	char				c;

	j = 0;
	while (j < map->width)
	{
		c = map->data[i][j];
		if (c == 'P')
			counts[0]++;
		else if (c == 'E')
			counts[1]++;
		else if (c == 'C')
			counts[2]++;
		j++;
	}
}

bool	check_elements(t_map *map)
{
	int					i;
	int					counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	i = 0;
	while (i < map->height)
	{
		count_elements(map, i, counts);
		i++;
	}
	return ((counts[0] == 1 && counts[1] >= 1 && counts[2] >= 1));
}

bool validate_map(t_map *map) {
    if (!map) return false;
    const char *valid_chars = "01CEP";  // Allowed characters

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (!strchr(valid_chars, map->data[y][x])) {
                fprintf(stderr, "Invalid character found: %c\n", map->data[y][x]);
                return false;
            }
        }
    }

    // Additional existing checks
    if (!check_borders(map) || !check_elements(map) || !check_rectangular_shape(map))
        return false;

    return true;
}


int player_x = -1, player_y = -1;

t_map *parse_map(const char *file_path) {
    char *content;
    t_map *map;

    content = read_file_content(file_path);
    if (!content)
        return (NULL);

    map = malloc(sizeof(t_map));
    if (!map)
        return (free(content), NULL);

    calculate_map_dimensions(content, &map->width, &map->height);
    map->data = allocate_map_data(map->width, map->height);
    if (!map->data)
        return (free(map), free(content), NULL);

    fill_map_data(map->data, content, map->height, map->width);

    // Locate player and store position
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->data[y][x] == 'P') {
                player_x = x;
                player_y = y;
                break;
            }
        }
    }

    free(content);
    return (map);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	free(map);
}