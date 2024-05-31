/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_helper_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:19:39 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:00:52 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_gc.h"
#include "so_long.h"

mlx_image_t	*scale_image(mlx_t *mlx, mlx_image_t *image, int new_width,
			int new_height)
{
	mlx_image_t	*scaled_image;

	scaled_image = create_scaled_image(mlx, image, new_width, new_height);
	if (!scaled_image)
		return (NULL);
	scale_pixels(image, scaled_image, new_width, new_height);
	return (scaled_image);
}

void	load_and_scale_sprite(t_sprite_args *args)
{
	mlx_texture_t	*temp_texture;
	mlx_image_t		*scaled_image;

	temp_texture = mlx_load_png(args->file_path);
	if (!temp_texture)
	{
		fprintf(stderr, "Failed to load texture from %s\n", args->file_path);
		exit(EXIT_FAILURE);
	}
	*(args->image) = mlx_texture_to_image(args->mlx, temp_texture);
	mlx_delete_texture(temp_texture);
	if (*(args->image))
	{
		scaled_image = scale_image(args->mlx, *(args->image), args->width,
				args->height);
		if (!scaled_image)
		{
			fprintf(stderr, "Failed to scale image for %s\n", args->file_path);
			exit(EXIT_FAILURE);
		}
		mlx_delete_image(args->mlx, *(args->image));
		*(args->image) = scaled_image;
		printf("Loaded and scaled %s successfully.\n", args->file_path);
	}
}

void	load_sprites(mlx_t *mlx, t_game_sprites *sprites, int tile_width,
		int tile_height)
{
	t_sprite_args	args;

	args.mlx = mlx;
	args.width = tile_width;
	args.height = tile_height;
	args.image = &sprites->wall;
	args.file_path = "assets/sprites/rock.png";
	load_and_scale_sprite(&args);
	args.image = &sprites->collectible;
	args.file_path = "assets/sprites/Egg.png";
	load_and_scale_sprite(&args);
	args.image = &sprites->exit;
	args.file_path = "assets/sprites/Chichken.png";
	load_and_scale_sprite(&args);
	args.image = &sprites->player;
	args.file_path = "assets/sprites/cat_0.png";
	load_and_scale_sprite(&args);
	args.image = &sprites->floor;
	args.file_path = "assets/sprites/Grass.png";
	load_and_scale_sprite(&args);
	printf("All sprites loaded successfully.\n");
}
