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

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    GameContext context = {0};  // Initialize to zero to ensure all fields start as NULL or zero.
    context.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "so_long", true);
    if (!context.mlx) {
        fprintf(stderr, "Failed to initialize MLX.\n");
        return EXIT_FAILURE;
    }

    context.map = parse_map(argv[1]);
    if (!context.map || !validate_map(context.map)) {
        fprintf(stderr, "Failed to load or validate the map.\n");
        if (context.map) {
            free_map(context.map);
        }
        mlx_terminate(context.mlx);
        return EXIT_FAILURE;
    }

    load_sprites(context.mlx, &context.sprites, TILE_SIZE, TILE_SIZE);
    render_map(context.mlx, context.map, &context.sprites); // Initial render

    mlx_key_hook(context.mlx, ft_key_hook, &context); // Setup key hook
    mlx_loop(context.mlx); // Start event loop

    // Cleanup resources
    if (context.sprites.wall) mlx_delete_image(context.mlx, context.sprites.wall);
    if (context.sprites.collectible) mlx_delete_image(context.mlx, context.sprites.collectible);
    if (context.sprites.exit) mlx_delete_image(context.mlx, context.sprites.exit);
    if (context.sprites.player) mlx_delete_image(context.mlx, context.sprites.player);
    if (context.sprites.floor) mlx_delete_image(context.mlx, context.sprites.floor);

    free_map(context.map);
    mlx_terminate(context.mlx);  // This should be the last call related to MLX.
	check_leaks();

    return EXIT_SUCCESS;
}
