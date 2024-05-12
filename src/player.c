/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:28:25 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:47:39 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int move_count = 0;
int collected_count = 0;

void update_position(int new_x, int new_y) {
    image->instances[0].x = new_x;
    image->instances[0].y = new_y;
    move_count++;
    printf("Move Count: %d\n", move_count);
}

void handle_movement(mlx_t* mlx, int key, int* key_down, int new_x, int new_y, int (*check_boundaries)(int, int)) {
    if (mlx_is_key_down(mlx, key) && check_boundaries(new_x, new_y)) {
        int gridX = new_x / TILE_SIZE;
        int gridY = new_y / TILE_SIZE;

        printf("Trying to move to %d, %d\n", gridX, gridY); // Debug output
        if (!*key_down) {
            char cell = map->data[gridY][gridX];
            if (cell == 'C') {
                printf("Landed on a collectible at %d, %d\n", gridX, gridY); // Debug output
                collect_collectible(gridX, gridY);
            }
            update_position(new_x, new_y);
            *key_down = 1;
        }
    } else {
        *key_down = 0;
    }
}


bool check_all_collected() {
	printf("Checking if all collectibles have been collected...\n"); // Debug output
	if (collected_count == collectible_count) {
		printf("Congratulations! All collectibles have been collected!\n");
		reveal_map(map); // Reveal the exit
		return true; // Return true when exit is revealed
	}
	printf("Not all collectibles have been collected yet.\n"); // Debug output
	return false; // Return false when exit is not revealed
}

void collect_collectible(int x, int y) {
	printf("Attempting to collect at %d, %d (Map value: %c)\n", x, y, map->data[y][x]); // Debug output
	if (map->data[y][x] == 'C') {
		map->data[y][x] = '0';
		collected_count++;
		printf("Collectible collected at [%d, %d], total collected: %d/%d.\n", x, y, collected_count, collectible_count); // Debug output
		if (check_all_collected()) {
			printf("All collectibles have been collected. Exit is revealed.\n"); // Debug output
		}
	}
}


int check_boundaries(int new_x, int new_y) {
    int map_x = new_x / 20;
    int map_y = new_y / 20;

    printf("Boundary check at %d, %d (Map coordinates: %d, %d, Value: %c)\n", new_x, new_y, map_x, map_y, map->data[map_y][map_x]);
    
    if (map->data[map_y][map_x] == '1') {
        printf("Blocked by wall at %d, %d\n", map_x, map_y);
        return 0; // Blocked by wall
    }
    return 1; // Free to move
}