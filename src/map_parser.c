/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:50 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:02:05 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_gc.h"
#include "so_long.h"

void	validate_characters(t_map *map)
{
	const char		*valid_chars;
	int				y;
	int				x;

	valid_chars = "01CEP";
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!strchr(valid_chars, map->data[y][x]))
			{
				fprintf(stderr, "Invalid character found: %c\n",
					map->data[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	handle_player_position(t_map *map, int x, int y, bool *found_player)
{
	if (map->data[y][x] == 'P')
	{
		if (*found_player)
		{
			fprintf(stderr, "Multiple player start positions found.\n");
			return ;
		}
		map->player_x = x;
		map->player_y = y;
		*found_player = true;
		printf("Player initial position set to [%d, %d]\n",
			map->player_x, map->player_y);
	}
}

void	find_player_start(t_map *map)
{
	bool		found_player;
	int			y;
	int			x;

	found_player = false;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			handle_player_position(map, x, y, &found_player);
			x++;
		}
		y++;
	}
	if (!found_player)
	{
		fprintf(stderr, "Player start position not found.\n");
		return ;
	}
}

void	allocate_and_fill_map(t_map *map, char *content)
{
	calculate_map_dimensions(content, &map->width, &map->height);
	map->data = allocate_map_data(map->width, map->height);
	if (!map->data)
	{
		fprintf(stderr, "Failed to allocate map data.\n");
		return ;
	}
	fill_map_data(map->data, content, map->height, map->width);
}

t_map	*parse_map(const char *file_path)
{
	char		*content;
	t_map		*map;

	printf("Reading map content from %s\n", file_path);
	content = read_file_content(file_path);
	if (!content)
	{
		fprintf(stderr, "Failed to read map content.\n");
		return (NULL);
	}
	map = ft_gc_malloc(1, sizeof(t_map));
	if (!map)
	{
		fprintf(stderr, "Memory allocation failed for map structure.\n");
		return (NULL);
	}
	allocate_and_fill_map(map, content);
	validate_characters(map);
	find_player_start(map);
	printf("Map parsed successfully. Player position: %d, %d\n",
		map->player_x, map->player_y);
	return (map);
}
