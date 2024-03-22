/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:23:54 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 09:30:29 by amassias         ###   ########.fr       */
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
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_window_ctx
{
	void			*ctx;
	void			*win;
	t_framebuffer	frame_buffer;
}	t_window_ctx;

/* ************************************************************************** */
/*                                                                            */
/* Header prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

t_window_ctx	*window_initialize(
					t_window_ctx *ctx
					);

void			window_cleanup(
					t_window_ctx *ctx
					);

#endif
