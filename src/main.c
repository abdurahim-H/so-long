/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:24 by abhudulo          #+#    #+#             */
/*   Updated: 2024/06/02 20:44:38 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

int	g_collected_count = 0;

void	cleanup_game(t_game_context *context)
{
	mlx_terminate(context->mlx);
}

void	initialize_game(t_game_context *context, char *map_file)
{
	if (!setup_game(context, map_file))
	{
		fprintf(stderr, "Game setup failed.\n");
		exit(EXIT_FAILURE);
	}
	if (!check_borders(context->map))
	{
		fprintf(stderr,
			"Invalid map. The map should be surrounded by walls.\n");
		exit(EXIT_FAILURE);
	}
}

void	setup_map_info(t_mapinfo *map_info, t_game_context *context)
{
	map_info->map = context->map->data;
	map_info->map_width = context->map->width;
	map_info->map_height = context->map->height;
	if (!bfs(*map_info, context->map->player_x, context->map->player_y))
	{
		fprintf(stderr, "Invalid map. No valid path from start to exit.\n");
		exit(EXIT_FAILURE);
	}
}

bool	check_ber_extension(const char *filename)
{
	const char	*dot = strrchr(filename, '.');

	if (!dot || dot == filename)
		return (false);
	return (strcmp(dot, ".ber") == 0);
}

int	main(int argc, char **argv)
{
	t_game_context	context;
	t_mapinfo		map_info;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (!check_ber_extension(argv[1]))
	{
		fprintf(stderr, "Invalid file type. Please provide a .ber file.\n");
		return (EXIT_FAILURE);
	}
	context = (t_game_context){0};
	initialize_game(&context, argv[1]);
	setup_map_info(&map_info, &context);
	mlx_key_hook(context.mlx, key_hook, &context);
	mlx_loop(context.mlx);
	cleanup_game(&context);
	return (EXIT_SUCCESS);
}
