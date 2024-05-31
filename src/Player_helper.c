/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:51:46 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:02:15 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

void	set_player_position(int x, int y, t_map *map)
{
	if (map)
	{
		map->player_x = x;
		map->player_y = y;
		printf("Player position set to [%d, %d]\n", x, y);
	}
	else
		printf("Error: Map is null. Cannot set player position.\n");
}

void	draw_tile(t_draw_context *context, int x, int y)
{
	char		tile;
	mlx_image_t	*sprite_to_draw;

	mlx_image_to_window(context->mlx, context->sprites->floor,
		x * TILE_SIZE, y * TILE_SIZE);
	tile = context->map->data[y][x];
	sprite_to_draw = NULL;
	if (tile == WALL)
		sprite_to_draw = context->sprites->wall;
	else if (tile == COLLECTIBLE)
		sprite_to_draw = context->sprites->collectible;
	else if (tile == EXIT)
		sprite_to_draw = context->sprites->exit;
	else if (tile == PLAYER)
		sprite_to_draw = context->sprites->player;
	if (sprite_to_draw)
		mlx_image_to_window(context->mlx, sprite_to_draw,
			x * TILE_SIZE, y * TILE_SIZE);
}

bool	is_within_bounds(t_map *map, int x, int y)
{
	return (x >= 0 && y >= 0 && x < map->width && y < map->height);
}

void	exit_game(mlx_t *mlx)
{
	printf("Exiting game...\n");
	mlx_close_window(mlx);
	exit(EXIT_SUCCESS);
}

bool	is_valid_position(t_game_context *context, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= context->map->width || new_y < 0
		|| new_y >= context->map->height)
		return (false);
	return (true);
}
