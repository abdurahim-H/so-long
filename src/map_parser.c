#include "so_long.h"

int exit_x = -1, exit_y = -1;

void count_elements(t_map *map, int i, int *counts) {
    for (int j = 0; j < map->width; j++) {
        char c = map->data[i][j];
        if (c == PLAYER) {
            counts[0]++;
        } else if (c == EXIT) {
            counts[1]++;
        } else if (c == COLLECTIBLE) {
            counts[2]++;
        }
    }
}

bool check_elements(t_map *map) {
    int counts[3] = {0, 0, 0};
    for (int i = 0; i < map->height; i++) {
        count_elements(map, i, counts);
    }
    return counts[0] == 1 && counts[1] >= 1 && counts[2] >= 1;
}

bool validate_map(t_map *map) {
    if (!map) {
        return false;
    }
    const char *valid_chars = "01CEP";
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (!strchr(valid_chars, map->data[y][x])) {
                fprintf(stderr, "Invalid character found: %c\n", map->data[y][x]);
                return false;
            }
        }
    }
    if (!check_borders(map) || !check_elements(map) || !check_rectangular_shape(map)) {
        fprintf(stderr, "Map validation failed.\n");
        return false;
    }
    return true;
}

t_map *parse_map(const char *file_path) {
    printf("Reading map content from %s\n", file_path);
    char *content = read_file_content(file_path);
    if (!content) {
        fprintf(stderr, "Failed to read map content.\n");
        return NULL;
    }

    t_map *map = malloc(sizeof(t_map));
    if (!map) {
        fprintf(stderr, "Memory allocation failed for map structure.\n");
        free(content);
        return NULL;
    }

    calculate_map_dimensions(content, &map->width, &map->height);
    map->data = allocate_map_data(map->width, map->height);
    if (!map->data) {
        fprintf(stderr, "Failed to allocate map data.\n");
        free(map);
        free(content);
        return NULL;
    }

    fill_map_data(map->data, content, map->height, map->width);
    free(content);

    bool found_player = false;
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->data[y][x] == PLAYER) {
                if (found_player) {
                    fprintf(stderr, "Multiple player start positions found.\n");
                    free_map(map);
                    return NULL;
                }
                map->player_x = x;
                map->player_y = y;
                found_player = true;
                printf("Player initial position set to [%d, %d]\n", map->player_x, map->player_y);
            }
        }
    }

    if (!found_player) {
        fprintf(stderr, "Player start position not found.\n");
        free_map(map);
        return NULL;
    }

    printf("Map parsed successfully. Player position: %d, %d\n", map->player_x, map->player_y);
    assert(map->player_x >= 0 && map->player_x < map->width);
    assert(map->player_y >= 0 && map->player_y < map->height);
    return map;
}

void free_map(t_map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->data[i]);
    }
    free(map->data);
    free(map);
}
