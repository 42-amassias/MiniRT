/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:08:07 by amassias          #+#    #+#             */
/*   Updated: 2024/04/04 02:08:41 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "renderer.h"
#include "utils.h"

#include <libft.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <unistd.h>
#include <X11/keysym.h>

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static void				_show_help(
							int fd,
							const char *pn
							);

noreturn static void	_quit_no_cleanup(
							const char *pn,
							const char *message,
							int fd,
							int code
							);

static bool				_handle_keys(
							int keycode,
							t_window_ctx *ctx
							);

/* ************************************************************************** */
/*                                                                            */
/* Main                                                                       */
/*                                                                            */
/* ************************************************************************** */

int	main(
		int argc,
		char **argv
		)
{
	static t_minirt_ctx	ctx = {0};

	if (argc < 2)
		_quit_no_cleanup(argv[0], "Missing scene file.", STDERR_FILENO, 1);
	if (argc > 2)
		_quit_no_cleanup(argv[0], "Too many arguments.", STDERR_FILENO, 1);
	if (scene_load(&ctx.scene, argv[1]) == NULL
		|| window_initialize(&ctx.window) == NULL)
		return (scene_cleanup(&ctx.scene), EXIT_FAILURE);
	window_set_key_hook(&ctx.window, (t_key_hook)_handle_keys, &ctx.window);
	render_scene(&ctx.scene, &ctx.window.frame_buffer);
	scene_cleanup(&ctx.scene);
	window_run(&ctx.window);
	window_cleanup(&ctx.window);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static void	_show_help(
				int fd,
				const char *pn
				)
{
	dprintf(fd, "Usage: %s [FILE]\n", pn);
}

noreturn static void	_quit_no_cleanup(
							const char *pn,
							const char *message,
							int fd,
							int code
							)
{
	if (*message != '\0')
		dprintf(fd, "%s\n", message);
	_show_help(fd, pn);
	exit(code);
}

static bool	_handle_keys(
				int keycode,
				t_window_ctx *ctx
				)
{
	(void)ctx;
	if (keycode == XK_q || keycode == XK_Escape)
		return (true);
	return (false);
}
