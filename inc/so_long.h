#ifndef SO_LONG_H
#define SO_LONG_H

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include "../lib/MiniLibX/include/MLX42/MLX42.h"

#define WINDOW_WIDTH 800  
#define WINDOW_HEIGHT 600 
#define TILE_SIZE 62
#define PLAYER 'P'
#define WALL '1'
#define COLLECTIBLE 'C'
#define EXIT 'E'
#define EMPTY '0'

typedef struct {
    int is_pressed;
} KeyState;

typedef struct {
    int width;
    int height;
    char **data;
    int player_x;
    int player_y;
} t_map;

typedef struct {
    mlx_image_t* wall;
    mlx_image_t* collectible;
    mlx_image_t* exit;
    mlx_image_t* player;
    mlx_image_t* floor;
} GameSprites;

typedef struct {
    mlx_t *mlx;
    t_map *map;
    GameSprites sprites;
} GameContext;

typedef struct s_node {
    int x;
    int y;
    struct s_node *next;
} t_node;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point pos;
    bool visited;
} Collectible;

typedef struct Node {
    Point point;
    struct Node* next;
} Node;

extern int collectible_count;
extern int exit_x, exit_y;

// Function declarations
char *read_file_content(const char *file_path);
void calculate_map_dimensions(const char *content, int *width, int *height);
void fill_map_data(char **data, const char *content, int height, int width);
t_map *parse_map(const char *file_path);
void free_map(t_map *map);
void randomize(void* param);
int32_t pixel(int32_t r, int32_t g, int32_t b, int32_t a);
bool validate_map(t_map *map);
char **allocate_map_data(int width, int height);
bool check_borders(t_map *map);
bool check_rectangular_shape(t_map *map);
void update_position(int new_x, int new_y);
void game_hook(void *param);
void enqueue(t_node **head, int x, int y);
bool dequeue(t_node **head, int *x, int *y);
bool bfs(char **map, int start_x, int start_y, int map_width, int map_height);
void validate_collectible_accessibility(char** map, int start_x, int start_y, int map_width, int map_height, Collectible* collectibles, int collectible_count);
void enqueue_collectible(Node** head, Point point);
bool dequeue_collectible(Node** head, Point* point);
bool** initialize_visited(int width, int height);
void validate_collectible_accessibility(char **map, int start_x, int start_y, int width, int height, Collectible *collectibles, int collectible_count);
int count_collectibles(char **map, int width, int height);
// void collect_collectible(int x, int y);
bool check_all_collected(t_map *map);
int count_collectibles(char** map, int width, int height);
void reveal_map(t_map *map);
void hide_exit(t_map *map);
void collect_collectible(int x, int y, t_map *map);
void update_display(GameContext *context);
void redraw_tile(GameContext *game, int x, int y);
void key_hook(mlx_key_data_t keydata, void *param);
void load_and_scale_sprite(mlx_t *mlx, mlx_image_t **image, const char *file_path, int width, int height);
void game_loop(mlx_t* mlx, GameContext *context);
void set_player_position(int x, int y, t_map *map);
void key_press(mlx_key_data_t key_data, void *param);
void key_release(int keycode, GameContext *context);
// void setup_game(GameContext *context);
void setup_game(GameContext *context, const char *map_file_path);
void collect_if_collectible(int x, int y, t_map *map);
void error_and_cleanup(GameContext *game, const char *msg);
void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites);
void tile_draw(t_map *map, mlx_image_t *image, int x, int y);
void redraw_tile(GameContext *game, int x, int y);
bool handle_movement(mlx_t* mlx, int key, int *key_down, GameContext *context);
void handle_player_input(int key, GameContext *context);
bool check_boundaries(int x, int y, t_map *map);
bool attempt_move(GameContext *context, int dx, int dy);
bool update_player_position(GameContext *context, int dx, int dy);
void draw_tile(mlx_t *mlx, t_map *map, GameSprites *sprites, int x, int y);
void redraw_player_tile(GameContext *context, int x, int y);
void move_player(GameContext *context, int dx, int dy);
void setup_game_hooks(GameContext *context);
void draw_player(GameContext *context);
void load_sprites(mlx_t *mlx, GameSprites *sprites, int tile_width, int tile_height);
void free_sprites(mlx_t *mlx, GameSprites *sprites);
void handle_input(mlx_key_data_t key_data, void *param);
void redraw_tile(GameContext *context, int x, int y);
void render_map(mlx_t *mlx, t_map *map, GameSprites *sprites);
void draw_tile(mlx_t *mlx, t_map *map, GameSprites *sprites, int x, int y);
void check_leaks();



#endif
