/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:31 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 21:54:37 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

char	**allocate_map_data(int width, int height)
{
	char	**data;
	int		i;

	i = 0;
	data = ft_gc_malloc(height, sizeof(char *));
	if (!data)
		return (NULL);
	while (i < height)
	{
		data[i] = ft_gc_malloc(1, (width + 1) * sizeof(char));
		if (!data[i])
			return (NULL);
		i++;
	}
	return (data);
}

void	handle_newline(const char **p, char **data, int *y, int *x)
{
	if (**p == '\r' && *(*p + 1) == '\n')
		(*p)++;
	data[*y][*x] = '\0';
	(*y)++;
	*x = 0;
}

void	fill_map_data(char **data, const char *content, int height, int width)
{
	int				y;
	int				x;
	const char		*p;

	x = 0;
	y = 0;
	p = content;
	while (*p && y < height)
	{
		if (*p == '\n' || *p == '\r')
			handle_newline(&p, data, &y, &x);
		else if (x < width)
			data[y][x++] = *p;
		p++;
	}
	if (y < height)
		fprintf(stderr, "Not enough l, e %d, got %d\n", height, y);
}

bool	check_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->data[0][i] != WALL || map->data[map->height - 1][i] != WALL)
			return (false);
		i++;
	}
	while (i < map->height)
	{
		if (map->data[i][0] != WALL || map->data[i][map->width - 1] != WALL)
			return (false);
		i++;
	}
	return (true);
}
