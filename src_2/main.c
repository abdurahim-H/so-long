#include "so_long.h"

mlx_image_t* image;
t_map* map;


int player_x = -1;
int player_y = -1;

Collectible* collectibles;
int collectible_count;


void cleanup_game(GameContext *context) {
    if (context->sprites.wall) mlx_delete_image(context->mlx, context->sprites.wall);
    if (context->sprites.collectible) mlx_delete_image(context->mlx, context->sprites.collectible);
    if (context->sprites.exit) mlx_delete_image(context->mlx, context->sprites.exit);
    if (context->sprites.player) mlx_delete_image(context->mlx, context->sprites.player);
    if (context->sprites.floor) mlx_delete_image(context->mlx, context->sprites.floor);

    // After all resources are safely freed
    mlx_terminate(context->mlx);
}

// int main(int argc, char **argv) {
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     GameContext context = {0};  // Initialize to zero to ensure all fields start as NULL or zero.
//     context.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "so_long", true);
//     if (!context.mlx) {
//         fprintf(stderr, "Failed to initialize MLX.\n");
//         return EXIT_FAILURE;
//     }

//     context.map = parse_map(argv[1]);
//     if (!context.map || !validate_map(context.map)) {
//         fprintf(stderr, "Failed to load or validate the map.\n");
//         if (context.map) {
//             free_map(context.map);
//         }
//         mlx_terminate(context.mlx);
//         return EXIT_FAILURE;
//     }

//     load_sprites(context.mlx, &context.sprites, TILE_SIZE, TILE_SIZE);
//     render_map(context.mlx, context.map, &context.sprites); // Initial render

//     mlx_key_hook(context.mlx, ft_key_hook, &context); // Setup key hook
//     mlx_loop(context.mlx); // Start event loop

//     // Cleanup resources
//     if (context.sprites.wall) mlx_delete_image(context.mlx, context.sprites.wall);
//     if (context.sprites.collectible) mlx_delete_image(context.mlx, context.sprites.collectible);
//     if (context.sprites.exit) mlx_delete_image(context.mlx, context.sprites.exit);
//     if (context.sprites.player) mlx_delete_image(context.mlx, context.sprites.player);
//     if (context.sprites.floor) mlx_delete_image(context.mlx, context.sprites.floor);

//     free_map(context.map);
//     mlx_terminate(context.mlx);  // This should be the last call related to MLX.

//     return EXIT_SUCCESS;
// }



// int main(int argc, char **argv) {
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <map_file_path>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     GameContext context;
//     context.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "So Long, and Thanks for All the Fish!", true);
//     if (!context.mlx) {
//         fprintf(stderr, "Failed to initialize MLX.\n");
//         return EXIT_FAILURE;
//     }

//     // Parse the map from the given file path
//     context.map = parse_map(argv[1]);
//     if (!context.map) {
//         fprintf(stderr, "Failed to load or parse the map.\n");
//         mlx_terminate(context.mlx);
//         return EXIT_FAILURE;
//     }

//     // Initialize sprites
//     load_sprites(context.mlx, &context.sprites, TILE_SIZE, TILE_SIZE);

//     // Validate the map
//     if (!validate_map(context.map)) {
//         fprintf(stderr, "Map validation failed.\n");
//         free_map(context.map);
//         mlx_terminate(context.mlx);
//         return EXIT_FAILURE;
//     }

//     // Initial rendering of the map
//     render_map(context.mlx, context.map, &context.sprites);
//     draw_player(&context);  // Draw the player initially

//     // Setup event handling
//     setup_game_hooks(&context);

//     // Start the game loop
//     game_loop(context.mlx, &context);

//     // Cleanup resources
//     free_map(context.map);
//     mlx_terminate(context.mlx);
//     return EXIT_SUCCESS;
// }


// int main(int argc, char **argv) {
//     if (argc != 2) {
//         fprintf(stderr, "Error: Incorrect usage. Please provide the map file as an argument.\n");
//         return EXIT_FAILURE;
//     }

//     // Initialize the game context and related structures
//     GameContext gameContext;
//     gameContext.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "So Long", true);
//     if (!gameContext.mlx) {
//         fprintf(stderr, "Error: Failed to initialize MLX.\n");
//         return EXIT_FAILURE;
//     }

//     // Parse the map from the provided file
//     gameContext.map = parse_map(argv[1]);
//     if (!gameContext.map || !validate_map(gameContext.map)) {
//         fprintf(stderr, "Error: Failed to load or validate map.\n");
//         free_map(gameContext.map);
//         mlx_terminate(gameContext.mlx);
//         return EXIT_FAILURE;
//     }

//     // Load and assign sprites
//     if (!load_sprites(gameContext.mlx, &gameContext.sprites, TILE_SIZE, TILE_SIZE)) {
//         fprintf(stderr, "Error: Failed to load sprites.\n");
//         free_map(gameContext.map);
//         mlx_terminate(gameContext.mlx);
//         return EXIT_FAILURE;
//     }

//     // Set up game hooks (for keyboard input etc.)
//     mlx_key_hook(gameContext.mlx, &ft_key_hook, &gameContext);

//     // Draw the initial game state
//     render_map(gameContext.mlx, gameContext.map, &gameContext.sprites);
//     draw_player(&gameContext);

//     // Start the MLX loop to handle events and updates
//     mlx_loop(gameContext.mlx);

//     // Cleanup resources on exit
//     free_map(gameContext.map);
//     free_sprites(&gameContext.sprites); // Make sure this function is defined
//     mlx_terminate(gameContext.mlx);

//     return EXIT_SUCCESS;
// }

// #include "so_long.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map file path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize the game context
    GameContext context;
    context.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "So Long", true);
    if (!context.mlx) {
        fprintf(stderr, "Failed to initialize MLX.\n");
        return EXIT_FAILURE;
    }

    // Load and parse the map
    context.map = parse_map(argv[1]);
    if (!context.map) {
        fprintf(stderr, "Failed to load or parse the map.\n");
        mlx_terminate(context.mlx);
        return EXIT_FAILURE;
    }

    // Load sprites
    if (!load_sprites(context.mlx, &context.sprites, TILE_SIZE, TILE_SIZE)) {
        fprintf(stderr, "Failed to load sprites.\n");
        free_map(context.map);
        mlx_terminate(context.mlx);
        return EXIT_FAILURE;
    }

    // Ensure all necessary sprites are loaded
    if (!context.sprites.wall || !context.sprites.collectible || !context.sprites.exit || !context.sprites.player) {
        fprintf(stderr, "One or more sprites are not loaded.\n");
        free_sprites(context.mlx, &context.sprites);
        free_map(context.map);
        mlx_terminate(context.mlx);
        return EXIT_FAILURE;
    }

    // Setup game hooks for keyboard input
    setup_game_hooks(&context);

    // Draw initial state of the map
    render_map(context.mlx, context.map, &context.sprites);
    draw_player(&context);

    // Start the main loop
    mlx_loop(context.mlx);

    // Cleanup resources after the loop ends
    free_sprites(context.mlx, &context.sprites);
    free_map(context.map);
    mlx_terminate(context.mlx);

    return EXIT_SUCCESS;
}
