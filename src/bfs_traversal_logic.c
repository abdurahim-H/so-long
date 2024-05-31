/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_traversal_logic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:43:29 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 21:35:37 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_gc.h"
#include "so_long.h"

bool	is_empty(t_node *queue)
{
	return (queue == NULL);
}

void	bfs_visit_neighbours(t_bfs *bfs, int x, int y, int i)
{
	int	nx;
	int	ny;

	while (i < 4)
	{
		nx = x + bfs->dx[i];
		ny = y + bfs->dy[i];
		if (nx >= 0 && nx < bfs->map_width && ny >= 0 && ny < bfs->map_height
			&& bfs->map[ny][nx] != WALL && !bfs->visited[ny][nx])
		{
			enqueue(&bfs->queue, nx, ny);
			bfs->visited[ny][nx] = true;
		}
		i++;
	}
}

bool	bfs_helper(t_bfs *bfs)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (!is_empty(bfs->queue))
	{
		dequeue(&bfs->queue, &x, &y);
		if (bfs->map[y][x] == EXIT)
			return (true);
		bfs_visit_neighbours(bfs, x, y, i);
	}
	return (false);
}

bool	bfs(MapInfo mapInfo, int start_x, int start_y)
{
	t_bfs	bfs;
	int		i;

	bfs.map = mapInfo.map;
	bfs.queue = NULL;
	bfs.dx = (int [4]){0, 1, 0, -1};
	bfs.dy = (int [4]){1, 0, -1, 0};
	bfs.visited = initialize_visited(mapInfo.map_width, mapInfo.map_height);
	bfs.map_width = mapInfo.map_width;
	bfs.map_height = mapInfo.map_height;
	i = 0;
	if (!bfs.visited)
	{
		fprintf(stderr, "Failed to allocate visited array.\n");
		return (false);
	}
	enqueue(&bfs.queue, start_x, start_y);
	bfs.visited[start_y][start_x] = true;
	return (bfs_helper(&bfs));
}
