/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_helper_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:07:03 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:56 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

void	calculate_map_dimensions(const char *content, int *width, int *height)
{
	const char	*temp_content;

	temp_content = content;
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

ssize_t	read_file_content_into_buffer(int fd, char *buffer,
	struct stat *statbuf)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, statbuf->st_size);
	if (bytes_read == -1)
	{
		perror("Failed to read file content");
		close(fd);
	}
	return (bytes_read);
}

int	open_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
	}
	return (fd);
}

int	get_file_statistics(int fd, struct stat *statbuf)
{
	if (fstat(fd, statbuf) == -1)
	{
		perror("Failed to get file statistics");
		close(fd);
		return (-1);
	}
	return (0);
}

char	*read_file_content(const char *file_path)
{
	int				fd;
	struct stat		statbuf;
	char			*buffer;
	ssize_t			bytes_read;

	fd = open_file(file_path);
	if (fd == -1)
		return (NULL);
	if (get_file_statistics(fd, &statbuf) == -1)
		return (NULL);
	buffer = allocate_buffer(fd, &statbuf);
	if (!buffer)
		return (NULL);
	bytes_read = read_file_content_into_buffer(fd, buffer, &statbuf);
	if (bytes_read == -1)
		return (NULL);
	buffer[bytes_read] = '\0';
	close(fd);
	return (buffer);
}
