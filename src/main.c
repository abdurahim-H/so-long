#include "so_long.h"

// int collectible_count = 0;
// int exit_x = -1, exit_y = -1;

void cleanup_game(GameContext *context) {
    free_sprites(context->mlx, &context->sprites);
    mlx_terminate(context->mlx);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    GameContext context = {0};
    setup_game(&context, argv[1]);

    mlx_key_hook(context.mlx, key_hook, &context);
    mlx_loop(context.mlx);

    cleanup_game(&context);
    free_map(context.map);

    return EXIT_SUCCESS;
}
