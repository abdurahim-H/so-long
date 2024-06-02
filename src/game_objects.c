/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:43:39 by abhudulo          #+#    #+#             */
/*   Updated: 2024/06/01 14:57:32 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

void	game_loop(mlx_t *mlx, t_game_context *context)
{
	mlx_loop_hook(mlx, game_hook, context);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void	free_sprites(mlx_t *mlx, t_game_sprites *sprites)
{
	if (sprites->wall)
	{
		mlx_delete_image(mlx, sprites->wall);
		sprites->wall = NULL;
	}
	if (sprites->collectible)
	{
		mlx_delete_image(mlx, sprites->collectible);
		sprites->collectible = NULL;
	}
	if (sprites->exit)
	{
		mlx_delete_image(mlx, sprites->exit);
		sprites->exit = NULL;
	}
	if (sprites->player)
	{
		mlx_delete_image(mlx, sprites->player);
		sprites->player = NULL;
	}
	if (sprites->floor)
	{
		mlx_delete_image(mlx, sprites->floor);
		sprites->floor = NULL;
	}
}
