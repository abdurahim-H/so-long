/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:34:07 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/14 20:06:09 by abhudulo         ###   ########.fr       */
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

// void hide_exit(GameContext *context) {
//     if (context->exit_x != -1 && context->exit_y != -1) {
//         printf("Hiding exit at [%d, %d].\n", context->exit_x, context->exit_y);
//         context->map->data[context->exit_y][context->exit_x] = '0';  // Hide the exit
//         render_map(context->mlx, context->map, &context->sprites);  // Update map visuals
//     }
// }

// void reveal_map(GameContext *context) {
//     if (context->exit_x != -1 && context->exit_y != -1) {
//         printf("Revealing exit at [%d, %d].\n", context->exit_x, context->exit_y);
//         context->map->data[context->exit_y][context->exit_x] = 'E';  // Reveal the exit
//         render_map(context->mlx, context->map, &context->sprites);  // Update map visuals
//     }
// }


void game_loop(mlx_t* mlx, GameContext *context) {
    // Set the hook to `ft_hook` with the context
    mlx_loop_hook(mlx, ft_hook, context);

    // Start the event loop
    mlx_loop(mlx);

    // After the loop is exited
    mlx_terminate(mlx);
}