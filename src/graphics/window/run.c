/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:20:48 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:23 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file run.c
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
#include <stdio.h>

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static int	_loop(
				t_window_ctx *ctx
				);

static int	_key_hook_wrapper(
				int keycode,
				t_window_ctx *ctx
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	window_run(
			t_window_ctx *ctx
			)
{
	mlx_key_hook(ctx->win, _key_hook_wrapper, ctx);
	mlx_loop_hook(ctx->ctx, _loop, ctx);
	mlx_loop(ctx->ctx);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static int	_loop(
				t_window_ctx *ctx
				)
{
	bool (*const _update)(void *) = ctx->__hooks[__HOOK__UPDATE].fun;
	bool (*const _render)(void *) = ctx->__hooks[__HOOK__RENDER].fun;
	if (ctx->__hooks[__HOOK__UPDATE].fun)
		if (_update(ctx->__hooks[__HOOK__UPDATE].ptr))
			mlx_loop_end(ctx->ctx);
	if (ctx->__hooks[__HOOK__RENDER].fun)
		if (_render(ctx->__hooks[__HOOK__RENDER].ptr))
			mlx_loop_end(ctx->ctx);
	mlx_put_image_to_window(ctx->ctx, ctx->win, ctx->frame_buffer.img, 0, 0);
	return (0);
}

static int	_key_hook_wrapper(
				int keycode,
				t_window_ctx *ctx
				)
{
	const t_key_hook	_key_hook = ctx->__hooks[__HOOK__KEY].fun;

	if (ctx->__hooks[__HOOK__KEY].fun)
		if (_key_hook(keycode, ctx->__hooks[__HOOK__KEY].ptr))
			mlx_loop_end(ctx->ctx);
	return (0);
}
