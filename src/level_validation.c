/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:51:53 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:46:23 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int collectible_count = 0;
int count = 0;

void enqueueCollectible(Node** head, Point point) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory for queue node.\n");
        return;
    }
    new_node->point = point;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

bool dequeueCollectible(Node** head, Point* point) {
    if (*head == NULL) return false;
    Node* temp = *head;
    *point = temp->point;
    *head = temp->next;
    free(temp);
    return true;
}

bool** initialize_visited(int width, int height) {
    bool** visited = malloc(height * sizeof(bool*));
    if (visited == NULL) return NULL;
    for (int i = 0; i < height; i++) {
        visited[i] = malloc(width * sizeof(bool));
        if (visited[i] == NULL) {
            // Clean up previously allocated memory
            for (int j = 0; j < i; j++) {
                free(visited[j]);
            }
            free(visited);
            return NULL;
        }
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
        }
    }
    return visited;
}

void free_resources_c(bool** visited, int height, Collectible* collectibles) {
    for (int i = 0; i < height; i++) {
        free(visited[i]);
    }
    free(visited);
    free(collectibles);
}

int count_collectibles(char** map, int width, int height) {
    // int count = 0;
	// collectible_count = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == 'C')
			{	
				count++;
				collectible_count++;
			}
        }
    }
    return count;
}

void validateCollectibleAccessibility(char** map, int start_x, int start_y, int map_width, int map_height, Collectible* collectibles, int collectible_count) {
    bool** visited = initialize_visited(map_width, map_height);
    if (!visited) {
        printf("Failed to allocate memory for visited array.\n");
        return;
    }

    Node* queue = NULL;
    enqueueCollectible(&queue, (Point){start_x, start_y});  // Starting point
    visited[start_y][start_x] = true;

    Point currentPoint;
    while (dequeueCollectible(&queue, &currentPoint)) {
        int x = currentPoint.x;
        int y = currentPoint.y;

        int dx[4] = {0, 0, -1, 1};  // Directions left and right
        int dy[4] = {-1, 1, 0, 0};  // Directions up and down

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < map_width && ny >= 0 && ny < map_height && !visited[ny][nx] && map[ny][nx] != '1') {
                visited[ny][nx] = true;
                enqueueCollectible(&queue, (Point){nx, ny});
                // Correctly check if the current node is a collectible
                for (int c = 0; c < collectible_count; c++) {
                    if (collectibles[c].pos.x == nx && collectibles[c].pos.y == ny) {
                        collectibles[c].visited = true;
                    }
                }
            }
        }
    }

    // Free resources
    for (int i = 0; i < map_height; i++) {
        free(visited[i]);
    }
    free(visited);
}