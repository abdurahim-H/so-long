/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:30:54 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:46:17 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void ft_hook(void* param) {
//     static int w_key_down = 0, a_key_down = 0, s_key_down = 0, d_key_down = 0;
//     mlx_t* mlx = param;
//     int old_x = image->instances[0].x;
//     int old_y = image->instances[0].y;

//     if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
//         mlx_close_window(mlx);

//     handle_movement(mlx, MLX_KEY_W, &w_key_down, old_x, old_y - 20, check_boundaries);
//     handle_movement(mlx, MLX_KEY_S, &s_key_down, old_x, old_y + 20, check_boundaries);
//     handle_movement(mlx, MLX_KEY_A, &a_key_down, old_x - 20, old_y, check_boundaries);
//     handle_movement(mlx, MLX_KEY_D, &d_key_down, old_x + 20, old_y, check_boundaries);
// }


void ft_hook(void *param)
{
    static int w_key_down = 0, a_key_down = 0, s_key_down = 0, d_key_down = 0;
    mlx_t* mlx = param;
    int old_x = map->player_x;
    int old_y = map->player_y;

    handle_movement(mlx, MLX_KEY_W, &w_key_down, old_x, old_y - 1, check_boundaries);
    handle_movement(mlx, MLX_KEY_S, &s_key_down, old_x, old_y + 1, check_boundaries);
    handle_movement(mlx, MLX_KEY_A, &a_key_down, old_x - 1, old_y, check_boundaries);
    handle_movement(mlx, MLX_KEY_D, &d_key_down, old_x + 1, old_y, check_boundaries);
}