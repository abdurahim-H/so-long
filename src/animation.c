/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:24:30 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:45:19 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t* mlx_scale_image_to(mlx_t *mlx, mlx_image_t *image, int new_width, int new_height) {
    if (!image) {
        fprintf(stderr, "Input image is NULL.\n");
        return NULL;
    }

    mlx_image_t* scaled_image = mlx_new_image(mlx, new_width, new_height);
    if (!scaled_image) {
        fprintf(stderr, "Failed to create new image.\n");
        return NULL;
    }

    int bytes_per_pixel = 4; // Assuming all images are 32-bit
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int src_x = x * image->width / new_width;
            int src_y = y * image->height / new_height;

            uint8_t* src_pixel = &image->pixels[(src_y * image->width + src_x) * bytes_per_pixel];
            uint8_t* dst_pixel = &scaled_image->pixels[(y * new_width + x) * bytes_per_pixel];

            memmove(dst_pixel, src_pixel, bytes_per_pixel);
        }
    }

    return scaled_image;
}



// void load_sprites(mlx_t *mlx, GameSprites *sprites) {
// 	mlx_texture_t* temp;

// 	temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/mystic_woods_free_2.1/sprites/objects/rock_in_water_01.png");
// 	if (!temp) {
// 		fprintf(stderr, "Failed to load wall texture.\n");
// 		return;
// 	}
// 	sprites->wall = mlx_texture_to_image(mlx, temp);
// 	mlx_delete_texture(temp);

// 	temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Egg_item.png");
// 	if (!temp) {
// 		fprintf(stderr, "Failed to load collectible texture.\n");
// 		return;
// 	}
// 	sprites->collectible = mlx_texture_to_image(mlx, temp);
// 	mlx_delete_texture(temp);

// 	temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Free_Chicken_House.png");
// 	if (!temp) {
// 		fprintf(stderr, "Failed to load exit texture.\n");
// 		return;
// 	}
// 	sprites->exit = mlx_texture_to_image(mlx, temp);
// 	mlx_delete_texture(temp);

// 	temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/cat_0.png");
// 	if (!temp) {
// 		fprintf(stderr, "Failed to load player texture.\n");
// 		return;
// 	}
// 	sprites->player = mlx_texture_to_image(mlx, temp);
// 	mlx_delete_texture(temp);
// }


// void load_sprites(mlx_t *mlx, GameSprites *sprites) {
//     mlx_texture_t* temp;

//     temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/mystic_woods_free_2.1/sprites/objects/rock_in_water_01.png");
//     if (!temp) {
//         fprintf(stderr, "Failed to load wall texture.\n");
//         exit(EXIT_FAILURE);
//     }
//     sprites->wall = mlx_texture_to_image(mlx, temp);
//     mlx_delete_texture(temp);

//     temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Egg_item.png");
//     if (!temp) {
//         fprintf(stderr, "Failed to load collectible texture.\n");
//         exit(EXIT_FAILURE);
//     }
//     sprites->collectible = mlx_texture_to_image(mlx, temp);
//     mlx_delete_texture(temp);

//     temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Free_Chicken_House.png");
//     if (!temp) {
//         fprintf(stderr, "Failed to load exit texture.\n");
//         exit(EXIT_FAILURE);
//     }
//     sprites->exit = mlx_texture_to_image(mlx, temp);
//     mlx_delete_texture(temp);

//     temp = mlx_load_png("/Users/abhudulo/Desktop/c_projects/so_long/cat_0.png");
//     if (!temp) {
//         fprintf(stderr, "Failed to load player texture.\n");
//         exit(EXIT_FAILURE);
//     }
//     sprites->player = mlx_texture_to_image(mlx, temp);
//     mlx_delete_texture(temp);
// }

// void load_sprites(mlx_t *mlx, GameSprites *sprites, int tile_width, int tile_height) {
//     load_and_scale_sprite(mlx, &sprites->wall, "/Users/abhudulo/Desktop/c_projects/so_long/mystic_woods_free_2.1/sprites/objects/rock_in_water_01.png", tile_width, tile_height);
//     load_and_scale_sprite(mlx, &sprites->collectible, "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Egg_item.png", tile_width, tile_height);
//     load_and_scale_sprite(mlx, &sprites->exit, "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Free_Chicken_House.pn", tile_width, tile_height);
//     load_and_scale_sprite(mlx, &sprites->player, "/Users/abhudulo/Desktop/c_projects/so_long/cat_0.png", tile_width, tile_height);
// }

