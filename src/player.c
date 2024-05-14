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
    if (sprites->floor) {
        mlx_image_to_window(mlx, sprites->floor, x * TILE_SIZE, y * TILE_SIZE);
    }
    mlx_image_t *sprite = NULL;
    switch (map->data[y][x]) {
        case WALL: sprite = sprites->wall; break;
        case COLLECTIBLE: sprite = sprites->collectible; break;
        case EXIT: sprite = sprites->exit; break;
        case PLAYER: sprite = sprites->player; break;
    }
    if (sprite) {
        mlx_image_to_window(mlx, sprite, x * TILE_SIZE, y * TILE_SIZE);
    }
}

bool update_player_position(GameContext *context, int dx, int dy) {
    int new_x = context->map->player_x + dx;
    int new_y = context->map->player_y + dy;

    if (new_x < 0 || new_x >= context->map->width || new_y < 0 || new_y >= context->map->height) {
        return false;
    }

    char target_tile = context->map->data[new_y][new_x];
    if (target_tile == WALL) {
        return false;
    }

    context->map->data[context->map->player_y][context->map->player_x] = EMPTY;
    context->map->player_x = new_x;
    context->map->player_y = new_y;
    context->map->data[new_y][new_x] = PLAYER;

    if (target_tile == COLLECTIBLE) {
        collected_count++;
        printf("Collected at [%d, %d]. Total collected: %d\n", new_x, new_y, collected_count);
        context->map->data[new_y][new_x] = EMPTY;
        render_map(context->mlx, context->map, &context->sprites);
    }

    return true;
}

bool attempt_move(GameContext *context, int dx, int dy) {
    int new_x = context->map->player_x + dx;
    int new_y = context->map->player_y + dy;

    if (check_boundaries(new_x, new_y, context->map)) {
        return update_player_position(context, dx, dy);
    }
    return false;
}

bool handle_movement(mlx_t *mlx, int key, int *key_down, GameContext *context) {
    if (mlx_is_key_down(mlx, key) && !*key_down) {
        *key_down = 1;
        int dx = 0, dy = 0;
        switch (key) {
            case MLX_KEY_W: dy = -1; break;
            case MLX_KEY_S: dy = 1; break;
            case MLX_KEY_A: dx = -1; break;
            case MLX_KEY_D: dx = 1; break;
        }
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
    return map->data[y][x] != WALL;
}

void collect_if_collectible(int x, int y, t_map *map) {
    if (map->data[y][x] == COLLECTIBLE) {
        map->data[y][x] = EMPTY;
        printf("Collected at [%d, %d].\n", x, y);
    }
}

bool check_all_collected(t_map *map) {
    printf("Checking if all collectibles have been collected...\n");
    if (collected_count == collectible_count) {
        printf("Congratulations! All collectibles have been collected!\n");
        reveal_map(map);
        return true;
    }
    printf("Not all collectibles have been collected yet.\n");
    return false;
}

void collect_collectible(int x, int y, t_map *map) {
    printf("Attempting to collect at %d, %d (Map value: %c)\n", x, y, map->data[y][x]);
    if (map->data[y][x] == COLLECTIBLE) {
        map->data[y][x] = EMPTY;
        collected_count++;
        printf("Collectible collected at [%d, %d], total collected: %d/%d.\n", x, y, collected_count, collectible_count);
        if (check_all_collected(map)) {
            printf("All collectibles have been collected. Exit is revealed.\n");
        }
    }
}
