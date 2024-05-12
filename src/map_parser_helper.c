/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:31:31 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:47:07 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *read_file_content(const char *file_path)
{
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
    if (buffer == NULL) {
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
    buffer[bytes_read] = '\0'; // null-terminate the string
    close(fd);
    return buffer;
}


void	calculate_map_dimensions(const char *content, int *width, int *height)
{
	const char				*temp_content = content;

	*height = 0;
	*width = 0;
	while (*temp_content)
	{
		if (*temp_content == '\n')
		{
			if (*height == 0)
				*width = temp_content - content;
			(*height)++;
		}
		temp_content++;
	}
	if (*height > 0 && *width == 0)
		*width = temp_content - content;
	if (content[temp_content - content - 1] != '\n')
		(*height)++;

}

char **allocate_map_data(int width, int height)
{
	char **data = malloc(height * sizeof(char *));
	if (data == NULL)
		return NULL;

	int i = 0;
	while (i < height) {
		data[i] = malloc((width + 1) * sizeof(char));
		if (data[i] == NULL) {
			while (--i >= 0) // free any previously allocated rows
				free(data[i]);
			free(data);
			return NULL;
		}
		i++;
	}
	return data;
}

void	fill_map_data(char **data, const char *content, int height, int width)
{
	const char			*line_start;
	const char			*line_end;
	int					line_length;
	int					row;

	(void)width;
	line_start = content;
	row = 0;
	while (row < height)
	{
		line_end = strchr(line_start, '\n');
		if (line_end == NULL)
			line_end = line_start + strlen(line_start);
		line_length = line_end - line_start;
		strncpy(data[row], line_start, line_length);
		data[row][line_length] = '\0';
		line_start = line_end + 1;
		row++;
	}
}


bool	check_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->data[0][i] != '1' || map->data[map->height - 1][i] != '1')
			return (false);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->data[i][0] != '1' || map->data[i][map->width - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}