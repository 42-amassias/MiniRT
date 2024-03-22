/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:23:54 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 13:01:02 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file window.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

#ifndef WINDOW_H
# define WINDOW_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include "graphics/framebuffer.h"

# include <stdbool.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

# define WINDOW_DEFAULT_WIDTH 1920
# define WINDOW_DEFAULT_HEIGHT 1080
# define WINDOW_DEFAULT_TITLE "MiniRT"

/* ************************************************************************** */
/*                                                                            */
/* Enums                                                                      */
/*                                                                            */
/* ************************************************************************** */

enum e_hook
{
	__HOOK__KEY,
	__HOOK__UPDATE,
	__HOOK__RENDER,
	__HOOK___COUNT
};

/* ************************************************************************** */
/*                                                                            */
/* Types                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef bool	(*t_update_hook)(void *);
typedef bool	(*t_render_hook)(void *);
typedef bool	(*t_key_hook)(int, void *);

/* ************************************************************************** */
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

struct s__hook_
{
	void	*fun;
	void	*ptr;
};

typedef struct s_window_ctx
{
	void			*ctx;
	void			*win;
	t_framebuffer	frame_buffer;
	struct s__hook_	__hooks[__HOOK___COUNT];
}	t_window_ctx;

/* ************************************************************************** */
/*                                                                            */
/* Header prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

t_window_ctx	*window_initialize(
					t_window_ctx *ctx
					);

void			__window_set_hook(
					t_window_ctx *ctx,
					enum e_hook type,
					void *hook,
					void *ptr
					);

void			window_set_key_hook(
					t_window_ctx *ctx,
					t_key_hook hook,
					void *ptr
					);

void			window_set_update_hook(
					t_window_ctx *ctx,
					t_update_hook hook,
					void *ptr
					);

void			window_set_render_hook(
					t_window_ctx *ctx,
					t_render_hook hook,
					void *ptr
					);

void			window_run(
					t_window_ctx *ctx
					);

void			window_cleanup(
					t_window_ctx *ctx
					);

#endif
