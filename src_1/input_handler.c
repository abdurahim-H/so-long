/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:30:54 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/12 17:28:17 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void update_key_state(KeyState* state, int is_currently_pressed) {
    if (is_currently_pressed && !state->is_pressed) {
        // Key was just pressed
        state->is_pressed = 1;
        printf("Key Pressed\n");
    } else if (!is_currently_pressed && state->is_pressed) {
        // Key was just released
        state->is_pressed = 0;
        printf("Key Released\n");
    }
}

static int w_key_down = 0, s_key_down = 0, a_key_down = 0, d_key_down = 0;


void ft_hook(void *param) {
    GameContext *context = (GameContext *)param;
    // Call directly with the actual MLX key codes
    if (mlx_is_key_down(context->mlx, MLX_KEY_W)) handle_player_input(MLX_KEY_W, context);
    if (mlx_is_key_down(context->mlx, MLX_KEY_S)) handle_player_input(MLX_KEY_S, context);
    if (mlx_is_key_down(context->mlx, MLX_KEY_A)) handle_player_input(MLX_KEY_A, context);
    if (mlx_is_key_down(context->mlx, MLX_KEY_D)) handle_player_input(MLX_KEY_D, context);
}
