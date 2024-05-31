/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:36:13 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:39 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../inc/ft_gc.h"

void enqueue(t_node **head, int x, int y) {
    t_node *new_node = ft_gc_malloc(1, sizeof(t_node));
    if (!new_node) {
        fprintf(stderr, "Failed to allocate memory for new node.\n");
        return;
    }
    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}


bool dequeue(t_node **head, int *x, int *y) {
    if (*head == NULL) {
        return false;
    }
    t_node *temp = *head;
    *x = temp->x;
    *y = temp->y;
    *head = temp->next;
    // No need to free(temp);
    return true;
}

void enqueue_collectible(t_Node **head, t_point point) {
    t_Node *new_node = ft_gc_malloc(1, sizeof(t_Node));
    if (!new_node) {
        fprintf(stderr, "Failed to allocate memory for new node.\n");
        return;
    }
    new_node->point = point;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

bool dequeue_collectible(t_Node **head, t_point *point) {
    if (*head == NULL) {
        return false;
    }
    t_Node *temp = *head;
    *point = temp->point;
    *head = temp->next;
    // No need to free(temp);
    return true;
}