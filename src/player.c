/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:58 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:02:20 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

bool	handle_movement(mlx_t *mlx, int key, int *key_down,
	t_game_context *context)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (mlx_is_key_down(mlx, key) && !*key_down)
	{
		*key_down = 1;
		if (key == MLX_KEY_W)
			dy = -1;
		else if (key == MLX_KEY_S)
			dy = 1;
		else if (key == MLX_KEY_A)
			dx = -1;
		else if (key == MLX_KEY_D)
			dx = 1;
		return (update_player_position(context, dx, dy));
	}
	else if (!mlx_is_key_down(mlx, key))
		*key_down = 0;
	return (false);
}

bool	check_boundaries(int x, int y, t_map *map)
{
	if (!map || !map->data || x < 0 || x >= map->width
		|| y < 0 || y >= map->height)
	{
		printf("Boundary check failed for [%d, %d]\n", x, y);
		return (false);
	}
	return (map->data[y][x] != WALL);
}

void	collect_if_collectible(int x, int y, t_map *map)
{
	if (map->data[y][x] == COLLECTIBLE)
	{
		map->data[y][x] = EMPTY;
		printf("Collected at [%d, %d].\n", x, y);
	}
}

bool	check_all_collected(t_map *map)
{
	printf("Checking if all collectibles have been collected...\n");
	if (g_collected_count == g_total_collectibles)
	{
		printf("Congratulations! All collectibles have been collected!\n");
		return (true);
	}
	printf("Not all collectibles have been collected yet.\n");
	return (false);
}

void	collect_collectible(int x, int y, t_map *map)
{
	printf("Attempting to collect at %d, %d (Map value: %c)\n",
		x, y, map->data[y][x]);
	if (map->data[y][x] == COLLECTIBLE)
	{
		map->data[y][x] = EMPTY;
		g_collected_count++;
		printf("Collectible collected at [%d, %d], total collected: %d/%d.\n",
			x, y, g_collected_count, g_total_collectibles);
		if (check_all_collected(map))
			printf("All collectibles have been collected. Exit is revealed.\n");
	}
}
