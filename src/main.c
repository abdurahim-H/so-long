#include "so_long.h"

mlx_image_t* image;
t_map* map;


Collectible* collectibles; // Array of collectibles
int collectible_count;     // Number of collectibles



// int32_t main(void)
// {
//     mlx_t* mlx;

//     // Parse the map
//     map = parse_map("assets/maps/map_file.ber");
//     if (!map)
//     {
//         puts("Failed to parse the map");
//         return(EXIT_FAILURE);
//     }

//     // Validate the map
//     if (!validate_map(map))
//     {
//         puts("Map validation failed.");
//         free_map(map); // Ensure to free the map to avoid memory leaks
//         return(EXIT_FAILURE);
//     }

//     // Initialize the window with the map dimensions
//     if (!(mlx = mlx_init((23*map->width), (20*map->height), "MLX42", true)))
//     {
//         puts(mlx_strerror(mlx_errno));
//         free_map(map); // Free the map if window initialization fails
//         return(EXIT_FAILURE);
//     }

//     // Create an image with the map dimensions
// 	if (!(image = mlx_new_image(mlx, (map->width), (map->height))))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}

// 	// Adjust the image position based on the player's coordinates
// 	if (mlx_image_to_window(mlx, image, (20 * player_x), (20 * player_y)) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}

//     // Collectibles and their accessibility
//     int collectible_count = count_collectibles(map->data, map->width, map->height);
//     Collectible *collectibles = malloc(collectible_count * sizeof(Collectible));
//     if (!collectibles) {
//         printf("Failed to allocate memory for collectibles.\n");
//         free_map(map);
//         return -1;
//     }

//     // Initialize collectible data
//     int index = 0;
//     int y = 0;
//     while (y < map->height) {
//         int x = 0;
//         while (x < map->width) {
//             if (map->data[y][x] == 'C') {
//                 collectibles[index++] = (Collectible){{x, y}, false};
//             }
//             x++;
//         }
//         y++;
//     }

//     // Perform BFS to check for a valid path
//     int start_x = 1, start_y = 1; // Example starting position, adjust based on your game's starting logic
//     bfs(map->data, start_x, start_y, map->width, map->height); // Assuming BFS sets a global flag if path is found

//     // Check if all collectibles are accessible
//     validateCollectibleAccessibility(map->data, start_x, start_y, map->width, map->height, collectibles, collectible_count);

//     bool all_visited = true;
//     for (int i = 0; i < collectible_count; i++) {
//         if (!collectibles[i].visited) {
//             all_visited = false;
//             break;
//         }
//     }

//     // Print results based on the accessibility check
//     if (all_visited) {
//         printf("All collectibles are accessible.\n");
//     }
//     else {
//         printf("Some collectibles are not accessible.\n");
//         free(collectibles);
//         free_map(map);
//         return (-1);
//     }

//     // Free collectibles after checking
//     free(collectibles);
//     game_loop(mlx);
// 	hide_exit();
//     free_map(map);
//     return (EXIT_SUCCESS);
// }


// int main(void) {
//     mlx_t *mlx;
//     GameSprites sprites;
//     t_map *map;

//     // Initialize MLX and load the map
//     mlx = mlx_init(800, 600, "so_long", true);
//     map = parse_map("assets/maps/map_file.ber");

//     // Load and initialize sprites
//     load_sprites(mlx, &sprites);

//     // Render initial state of the map
//     render_map(mlx, map, &sprites);

//     // Enter the game loop (adjust accordingly to your game structure)
//     mlx_loop(mlx);

//     // Cleanup
//     mlx_terminate(mlx);
//     free_map(map);
//     return 0;
// }


// int main(void) {
//     mlx_t* mlx;
//     GameSprites sprites;
//     t_map* map;

//     // Initialize MLX and parse the map
//     map = parse_map("assets/maps/map_file.ber");
//     if (!map) {
//         puts("Failed to parse the map");
//         return EXIT_FAILURE;
//     }

//     // Validate the map
//     if (!validate_map(map)) {
//         puts("Map validation failed.");
//         free_map(map);
//         return EXIT_FAILURE;
//     }

