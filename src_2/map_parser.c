/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:43:13 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/12 08:04:21 by abhudulo         ###   ########.fr       */
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
    if (!check_borders(map) || !check_elements(map) || !check_rectangular_shape(map)) {
        fprintf(stderr, "Map validation failed due to incorrect border setup or missing required elements.\n");
        return false;
    }
    return true;
}

t_map *parse_map(const char *file_path) {
    printf("Reading map content from %s\n", file_path);
    char *content = read_file_content(file_path);
    if (!content) {
        fprintf(stderr, "Failed to read map content.\n");
        return NULL;
    }

    t_map *map = malloc(sizeof(t_map));
    if (!map) {
        fprintf(stderr, "Memory allocation failed for map structure.\n");
        free(content);
        return NULL;
    }

    calculate_map_dimensions(content, &map->width, &map->height);
    map->data = allocate_map_data(map->width, map->height);
    if (!map->data) {
        fprintf(stderr, "Failed to allocate map data.\n");
        free(map);
        free(content);
        return NULL;
    }

    fill_map_data(map->data, content, map->height, map->width);
    free(content); // free the content early if it's no longer needed

    bool found_player = false;
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->data[y][x] == 'P') {
                if (found_player) {
                    fprintf(stderr, "Multiple player start positions found.\n");
                    free_map(map);
                    return NULL;
                }
                map->player_x = x;
                map->player_y = y;
                found_player = true;
                printf("Player initial position set to [%d, %d]\n", map->player_x, map->player_y);
            }
        }
    }

    if (!found_player) {
        fprintf(stderr, "Player start position not found.\n");
        free_map(map);
        return NULL;
    }

    printf("Map parsed successfully. Player position: %d, %d\n", map->player_x, map->player_y);
    assert(map->player_x >= 0 && map->player_x < map->width);
    assert(map->player_y >= 0 && map->player_y < map->height);
    return map;
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