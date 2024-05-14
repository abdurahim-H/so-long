#include "so_long.h"

char *read_file_content(const char *file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return NULL;
    }
    struct stat statbuf;
    if (fstat(fd, &statbuf) == -1) {
        perror("Failed to get file statistics");
        close(fd);
        return NULL;
    }
    char *buffer = malloc(statbuf.st_size + 1);
    if (!buffer) {
        perror("Failed to allocate memory for file content");
        close(fd);
        return NULL;
    }
    ssize_t bytes_read = read(fd, buffer, statbuf.st_size);
    if (bytes_read == -1) {
        perror("Failed to read file content");
        free(buffer);
        close(fd);
        return NULL;
    }
    buffer[bytes_read] = '\0';
    close(fd);
    return buffer;
}

void calculate_map_dimensions(const char *content, int *width, int *height) {
    const char *temp_content = content;
    *height = 0;
    *width = 0;
    while (*temp_content) {
        if (*temp_content == '\n') {
            if (*height == 0) {
                *width = temp_content - content;
            }
            (*height)++;
        }
        temp_content++;
    }
    if (*height > 0 && *width == 0) {
        *width = temp_content - content;
    }
    if (content[temp_content - content - 1] != '\n') {
        (*height)++;
    }
}

char **allocate_map_data(int width, int height) {
    char **data = malloc(height * sizeof(char *));
    if (!data) {
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        data[i] = malloc((width + 1) * sizeof(char));
        if (!data[i]) {
            for (int j = 0; j < i; j++) {
                free(data[j]);
            }
            free(data);
            return NULL;
        }
    }
    return data;
}

void fill_map_data(char **data, const char *content, int height, int width) {
    const char *line_start = content;
    const char *line_end;
    int row = 0;
    while (row < height) {
        line_end = strchr(line_start, '\n');
        if (!line_end) {
            line_end = line_start + strlen(line_start);
        }
        int line_length = line_end - line_start;
        strncpy(data[row], line_start, line_length);
        data[row][line_length] = '\0';
        line_start = line_end + 1;
        row++;
    }
}

bool check_borders(t_map *map) {
    for (int i = 0; i < map->width; i++) {
        if (map->data[0][i] != WALL || map->data[map->height - 1][i] != WALL) {
            return false;
        }
    }
    for (int i = 0; i < map->height; i++) {
        if (map->data[i][0] != WALL || map->data[i][map->width - 1] != WALL) {
            return false;
        }
    }
    return true;
}
