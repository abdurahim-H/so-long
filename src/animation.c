#include "so_long.h"

mlx_image_t *scale_image(mlx_t *mlx, mlx_image_t *image, int new_width, int new_height) {
    if (!image) {
        fprintf(stderr, "Input image is NULL.\n");
        return NULL;
    }

    mlx_image_t *scaled_image = mlx_new_image(mlx, new_width, new_height);
    if (!scaled_image) {
        fprintf(stderr, "Failed to create new image.\n");
        return NULL;
    }

    int bytes_per_pixel = 4;
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int src_x = x * image->width / new_width;
            int src_y = y * image->height / new_height;

            uint8_t *src_pixel = &image->pixels[(src_y * image->width + src_x) * bytes_per_pixel];
            uint8_t *dst_pixel = &scaled_image->pixels[(y * new_width + x) * bytes_per_pixel];

            memmove(dst_pixel, src_pixel, bytes_per_pixel);
        }
    }

    return scaled_image;
}

void load_and_scale_sprite(mlx_t *mlx, mlx_image_t **image, const char *file_path, int width, int height) {
    mlx_texture_t *temp_texture = mlx_load_png(file_path);
    if (!temp_texture) {
        fprintf(stderr, "Failed to load texture from %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    *image = mlx_texture_to_image(mlx, temp_texture);
    mlx_delete_texture(temp_texture);

    if (*image) {
        mlx_image_t *scaled_image = scale_image(mlx, *image, width, height);
        if (!scaled_image) {
            fprintf(stderr, "Failed to scale image for %s\n", file_path);
            exit(EXIT_FAILURE);
        }
        mlx_delete_image(mlx, *image);
        *image = scaled_image;
        printf("Loaded and scaled %s successfully.\n", file_path);
    }
}

void load_sprites(mlx_t *mlx, GameSprites *sprites, int tile_width, int tile_height) {
	load_and_scale_sprite(mlx, &sprites->wall, "/Users/abhudulo/Desktop/c_projects/so_long/mystic_woods_free_2.1/sprites/objects/rock_in_water_01.png", tile_width, tile_height);
	load_and_scale_sprite(mlx, &sprites->collectible, "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Egg_item.png", tile_width, tile_height);
	load_and_scale_sprite(mlx, &sprites->exit, "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Free_Chicken_House.png", tile_width, tile_height);
	load_and_scale_sprite(mlx, &sprites->player, "/Users/abhudulo/Desktop/c_projects/so_long/cat_0.png", tile_width, tile_height);
	printf("All sprites loaded successfully.\n");
}

void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char tile = map->data[y][x];
            mlx_image_t *sprite_to_draw = NULL;
            switch (tile) {
                case EMPTY: continue;
                case WALL: sprite_to_draw = sprites->wall; break;
                case COLLECTIBLE: sprite_to_draw = sprites->collectible; break;
                case EXIT: sprite_to_draw = sprites->exit; break;
                case PLAYER: sprite_to_draw = sprites->player; break;
            }
            if (sprite_to_draw) {
                mlx_image_to_window(mlx, sprite_to_draw, x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}

void key_hook(mlx_key_data_t keydata, void *param) {
    GameContext *context = (GameContext *)param;
    if (keydata.key == MLX_KEY_ESCAPE) {
        mlx_close_window(context->mlx);
    } else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
        handle_player_input(keydata.key, context);
    }
}

void handle_player_input(int key, GameContext *context) {
    int dx = 0;
    int dy = 0;

    switch (key) {
        case MLX_KEY_W: dy = -1; break;
        case MLX_KEY_S: dy = 1; break;
        case MLX_KEY_A: dx = -1; break;
        case MLX_KEY_D: dx = 1; break;
    }

    if (attempt_move(context, dx, dy)) {
        render_map(context->mlx, context->map, &context->sprites);
    }
}

void setup_game(GameContext *context, const char *map_file_path) {
    context->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "so_long", true);
    if (!context->mlx) {
        fprintf(stderr, "Failed to initialize MLX.\n");
        exit(EXIT_FAILURE);
    }

    context->map = parse_map(map_file_path);
    if (!context->map || !validate_map(context->map)) {
        fprintf(stderr, "Failed to load or validate map.\n");
        if (context->map) {
            free_map(context->map);
        }
        mlx_terminate(context->mlx);
        exit(EXIT_FAILURE);
    }

    load_sprites(context->mlx, &context->sprites, TILE_SIZE, TILE_SIZE);
    render_map(context->mlx, context->map, &context->sprites);
}
