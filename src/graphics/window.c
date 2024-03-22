/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:12:10 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 11:24:40 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file window.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/window.h"

#include <mlx.h>
#include <stdlib.h>

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_window_ctx	*window_initialize(
					t_window_ctx *ctx
					)
{
	ctx->ctx = mlx_init();
	if (ctx->ctx == NULL)
		return (window_cleanup(ctx), NULL);
	ctx->win = mlx_new_window(ctx->ctx,
			WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT,
			WINDOW_DEFAULT_TITLE);
	if (ctx->win == NULL)
		return (window_cleanup(ctx), NULL);
	ctx->frame_buffer.img = mlx_new_image(ctx->ctx,
			WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
	if (ctx->frame_buffer.img == NULL)
		return (window_cleanup(ctx), NULL);
	ctx->frame_buffer.data = mlx_get_data_addr(ctx->frame_buffer.img,
			&ctx->frame_buffer.bits_per_pixel,
			&ctx->frame_buffer.line_len,
			&ctx->frame_buffer.endian);
	return (ctx);
}

void	window_cleanup(
			t_window_ctx *ctx
			)
{
	if (ctx->ctx == NULL)
		return ;
	if (ctx->win)
	{
		if (ctx->frame_buffer.img)
			mlx_destroy_image(ctx->ctx, ctx->frame_buffer.img);
		mlx_destroy_window(ctx->ctx, ctx->ctx);
	}
	mlx_destroy_display(ctx->ctx);
	free(ctx->ctx);
}
