/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_helper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 05:13:27 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:00:57 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_gc.h"
#include "so_long.h"

mlx_image_t	*create_scaled_image(mlx_t *mlx, mlx_image_t *image, int new_width,
			int new_height)
{
	mlx_image_t	*scaled_image;

	if (!image)
	{
		fprintf(stderr, "Input image is NULL.\n");
		return (NULL);
	}
	scaled_image = mlx_new_image(mlx, new_width, new_height);
	if (!scaled_image)
	{
		fprintf(stderr, "Failed to create new image.\n");
		return (NULL);
	}
	return (scaled_image);
}

void	scale_pixel(t_scale_pixel_args *args)
{
	int			b_p_pix;
	int			src_x;
	int			src_y;
	uint8_t		*src_pixel;
	uint8_t		*dst_pixel;

	b_p_pix = 4;
	src_x = args->x * args->image->width / args->new_width;
	src_y = args->y * args->image->height / args->new_height;
	src_pixel = &args->image->pixels[(src_y * args->image->width + src_x)
		* b_p_pix];
	dst_pixel = &args->scaled_image->pixels[(args->y * args->new_width
			+ args->x) * b_p_pix];
	memmove(dst_pixel, src_pixel, b_p_pix);
}

void	scale_pixels(mlx_image_t *image, mlx_image_t *scaled_image,
		int new_width, int new_height)
{
	int					y;
	int					x;
	t_scale_pixel_args	args;

	args.image = image;
	args.scaled_image = scaled_image;
	args.new_width = new_width;
	args.new_height = new_height;
	y = 0;
	while (y < new_height)
	{
		x = 0;
		while (x < new_width)
		{
			args.x = x;
			args.y = y;
			scale_pixel(&args);
			x++;
		}
		y++;
	}
}
