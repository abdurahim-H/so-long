/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_ctx_wild_manip.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhudulo <abhudulo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:40:53 by abhudulo          #+#    #+#             */
/*   Updated: 2024/05/31 21:40:55 by abhudulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc_internal.h"

void	ft_gc_ctx_release(t_ctx *ctx, t_ptr p)
{
	ft_gc_ctx_transfer(_get_wild(), ctx, p);
}

void	ft_gc_ctx_release_all(t_ctx *ctx)
{
	ft_gc_ctx_transfer_all(_get_wild(), ctx);
}

void	ft_gc_ctx_obtain_wild(t_ctx *ctx)
{
	ft_gc_ctx_transfer_all(ctx, _get_wild());
}
