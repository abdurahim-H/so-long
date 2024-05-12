/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:34:07 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/08 07:45:55 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	check_boundaries(int new_x, int new_y)
// {
// 	return (new_x >= 0 && new_x < (int)((35 * map->width) - image->width) &&
// 			new_y >= 0 && new_y < (int)((85 * map->height) - image->height) &&
// 			map->data[new_y / 20][new_x / 20] != '1');
// }

void	enqueue(t_node **head, int x, int y)
{
	t_node		*new_node;
	t_node		*current;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->x = x;
	new_node->y = y;
	new_node -> next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current -> next != NULL)
			current = current -> next;
		current->next = new_node;
	}
}

bool	dequeue(t_node **head, int *x, int *y)
{
	t_node		*temp;

	if (*head == NULL)
		return (false);
	temp = *head;
	*x = temp -> x;
	*y = temp -> y;
	*head = temp -> next;
	free(temp);
	return (true);
}