void load_and_scale_sprite(mlx_t *mlx, mlx_image_t **image, const char *file_path, int width, int height) {
    mlx_texture_t* temp_texture = mlx_load_png(file_path);
    if (!temp_texture) {
        fprintf(stderr, "Failed to load texture from %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    *image = mlx_texture_to_image(mlx, temp_texture);
    mlx_delete_texture(temp_texture);

    if (*image) {
        // Scale the image to fit the tile size
        mlx_image_t* scaled_image = mlx_scale_image_to(mlx, *image, width, height);
        if (scaled_image) {
            mlx_delete_image(mlx, *image);  // Delete the old image
            *image = scaled_image;          // Assign the scaled image
        }
    }
}

void load_sprites(mlx_t *mlx, GameSprites *sprites, int tile_width, int tile_height) {
    load_and_scale_sprite(mlx, &sprites->wall, "/Users/abhudulo/Desktop/c_projects/so_long/mystic_woods_free_2.1/sprites/objects/rock_in_water_01.png", tile_width, tile_height);
    load_and_scale_sprite(mlx, &sprites->collectible, "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Egg_item.png", tile_width, tile_height);
    load_and_scale_sprite(mlx, &sprites->exit, "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Free_Chicken_House.png", tile_width, tile_height);
    load_and_scale_sprite(mlx, &sprites->player, "/Users/abhudulo/Desktop/c_projects/so_long/cat_0.png", tile_width, tile_height);
}





// void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites) {
//     for (int y = 0; y < map->height; y++) {
//         for (int x = 0; x < map->width; x++) {
//             int px = x * TILE_SIZE;
//             int py = y * TILE_SIZE;

//             switch (map->data[y][x]) {
//                 case '1':
//                     mlx_image_to_window(mlx, sprites->wall, px, py);
//                     break;
//                 case 'C':
//                     mlx_image_to_window(mlx, sprites->collectible, px, py);
//                     break;
//                 case 'E':
//                     mlx_image_to_window(mlx, sprites->exit, px, py);
//                     break;
//                 case 'P':
//                     mlx_image_to_window(mlx, sprites->player, px, py);
//                     break;
//             }
//         }
//     }
// }

// void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites) {
//     for (int y = 0; y < map->height; y++) {
//         for (int x = 0; x < map->width; x++) {
//             int px = x * TILE_SIZE;
//             int py = y * TILE_SIZE;

//             if (!sprites->wall || !sprites->collectible || !sprites->exit || !sprites->player) {
//                 fprintf(stderr, "Sprite not loaded.\n");
//                 exit(EXIT_FAILURE);
//             }
            
//             switch (map->data[y][x]) {
//                 case '1':
//                     mlx_image_to_window(mlx, sprites->wall, px, py);
//                     break;
//                 case 'C':
//                     mlx_image_to_window(mlx, sprites->collectible, px, py);
//                     break;
//                 case 'E':
//                     mlx_image_to_window(mlx, sprites->exit, px, py);
//                     break;
//                 case 'P':
//                     mlx_image_to_window(mlx, sprites->player, px, py);
//                     break;
//             }
//         }
//     }
// }

// void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites) {
//     for (int y = 0; y < map->height; y++) {
//         for (int x = 0; x < map->width; x++) {
//             int px = x * TILE_SIZE;
//             int py = y * TILE_SIZE;

//             if (!sprites->wall || !sprites->collectible || !sprites->exit || !sprites->player) {
//                 fprintf(stderr, "Sprite not loaded.\n");
//                 exit(EXIT_FAILURE);
//             }

//             switch (map->data[y][x]) {
//                 case '1':
//                     mlx_image_to_window(mlx, sprites->wall, px, py);
//                     break;
//                 case 'C':
//                     mlx_image_to_window(mlx, sprites->collectible, px, py);
//                     break;
//                 case 'E':
//                     mlx_image_to_window(mlx, sprites->exit, px, py);
//                     break;
//                 case 'P':
//                     mlx_image_to_window(mlx, sprites->player, px, py);
//                     break;
//             }
//         }
//     }
// }


// void update_player_position(t_map *map, int dx, int dy) {
//     int newX = map->player_x + dx;
//     int newY = map->player_y + dy;

//     // Check for boundary conditions
//     if (newX < 0 || newX >= map->width || newY < 0 || newY >= map->height) {
//         return; // Prevent moving out of map bounds
//     }

//     // Check for collisions with walls
//     if (map->data[newY][newX] == '1') {
//         return; // Prevent moving into walls
//     }

//     // Update player position
//     map->data[map->player_y][map->player_x] = '0'; // Clear old position
//     map->player_x = newX;
//     map->player_y = newY;
//     map->data[newY][newX] = 'P'; // Set new position
// }

// void update_player_position(t_map *map, int dx, int dy) {
//     int newX = map->player_x + dx;
//     int newY = map->player_y + dy;

//     // Corrected boundary conditions
//     if (newX < 0 || newX >= map->width || newY < 0 || newY >= map->height) {
//         printf("Attempted to move out of bounds to %d, %d\n", newX, newY);
//         return; // Prevent moving out of map bounds
//     }

//     if (map->data[newY][newX] == '1') {
//         printf("Attempted to move into a wall at %d, %d\n", newX, newY);
//         return; // Prevent moving into walls
//     }

//     // Update player position
//     map->data[map->player_y][map->player_x] = '0'; // Clear old position
//     map->player_x = newX;
//     map->player_y = newY;
//     map->data[newY][newX] = 'P'; // Set new position
// }

// void update_player_position(t_map *map, int dx, int dy, mlx_t *mlx, GameSprites *sprites) {
//     int newX = map->player_x + dx;
//     int newY = map->player_y + dy;

//     if (newX < 0 || newX >= map->width || newY < 0 || newY >= map->height) {
//         printf("Attempted to move out of bounds to %d, %d\n", newX, newY);
//         return; // Prevent moving out of map bounds
//     }

//     if (map->data[newY][newX] == '1') {
//         printf("Attempted to move into a wall at %d, %d\n", newX, newY);
//         return; // Prevent moving into walls
//     }

//     map->data[map->player_y][map->player_x] = '0'; // Clear old position
//     map->player_x = newX;
//     map->player_y = newY;
//     map->data[newY][newX] = 'P'; // Set new position

//     render_map(mlx, map, sprites); // Redraw the map with the new player position
// }

void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            int px = x * TILE_SIZE;
            int py = y * TILE_SIZE;

            if (!sprites->wall || !sprites->collectible || !sprites->exit || !sprites->player) {
                fprintf(stderr, "Sprite not loaded.\n");
                exit(EXIT_FAILURE);
            }

            switch (map->data[y][x]) {
                case '1':
                    mlx_image_to_window(mlx, sprites->wall, px, py);
                    break;
                case 'C':
                    mlx_image_to_window(mlx, sprites->collectible, px, py);
                    break;
                case 'E':
                    mlx_image_to_window(mlx, sprites->exit, px, py);
                    break;
                case 'P':
                    mlx_image_to_window(mlx, sprites->player, px, py);
                    break;
            }
        }
    }
}


