/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:24 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 21:39:25 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

int	g_total_collectibles = 0;
int	g_collected_count = 0;

void	cleanup_game(t_game_context *context)
{
	mlx_terminate(context->mlx);
}

int	main(int argc, char **argv)
{
	t_game_context	context;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	context = (t_game_context){0};
	if (!setup_game(&context, argv[1]))
	{
		fprintf(stderr, "Game setup failed.\n");
		return (EXIT_FAILURE);
	}
	mlx_key_hook(context.mlx, key_hook, &context);
	mlx_loop(context.mlx);
	cleanup_game(&context);
	return (EXIT_SUCCESS);
}
