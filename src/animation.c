/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:43:14 by abhudulo          #+#    #+#             */
/*   Updated: 2024/06/02 21:08:24 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_gc.h"
#include "so_long.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game_context	*context;

	context = (t_game_context *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(context->mlx);
	}
	else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		handle_player_input(keydata.key, context);
	}
}

void	handle_player_input(int key, t_game_context *context)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (key == MLX_KEY_W)
		dy = -1;
	else if (key == MLX_KEY_S)
		dy = 1;
	else if (key == MLX_KEY_A)
		dx = -1;
	else if (key == MLX_KEY_D)
		dx = 1;
	else
		return ;
	if (attempt_move(context, dx, dy))
	{
		g_move_count++;
		printf("Move %d\n", g_move_count);
		render_map(context->mlx, context->map, &context->sprites);
	}
}

bool	can_exit_game(t_map *map, int x, int y)
{
	if (map->data[y][x] == 'E' && g_collected_count == g_total_collectibles)
		return (true);
	return (false);
}

bool	setup_game(t_game_context *context, const char *map_file_path)
{
	context->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "so_long", true);
	if (!context->mlx)
	{
		fprintf(stderr, "Failed to initialize MLX.\n");
		return (false);
	}
	context->map = parse_map(map_file_path);
	if (!context->map)
	{
		fprintf(stderr, "Failed to load or validate map.\n");
		mlx_terminate(context->mlx);
		return (false);
	}
	load_sprites(context->mlx, &context->sprites, TILE_SIZE, TILE_SIZE);
	render_map(context->mlx, context->map, &context->sprites);
	g_total_collectibles = count_collectibles(context->map->data,
			context->map->width, context->map->height);
	if (g_total_collectibles <= 0)
	{
		fprintf(stderr, "No collectibles on the map, can't play this level.\n");
		return (false);
	}
	printf("Map setup successful with %d collectibles.\n",
		g_total_collectibles);
	return (true);
}
