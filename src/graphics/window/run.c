/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:20:48 by amassias          #+#    #+#             */
/*   Updated: 2024/04/04 02:26:38 by amassias         ###   ########.fr       */
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
				void *_
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
	mlx_loop_hook(ctx->ctx, _loop, NULL);
	mlx_loop(ctx->ctx);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static int	_loop(
				void *_
				)
{
	(void)_;
	return (0);
}

static int	_key_hook_wrapper(
				int keycode,
				t_window_ctx *ctx
				)
{
	const t_key_hook	_key_hook = ctx->__hooks[__HOOK__KEY].fun;

	if (!ctx->__hooks[__HOOK__KEY].fun)
		return (0);
	if (_key_hook(keycode, ctx->__hooks[__HOOK__KEY].ptr))
		mlx_loop_end(ctx->ctx);
	return (0);
}
