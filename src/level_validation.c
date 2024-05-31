/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:06 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:44 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

int	g_dx[4] = {0, 0, -1, 1};
int	g_dy[4] = {-1, 1, 0, 0};

bool	**initialize_visited(int width, int height)
{
	bool	**visited;
	int		i;

	visited = (bool **)ft_gc_malloc(height, sizeof(bool *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = (bool *)ft_gc_malloc(width, sizeof(bool));
		if (!visited[i])
			return (NULL);
		memset(visited[i], 0, width * sizeof(bool));
		i++;
	}
	return (visited);
}

int	count_collectibles(char **map, int width, int height)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == COLLECTIBLE)
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return (count);
}

void	enqueue_direction(t_queue_info *queue_info, int nx, int ny)
{
	if (nx >= 0 && nx < queue_info->map_info->map_width && ny >= 0
		&& ny < queue_info->map_info->map_height
		&& !queue_info->visited[ny][nx]
		&& queue_info->map_info->map[ny][nx] != WALL)
	{
		queue_info->visited[ny][nx] = true;
		enqueue_collectible(queue_info->queue, (t_point){nx, ny});
	}
}

void	process_directions(t_queue_info *queue_info, int x, int y)
{
	int	i;
	int	nx;
	int	ny;

	i = 0;
	while (i < 4)
	{
		nx = x + g_dx[i];
		ny = y + g_dy[i];
		enqueue_direction(queue_info, nx, ny);
		i++;
	}
}

void	validate_collectible_accessibility(t_map_info *map_info,
	int start_x, int start_y)
{
	bool			**visited;
	t_Node			*queue;
	t_point			current_point;
	t_queue_info	queue_info;

	visited = initialize_visited(map_info->map_width, map_info->map_height);
	if (!visited)
	{
		fprintf(stderr, "Failed to allocate memory for visited array.\n");
		return ;
	}
	queue = NULL;
	enqueue_collectible(&queue, (t_point){start_x, start_y});
	visited[start_y][start_x] = true;
	queue_info.queue = &queue;
	queue_info.visited = visited;
	queue_info.map_info = map_info;
	while (dequeue_collectible(&queue, &current_point))
		process_directions(&queue_info, current_point.x, current_point.y);
}
