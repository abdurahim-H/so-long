/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:28:25 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/14 20:08:44 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int move_count = 0;
int collected_count = 0;


void set_player_position(int x, int y, t_map *map) {
	if (map) {
		map->player_x = x;
		map->player_y = y;
		printf("Player position set to [%d, %d]\n", x, y);
	} else {
		printf("Error: Map is null. Cannot set player position.\n");
	}
}


void draw_tile(mlx_t *mlx, t_map *map, GameSprites *sprites, int x, int y) {
    // Clear the tile by redrawing the floor or background
    if (sprites->floor) {
        mlx_image_to_window(mlx, sprites->floor, x * TILE_SIZE, y * TILE_SIZE);
    }
    // Draw the object at this tile
    mlx_image_t *sprite = NULL;
    switch (map->data[y][x]) {
        case '1': sprite = sprites->wall; break;
        case 'C': sprite = sprites->collectible; break;
        case 'E': sprite = sprites->exit; break;
        case 'P': sprite = sprites->player; break;
    }
    if (sprite) {
        mlx_image_to_window(mlx, sprite, x * TILE_SIZE, y * TILE_SIZE);
    }
}

// bool update_player_position(GameContext *context, int dx, int dy) {
//     int newX = context->map->player_x + dx;
//     int newY = context->map->player_y + dy;

//     // Ensure newX and newY are within the bounds of the map
//     if (newX >= 0 && newX < context->map->width && newY >= 0 && newY < context->map->height) {
//         context->map->data[context->map->player_y][context->map->player_x] = '0'; // Safe as old position is valid
//         context->map->player_x = newX;
//         context->map->player_y = newY;
//         context->map->data[newY][newX] = 'P'; // Ensure this is a valid index
//         return true;
//     }
//     return false;
// }

bool update_player_position(GameContext *context, int dx, int dy) {
    int newX = context->map->player_x + dx;
    int newY = context->map->player_y + dy;

    if (newX < 0 || newX >= context->map->width || newY < 0 || newY >= context->map->height) {
        return false;
    }

    char targetTile = context->map->data[newY][newX];
    if (targetTile == '1') { // Wall check
        return false;
    }

    // Move player to new position
    context->map->data[context->map->player_y][context->map->player_x] = '0'; // Clear old position
    context->map->player_x = newX;
    context->map->player_y = newY;
    context->map->data[newY][newX] = 'P';

    if (targetTile == 'C') { // Collectible found at the new position
        collected_count++;
        printf("Collected at [%d, %d]. Total collected: %d\n", newX, newY, collected_count);
        context->map->data[newY][newX] = '0'; // Remove collectible visually
        render_map(context->mlx, context->map, context->sprites); // Redraw map to update visuals
    }

    return true;
}



bool attempt_move(GameContext *context, int dx, int dy) {
    // Check if the move is possible
    int newX = context->map->player_x + dx;
    int newY = context->map->player_y + dy;

    if (check_boundaries(newX, newY, context->map)) {
        return update_player_position(context, dx, dy);
    }
    return false;
}


bool handle_movement(mlx_t* mlx, int key, int *key_down, GameContext *context) {
    if (mlx_is_key_down(mlx, key) && !*key_down) {
        *key_down = 1;
        int dx = 0, dy = 0;
        switch (key) {
            case MLX_KEY_W: dy = -1; break;
            case MLX_KEY_S: dy = 1; break;
            case MLX_KEY_A: dx = -1; break;
            case MLX_KEY_D: dx = 1; break;
        }
        // Correctly pass the entire context to update_player_position
        return update_player_position(context, dx, dy); 
    } else if (!mlx_is_key_down(mlx, key)) {
        *key_down = 0;
    }
    return false;
}



bool check_boundaries(int x, int y, t_map *map) {
    if (!map || !map->data || x < 0 || x >= map->width || y < 0 || y >= map->height) {
        printf("Boundary check failed for [%d, %d]\n", x, y);
        return false;
    }
    return map->data[y][x] != '1';
}

void collect_if_collectible(int x, int y, t_map *map) {
    if (map->data[y][x] == 'C') {  // Check if the target position has a collectible
        map->data[y][x] = '0';    // Remove the collectible from the map
        // Increase the count of collected items, update game state, etc.
        printf("Collected at [%d, %d].\n", x, y);
    }
}



bool check_all_collected() {
	printf("Checking if all collectibles have been collected...\n"); // Debug output
	if (collected_count == collectible_count) {
		printf("Congratulations! All collectibles have been collected!\n");
		// reveal_map(map); // Reveal the exit
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
