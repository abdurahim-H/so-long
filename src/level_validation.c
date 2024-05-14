#include "so_long.h"

int collectible_count = 0;
int count = 0;

void enqueue(t_node **head, int x, int y) {
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node) {
        fprintf(stderr, "Failed to allocate memory for new node.\n");
        return;
    }
    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

bool dequeue(t_node **head, int *x, int *y) {
    if (*head == NULL) {
        return false;
    }
    t_node *temp = *head;
    *x = temp->x;
    *y = temp->y;
    *head = temp->next;
    free(temp);
    return true;
}

void enqueue_collectible(Node **head, Point point) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Failed to allocate memory for new node.\n");
        return;
    }
    new_node->point = point;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

bool dequeue_collectible(Node **head, Point *point) {
    if (*head == NULL) {
        return false;
    }
    Node *temp = *head;
    *point = temp->point;
    *head = temp->next;
    free(temp);
    return true;
}

bool **initialize_visited(int width, int height) {
    bool **visited = malloc(height * sizeof(bool *));
    if (!visited) {
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        visited[i] = malloc(width * sizeof(bool));
        if (!visited[i]) {
            for (int j = 0; j < i; j++) {
                free(visited[j]);
            }
            free(visited);
            return NULL;
        }
        memset(visited[i], 0, width * sizeof(bool));
    }
    return visited;
}

void free_resources_c(bool **visited, int height, Collectible *collectibles) {
    for (int i = 0; i < height; i++) {
        free(visited[i]);
    }
    free(visited);
    free(collectibles);
}

int count_collectibles(char **map, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == COLLECTIBLE) {
                count++;
                collectible_count++;
            }
        }
    }
    return count;
}

void validate_collectible_accessibility(char **map, int start_x, int start_y, int map_width, int map_height, Collectible *collectibles, int collectible_count) {
    bool **visited = initialize_visited(map_width, map_height);
    if (!visited) {
        fprintf(stderr, "Failed to allocate memory for visited array.\n");
        return;
    }

    Node *queue = NULL;
    enqueue_collectible(&queue, (Point) {start_x, start_y});
    visited[start_y][start_x] = true;

    Point current_point;
    while (dequeue_collectible(&queue, &current_point)) {
        int x = current_point.x;
        int y = current_point.y;

        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < map_width && ny >= 0 && ny < map_height && !visited[ny][nx] && map[ny][nx] != WALL) {
                visited[ny][nx] = true;
                enqueue_collectible(&queue, (Point) {nx, ny});
                for (int c = 0; c < collectible_count; c++) {
                    if (collectibles[c].pos.x == nx && collectibles[c].pos.y == ny) {
                        collectibles[c].visited = true;
                    }
                }
            }
        }
    }

    free_resources_c(visited, map_height, collectibles);
}