//     // Initialize the window with the map dimensions
//     if (!(mlx = mlx_init(43 * map->width, 40 * map->height, "MLX42", true))) {
//         puts(mlx_strerror(mlx_errno));
//         free_map(map);
//         return EXIT_FAILURE;
//     }

//     // Load and initialize sprites
//     load_sprites(mlx, &sprites);

//     // Collectibles and their accessibility
//     int collectible_count = count_collectibles(map->data, map->width, map->height);
//     Collectible *collectibles = malloc(collectible_count * sizeof(Collectible));
//     if (!collectibles) {
//         printf("Failed to allocate memory for collectibles.\n");
//         mlx_terminate(mlx);
//         free_map(map);
//         return -1;
//     }
// 	int index = 0;
// 	for (int y = 0; y < map->height; y++) {
// 		for (int x = 0; x < map->width; x++) {
// 			if (map->data[y][x] == 'C') {
// 				collectibles[index++] = (Collectible){{x, y}, false};
// 			}
// 		}
// 	}

//     // Perform BFS to check for a valid path
//     int start_x = 1, start_y = 1; // Example starting position, adjust based on your game's starting logic
//     bfs(map->data, start_x, start_y, map->width, map->height);

//     // Check if all collectibles are accessible
//     validateCollectibleAccessibility(map->data, start_x, start_y, map->width, map->height, collectibles, collectible_count);

//     bool all_visited = true;
//     for (int i = 0; i < collectible_count; i++) {
//         if (!collectibles[i].visited) {
//             all_visited = false;
//             break;
//         }
//     }

//     if (!all_visited) {
//         printf("Some collectibles are not accessible.\n");
//         free(collectibles);
//         mlx_terminate(mlx);
//         free_map(map);
//         return -1;
//     }

//     // Print results based on the accessibility check
//     printf("All collectibles are accessible.\n");

//     // Render initial state of the map
//     render_map(mlx, map, &sprites);

//     // Enter the game loop (adjust accordingly to your game structure)
//     mlx_loop(mlx);

//     // Cleanup
//     free(collectibles);
//     mlx_terminate(mlx);
//     free_map(map);
//     return EXIT_SUCCESS;
// }

// int main(void) {
//     mlx_t* mlx;
//     GameSprites sprites;

//     map = parse_map("assets/maps/map_file.ber");
//     if (!map) {
//         puts("Failed to parse the map");
//         return EXIT_FAILURE;
//     }

//     if (!validate_map(map)) {
//         puts("Map validation failed.");
//         free_map(map);
//         return EXIT_FAILURE;
//     }

//     mlx = mlx_init((23 * map->width), (20 * map->height), "MLX42", true);
//     if (!mlx) {
//         puts("Failed to initialize MLX");
//         free_map(map);
//         return EXIT_FAILURE;
//     }

//     load_sprites(mlx, &sprites);
//     render_map(mlx, map, &sprites);

//     mlx_loop_hook(mlx, ft_hook, mlx);
//     mlx_loop(mlx);

//     free_map(map);
//     mlx_terminate(mlx);
//     return EXIT_SUCCESS;
// }


#include "so_long.h"

int main(void) {
    mlx_t* mlx;
    GameSprites sprites;

    // Parse the map from the file
    map = parse_map("assets/maps/map_file.ber");
    if (!map) {
        puts("Failed to parse the map");
        return EXIT_FAILURE;
    }

    // Validate the parsed map
    if (!validate_map(map)) {
        puts("Map validation failed.");
        free_map(map);
        return EXIT_FAILURE;
    }

    // Initialize the MiniLibX window with dynamic dimensions based on the map size
    mlx = mlx_init(TILE_SIZE * map->width, TILE_SIZE * map->height, "MLX42", true);
    if (!mlx) {
        puts("Failed to initialize MLX");
        free_map(map);
        return EXIT_FAILURE;
    }

    // Load and scale sprites based on the TILE_SIZE
    load_sprites(mlx, &sprites, TILE_SIZE, TILE_SIZE);

    // Render the map with the loaded sprites
    render_map(mlx, map, &sprites);

    // Set the loop hook to handle game logic and events
    mlx_loop_hook(mlx, ft_hook, mlx);

    // Start the MLX event loop
    mlx_loop(mlx);

    // Clean up resources after the loop is terminated
    free_map(map);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}