void update_player_position(t_map *map, int dx, int dy) {
    int newX = map->player_x + dx;
    int newY = map->player_y + dy;

    // Corrected boundary conditions
    if (newX < 0 || newX >= map->width || newY < 0 || newY >= map->height) {
        printf("Attempted to move out of bounds to %d, %d\n", newX, newY);
        return; // Prevent moving out of map bounds
    }

    if (map->data[newY][newX] == '1') {
        printf("Attempted to move into a wall at %d, %d\n", newX, newY);
        return; // Prevent moving into walls
    }

    // Update player position
    map->data[map->player_y][map->player_x] = '0'; // Clear old position
    map->player_x = newX;
    map->player_y = newY;
    map->data[newY][newX] = 'P'; // Set new position
}



// void ft_hook(void *param) {
//     mlx_t *mlx = (mlx_t *)param;
//     mlx_key_hook(mlx, handle_key_events, param);  // Make sure key events are handled
// }

// void handle_key_events(mlx_key_data_t keydata, void *param) {
//     t_map *map = param;  // Ensure this parameter passing is set up correctly
//     if (keydata.action == MLX_PRESS) {
//         switch (keydata.key) {
//             case MLX_KEY_W: update_player_position(map, 0, -1); break;
//             case MLX_KEY_S: update_player_position(map, 0, 1); break;
//             case MLX_KEY_A: update_player_position(map, -1, 0); break;
//             case MLX_KEY_D: update_player_position(map, 1, 0); break;
//         }
//     }
//     render_map(mlx, map, sprites);  // Make sure `sprites` and `mlx` are available
// }

// void setup_key_hooks(mlx_t *mlx, t_map *map) {
//     mlx_key_hook(mlx, handle_key_events, map);
// }