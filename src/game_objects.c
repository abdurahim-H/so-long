#include "so_long.h"

void game_loop(mlx_t *mlx, GameContext *context) {
    mlx_loop_hook(mlx, game_hook, context);
    mlx_loop(mlx);
    mlx_terminate(mlx);
}

void hide_exit(t_map *map) {
    if (exit_x != -1 && exit_y != -1) {
        printf("Hiding exit at [%d, %d].\n", exit_x, exit_y);
        map->data[exit_y][exit_x] = EMPTY;
    }
}

void reveal_map(t_map *map) {
    if (exit_x != -1 && exit_y != -1) {
        printf("Revealing exit at [%d, %d].\n", exit_x, exit_y);
        map->data[exit_y][exit_x] = EXIT;
    }
}

void free_sprites(mlx_t *mlx, GameSprites *sprites) {
    if (sprites->wall) {
        mlx_delete_image(mlx, sprites->wall);
        sprites->wall = NULL;
    }
    if (sprites->collectible) {
        mlx_delete_image(mlx, sprites->collectible);
        sprites->collectible = NULL;
    }
    if (sprites->exit) {
        mlx_delete_image(mlx, sprites->exit);
        sprites->exit = NULL;
    }
    if (sprites->player) {
        mlx_delete_image(mlx, sprites->player);
        sprites->player = NULL;
    }
    if (sprites->floor) {
        mlx_delete_image(mlx, sprites->floor);
        sprites->floor = NULL;
    }
}
