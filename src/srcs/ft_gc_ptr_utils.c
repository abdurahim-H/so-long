/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_ptr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:40:31 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 21:40:48 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc_internal.h"

void	_insert_managed_ptr(t_ctx *ctx, t_ptr p)
{
	*((t_ptr *)p) = ctx->man;
	ctx->man = p;
}

void	_insert_unmanaged_ptr(t_ctx *ctx, t_unman *unman)
{
	unman->next = ctx->unman;
	ctx->unman = unman;
}

t_ptr	_find_managed_ptr(t_ctx *ctx, t_ptr p)
{
	t_ptr	cur;

	if (p == ctx->man)
		return (p);
	cur = ctx->man;
	if (cur == NULL)
		return (NULL);
	while (*((t_ptr *)cur))
	{
		if (*((t_ptr *)cur) == p)
			return (cur);
		cur = *((t_ptr *)cur);
	}
	return (NULL);
}

t_unman	*_find_unmanaged_ptr(t_ctx *ctx, t_ptr p)
{
	t_unman	*cur;

	if (ctx->unman == NULL || p == ctx->unman->addr)
		return (ctx->unman);
	cur = ctx->unman;
	while (cur->next)
	{
		if (p == cur->next->addr)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
