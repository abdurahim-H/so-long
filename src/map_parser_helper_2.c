/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_helper_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:41 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:59 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

char	*allocate_buffer(int fd, struct stat *statbuf)
{
	char	*buffer;

	buffer = ft_gc_malloc(1, statbuf->st_size + 1);
	if (!buffer)
	{
		perror("Failed to allocate memory for file content");
		close(fd);
	}
	return (buffer);
}
