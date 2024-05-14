#include "so_long.h"

void update_key_state(KeyState *state, int is_currently_pressed) {
    if (is_currently_pressed && !state->is_pressed) {
        state->is_pressed = 1;
        printf("Key Pressed\n");
    } else if (!is_currently_pressed && state->is_pressed) {
        state->is_pressed = 0;
        printf("Key Released\n");
    }
}

static int w_key_down = 0, s_key_down = 0, a_key_down = 0, d_key_down = 0;

void game_hook(void *param) {
    GameContext *context = (GameContext *)param;
    if (mlx_is_key_down(context->mlx, MLX_KEY_W)) handle_player_input(MLX_KEY_W, context);
    if (mlx_is_key_down(context->mlx, MLX_KEY_S)) handle_player_input(MLX_KEY_S, context);
    if (mlx_is_key_down(context->mlx, MLX_KEY_A)) handle_player_input(MLX_KEY_A, context);
    if (mlx_is_key_down(context->mlx, MLX_KEY_D)) handle_player_input(MLX_KEY_D, context);
}
