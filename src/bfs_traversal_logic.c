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
    if (!visited) {
        fprintf(stderr, "Failed to allocate visited array.\n");
        return false;
    }

    bool path_to_exit = false;
    t_node *queue = NULL;

    enqueue(&queue, start_x, start_y);
    visited[start_y][start_x] = true;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    while (!is_empty(queue)) {
        int x, y;
        dequeue(&queue, &x, &y);

        if (map[y][x] == EXIT) {
            path_to_exit = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if (nx >= 0 && nx < map_width && ny >= 0 && ny < map_height && map[ny][nx] != WALL && !visited[ny][nx]) {
                enqueue(&queue, nx, ny);
                visited[ny][nx] = true;
            }
        }
    }

    free_resources(visited, map_height);
    return path_to_exit;
}
