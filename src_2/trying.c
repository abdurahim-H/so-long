
#include "so_long.h"

void draw_tile(GameContext *context, int x, int y) {
    mlx_image_t* texture = context->sprites.floor;  // Default to floor
    char tile_type = context->map->data[y][x];

    switch (tile_type) {
        case '1': texture = context->sprites.wall; break;
        case 'C': texture = context->sprites.collectible; break;
        case 'E': texture = context->sprites.exit; break;
        case 'P': texture = context->sprites.player; break;
    }

    mlx_image_to_window(context->mlx, texture, x * TILE_SIZE, y * TILE_SIZE);
}

// Redraw the player's tile after movement to refresh the visuals
void redraw_player_tile(GameContext *context, int x, int y) {
    if (context->sprites.player) {
        mlx_image_to_window(context->mlx, context->sprites.player, x * TILE_SIZE, y * TILE_SIZE);
    }
}


// Function to handle player movement
void move_player(GameContext *context, int dx, int dy) {
    int new_x = context->map->player_x + dx;
    int new_y = context->map->player_y + dy;

    // Check boundaries and wall collisions
    if (new_x >= 0 && new_x < context->map->width && new_y >= 0 && new_y < context->map->height) {
        char new_pos_type = context->map->data[new_y][new_x];
        if (new_pos_type != '1') { // Assuming '1' is a wall
            // Move player
            context->map->data[context->map->player_y][context->map->player_x] = '0'; // Clear old position
            context->map->data[new_y][new_x] = 'P'; // Set new position
            context->map->player_x = new_x;
            context->map->player_y = new_y;
            redraw_player_tile(context, context->map->player_x, context->map->player_y); // Redraw new position
        }
    }
}
void handle_input(mlx_key_data_t key_data, void *param) {
    GameContext *context = (GameContext *)param;

    if (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT) {
        int dx = 0, dy = 0;
        switch (key_data.key) {
            case MLX_KEY_W:
            case MLX_KEY_UP:
                dy = -1; break;
            case MLX_KEY_S:
            case MLX_KEY_DOWN:
                dy = 1; break;
            case MLX_KEY_A:
            case MLX_KEY_LEFT:
                dx = -1; break;
            case MLX_KEY_D:
            case MLX_KEY_RIGHT:
                dx = 1; break;
            case MLX_KEY_ESCAPE:  // Handle exit
                mlx_close_window(context->mlx);
                return;
            default:
                // Handle other keys or do nothing
                break;
        }
        if (dx != 0 || dy != 0) {
            move_player(context, dx, dy);
        }
    }
}


// Define these in your configuration or directly in the code:
#define WALL "/Users/abhudulo/Desktop/c_projects/so_long/mystic_woods_free_2.1/sprites/objects/rock_in_water_01.png"
#define COLLECTABLE "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Egg_item.png"
#define DOOR "/Users/abhudulo/Desktop/c_projects/so_long/Sprout Lands - Sprites - Basic pack/Objects/Free_Chicken_House.png"
#define PLAYER "/Users/abhudulo/Desktop/c_projects/so_long/cat_0.png"

void load_sprites(mlx_t *mlx, GameSprites *sprites, int tile_width, int tile_height) {
    const char* paths[] = {WALL, COLLECTABLE, DOOR, PLAYER};
    for (int i = 0; i < sizeof(paths) / sizeof(paths[0]); i++) {
        mlx_texture_t *texture = mlx_load_png(paths[i]);
        if (!texture) {
            fprintf(stderr, "Failed to load texture from %s\n", paths[i]);
            continue;
        }
        printf("Loaded texture %s with size %dx%d\n", paths[i], texture->width, texture->height);

        // Assume mlx_texture_to_image resizes to fit tile dimensions
        *sprites[i] = mlx_texture_to_image(mlx, texture, tile_width, tile_height);
        if (!*sprites[i]) {
            fprintf(stderr, "Failed to convert texture to image for %s\n", paths[i]);
            mlx_delete_texture(texture);
        } else {
            printf("Sprite for %s created with size %dx%d\n", paths[i], tile_width, tile_height);
        }
    }
}



void redraw_tile(GameContext *context, int x, int y) {
    mlx_image_t* sprite_to_draw = NULL;
    char tile_type = context->map->data[y][x];

    switch (tile_type) {
        case '1': sprite_to_draw = context->sprites.wall; break;
        case 'C': sprite_to_draw = context->sprites.collectible; break;
        case 'E': sprite_to_draw = context->sprites.exit; break;
        case 'P': sprite_to_draw = context->sprites.player; break;
    }

    if (sprite_to_draw != NULL) {
        mlx_image_to_window(context->mlx, sprite_to_draw, x * TILE_SIZE, y * TILE_SIZE);
    } else {
        fprintf(stderr, "Attempted to draw a null sprite at [%d, %d], tile_type: %c\n", x, y, tile_type);
    }
}


void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char tile_type = map->data[y][x];
            mlx_image_t *sprite_to_draw = NULL;

            switch (tile_type) {
                case '1': sprite_to_draw = sprites->wall; break;
                case 'C': sprite_to_draw = sprites->collectible; break;
                case 'E': sprite_to_draw = sprites->exit; break;
                case 'P': sprite_to_draw = sprites->player; break;
            }

            if (sprite_to_draw) {
                mlx_image_to_window(mlx, sprite_to_draw, x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}




// Corrected free_sprites function that doesn't need mlx passed since it's not used
void free_sprites(mlx_t *mlx, GameSprites *sprites) {
    mlx_image_t* images[] = {sprites->wall, sprites->collectible, sprites->exit, sprites->player};
    for (int i = 0; i < sizeof(images) / sizeof(images[0]); i++) {
        if (images[i]) {
            mlx_delete_image(mlx, images[i]);
        }
    }
}



void setup_game_hooks(GameContext *context) {
    mlx_key_hook(context->mlx, handle_input, context);
}

void draw_player(GameContext *context) {
    if (context->sprites.player != NULL) {
        redraw_tile(context, context->map->player_x, context->map->player_y);
    } else {
        fprintf(stderr, "Player sprite is null.\n");
    }
}
