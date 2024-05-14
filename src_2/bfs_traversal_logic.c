/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_traversal_logic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 05:19:56 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:45:32 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool is_empty(t_node *queue) {
    return queue == NULL;
}

void free_resources(bool **visited, int height) {
    for (int i = 0; i < height; i++) {
        free(visited[i]);
    }
    free(visited);
}

bool bfs(char **map, int start_x, int start_y, int map_width, int map_height) {
    bool **visited = initialize_visited(map_width, map_height);
    bool path_to_exit = false; // Assume no path by default
    t_node *queue = NULL;

    enqueue(&queue, start_x, start_y);
    visited[start_y][start_x] = true;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    while (!is_empty(queue)) {
        int x, y;
        dequeue(&queue, &x, &y);

        // Check if this node is the exit
        if (map[y][x] == 'E') {
            path_to_exit = true;
            break; // Exit found, no need to continue
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if (nx >= 0 && nx < map_width && ny >= 0 && ny < map_height && map[ny][nx] != '1' && !visited[ny][nx]) {
                enqueue(&queue, nx, ny);
                visited[ny][nx] = true;
            }
        }
    }

    free_resources(visited, map_height);
    return path_to_exit;
}