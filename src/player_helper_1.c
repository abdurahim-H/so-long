/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_helper_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:53:37 by abhudulo          #+#    #+#             */
/*   Updated: 2024/06/02 21:10:54 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

int	g_move_count = 0;
int	g_total_collectibles = 0;

bool	handle_collectible(t_game_context *context, int new_x, int new_y)
{
	g_collected_count++;
	context->map->data[new_y][new_x] = 'P';
	printf("Collected at [%d, %d]. Total collected: %d\n",
		new_x, new_y, g_collected_count);
	return (true);
}

void	update_position(t_game_context *context, int new_x, int new_y)
{
	context->map->data[context->map->player_y][context->map->player_x] = '0';
	context->map->player_x = new_x;
	context->map->player_y = new_y;
	context->map->data[new_y][new_x] = 'P';
}

bool	handle_tile(t_game_context *context, char target_tile,
	int new_x, int new_y)
{
	if (target_tile == 'C')
	{
		g_collected_count++;
		context->map->data[new_y][new_x] = 'P';
		printf("Collected at [%d, %d]. Total collected: %d\n",
			new_x, new_y, g_collected_count);
	}
	else if (target_tile == 'E')
	{
		if (g_collected_count == g_total_collectibles)
		{
			printf("All collectibles collected. Exiting game.\n");
			exit_game(context->mlx);
			return (true);
		}
		else
		{
			printf("Cannot exit yet! Collect all items first.\n");
			return (false);
		}
	}
	return (true);
}

// bool	update_player_position(t_game_context *context, int dx, int dy)
// {
// 	int			new_x;
// 	int			new_y;
// 	char		target_tile;

// 	new_x = context->map->player_x + dx;
// 	new_y = context->map->player_y + dy;
// 	if (!is_valid_position(context, new_x, new_y))
// 		return (false);
// 	target_tile = context->map->data[new_y][new_x];
// 	if (target_tile == 'W')
// 		return (false);
// 	if (!handle_tile(context, target_tile, new_x, new_y))
// 		return (false);
// 	update_position(context, new_x, new_y);
// 	render_map(context->mlx, context->map, &context->sprites);
// 	return (true);
// }

bool	update_player_position(t_game_context *context, int dx, int dy)
{
	int			new_x;
	int			new_y;
	char		target_tile;

	new_x = context->map->player_x + dx;
	new_y = context->map->player_y + dy;
	if (!is_valid_position(context, new_x, new_y))
		return (false);
	target_tile = context->map->data[new_y][new_x];
	if (target_tile == 'W')
		return (false);
	if (!handle_tile(context, target_tile, new_x, new_y))
		return (false);
	update_position(context, new_x, new_y);
	render_map(context->mlx, context->map, &context->sprites);
	return (true);
}

bool	attempt_move(t_game_context *context, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = context->map->player_x + dx;
	new_y = context->map->player_y + dy;
	if (check_boundaries(new_x, new_y, context->map))
	{
		if (update_player_position(context, dx, dy))
			return (true);
	}
	return (false);
}
