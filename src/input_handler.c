/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:43:54 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:15 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_gc.h"
#include "so_long.h"

void	update_key_state(t_key_state *state, int is_currently_pressed)
{
	if (is_currently_pressed && !state->is_pressed)
	{
		state->is_pressed = 1;
		printf("Key Pressed\n");
	}
	else if (!is_currently_pressed && state->is_pressed)
	{
		state->is_pressed = 0;
		printf("Key Released\n");
	}
}

void	game_hook(void *param)
{
	t_game_context	*context;

	context = (t_game_context *)param;
	if (mlx_is_key_down(context->mlx, MLX_KEY_W))
		handle_player_input(MLX_KEY_W, context);
	if (mlx_is_key_down(context->mlx, MLX_KEY_S))
		handle_player_input(MLX_KEY_S, context);
	if (mlx_is_key_down(context->mlx, MLX_KEY_A))
		handle_player_input(MLX_KEY_A, context);
	if (mlx_is_key_down(context->mlx, MLX_KEY_D))
		handle_player_input(MLX_KEY_D, context);
}
