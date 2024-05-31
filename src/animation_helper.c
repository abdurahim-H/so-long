/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:36:34 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:02 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_gc.h"
#include "so_long.h"

void	draw_sprite(mlx_t *mlx, mlx_image_t *sprite, int x, int y)
{
	if (sprite)
	{
		mlx_image_to_window(mlx, sprite, x * TILE_SIZE, y * TILE_SIZE);
	}
}

mlx_image_t	*get_sprite(char tile, t_game_sprites *sprites)
{
	mlx_image_t	*sprite_to_draw;

	sprite_to_draw = NULL;
	if (tile == WALL)
		sprite_to_draw = sprites->wall;
	else if (tile == PLAYER)
		sprite_to_draw = sprites->player;
	else if (tile == COLLECTIBLE)
		sprite_to_draw = sprites->collectible;
	else if (tile == EXIT)
		sprite_to_draw = sprites->exit;
	return (sprite_to_draw);
}

void	render_row(mlx_t *mlx, t_map *map, t_game_sprites *sprites, int y)
{
	int			x;
	char		tile;
	mlx_image_t	*sprite_to_draw;

	x = 0;
	while (x < map->width)
	{
		if (sprites->floor)
			draw_sprite(mlx, sprites->floor, x, y);
		tile = map->data[y][x];
		sprite_to_draw = get_sprite(tile, sprites);
		draw_sprite(mlx, sprite_to_draw, x, y);
		x++;
	}
}

void	render_map(mlx_t *mlx, t_map *map, t_game_sprites *sprites)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		render_row(mlx, map, sprites, y);
		y++;
	}
}
