/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:34:07 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/13 08:18:09 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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


void hide_exit() {
	if (exit_x != -1 && exit_y != -1) {
		printf("Hiding exit at [%d, %d].\n", exit_x, exit_y); // Debug output
		map->data[exit_y][exit_x] = '0'; // Hide the exit
	}
}

void reveal_map(t_map *map) {
	if (exit_x != -1 && exit_y != -1) {
		printf("Revealing exit at [%d, %d].\n", exit_x, exit_y); // Debug output
		map->data[exit_y][exit_x] = 'E'; // Reveal the exit
	}
}