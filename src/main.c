/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:24 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:53 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

int g_total_collectibles = 0;
int g_collected_count = 0;

void cleanup_game(t_game_context *context)
{
    mlx_terminate(context->mlx);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    t_game_context context = {0};

    if (!setup_game(&context, argv[1])) {
        fprintf(stderr, "Game setup failed.\n");
        return EXIT_FAILURE; // Exit if setup failed
    }

    mlx_key_hook(context.mlx, key_hook, &context); // Hook the keyboard input
    mlx_loop(context.mlx); // Start the game loop

    cleanup_game(&context); // Cleanup resources upon game exit
    return EXIT_SUCCESS;
}
