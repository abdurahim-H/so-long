/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:01:24 by abhudulo          #+#    #+#             */
/*   Updated: 2024/06/01 21:30:59 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <ctype.h>
# include <assert.h>
# include "../lib/MiniLibX/include/MLX42/MLX42_Int.h"
# include "../lib/MiniLibX/include/MLX42/MLX42.h"

# define WINDOW_WIDTH 1300  
# define WINDOW_HEIGHT 850 
# define TILE_SIZE 96
# define PLAYER 'P'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define EMPTY '0'

typedef struct s_key_state
{
	int				is_pressed;
}	t_key_state;

typedef struct s_map
{
	int				width;
	int				height;
	char			**data;
	int				player_x;
	int				player_y;
	int				start_x;
	int				start_y;
}	t_map;

typedef struct s_game_sprites
{
	mlx_image_t		*wall;
	mlx_image_t		*collectible;
	mlx_image_t		*exit;
	mlx_image_t		*player;
	mlx_image_t		*floor;
}	t_game_sprites;

typedef struct s_game_context
{
	mlx_t			*mlx;
	t_map			*map;
	t_game_sprites	sprites;
}	t_game_context;

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

typedef struct s_collectible
{
	t_point			pos;
	bool			visited;
}	t_collectible;

typedef struct s_Node
{
	t_point			point;
	struct s_Node	*next;
}	t_Node;

typedef struct s_scale_pixel_args
{
	mlx_image_t	*image;
	mlx_image_t	*scaled_image;
	int			x;
	int			y;
	int			new_width;
	int			new_height;
}	t_scale_pixel_args;

typedef struct s_sprite_args
{
	mlx_t		*mlx;
	mlx_image_t	**image;
	const char	*file_path;
	int			width;
	int			height;
}	t_sprite_args;

typedef struct s_map_info
{
	int		map_width;
	int		map_height;
	char	**map;
}	t_map_info;

typedef struct s_queue_info
{
	t_Node		**queue;
	bool		**visited;
	t_map_info	*map_info;
}	t_queue_info;

typedef struct s_draw_context
{
	mlx_t			*mlx;
	t_map			*map;
	t_game_sprites	*sprites;
}	t_draw_context;

typedef struct s_bfs
{
	char			**map;
	t_node			*queue;
	int				*dx;
	int				*dy;
	bool			**visited;
	int				map_width;
	int				map_height;
}	t_bfs;

typedef struct s_mapinfo
{
	char	**map;
	int		map_width;
	int		map_height;
}	t_mapinfo;

extern int	g_exit_x;
extern int	g_exit_y;
extern int	g_total_collectibles;
extern int	g_collected_count;

char		*read_file_content(const char *file_path);
void		calculate_map_dimensions(const char *content,
				int *width, int *height);
void		fill_map_data(char **data, const char *content,
				int height, int width);
t_map		*parse_map(const char *file_path);
char		**allocate_map_data(int width, int height);
bool		check_borders(t_map *map);
void		game_hook(void *param);
void		enqueue(t_node **head, int x, int y);
bool		dequeue(t_node **head, int *x, int *y);
bool		bfs(t_mapinfo mapInfo, int start_x, int start_y);
void		enqueue_collectible(t_Node **head, t_point point);
bool		dequeue_collectible(t_Node **head, t_point *point);
bool		**initialize_visited(int width, int height);
void		validate_collectible_accessibility(t_map_info *map_info,
				int start_x, int start_y);
bool		check_all_collected(t_map *map);
void		collect_collectible(int x, int y, t_map *map);
void		key_hook(mlx_key_data_t keydata, void *param);
mlx_image_t	*create_scaled_image(mlx_t *mlx, mlx_image_t *image, int new_width,
				int new_height);
void		scale_pixel(t_scale_pixel_args *args);
void		scale_pixels(mlx_image_t *image, mlx_image_t *scaled_image,
				int new_width, int new_height);
void		load_and_scale_sprite(t_sprite_args *args);
void		game_loop(mlx_t *mlx, t_game_context *context);
void		set_player_position(int x, int y, t_map *map);
bool		setup_game(t_game_context *context, const char *map_file_path);
void		collect_if_collectible(int x, int y, t_map *map);
void		render_map(mlx_t *mlx, t_map *map, t_game_sprites *sprites);
bool		handle_movement(mlx_t *mlx, int key, int *key_down,
				t_game_context *context);
void		handle_player_input(int key, t_game_context *context);
bool		check_boundaries(int x, int y, t_map *map);
bool		attempt_move(t_game_context *context, int dx, int dy);
bool		update_player_position(t_game_context *context, int dx, int dy);
void		load_sprites(mlx_t *mlx, t_game_sprites *sprites,
				int tile_width, int tile_height);
void		free_sprites(mlx_t *mlx, t_game_sprites *sprites);
void		draw_tile(t_draw_context *context, int x, int y);
bool		can_exit_game(t_map *map, int x, int y);
int			count_collectibles(char **map, int width, int height);
void		cleanup_game(t_game_context *context);
char		*allocate_buffer(int fd, struct stat *statbuf);
void		exit_game(mlx_t *mlx);
bool		is_valid_position(t_game_context *context, int new_x, int new_y);

#endif