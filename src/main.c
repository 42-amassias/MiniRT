/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:08:07 by amassias          #+#    #+#             */
/*   Updated: 2024/03/21 19:17:32 by amassias         ###   ########.fr       */
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

#include "scene.h"

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

const char	*g_pn;

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static void				_show_help(
							int fd
							);

noreturn static void	_quit_no_cleanup(
							const char *message,
							int fd,
							int code
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
	t_scene	scene;

	g_pn = *argv;
	if (argc < 2)
		_quit_no_cleanup("Missing scene file.", STDERR_FILENO, 1);
	if (argc > 2)
		_quit_no_cleanup("Too many arguments.", STDERR_FILENO, 1);
	if (load_scene(&scene, argv[1]) == NULL)
		_quit_no_cleanup("", STDERR_FILENO, 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static void	_show_help(
				int fd
				)
{
	dprintf(fd, "Usage: %s [FILE]\n", g_pn);
}

noreturn static void	_quit_no_cleanup(
							const char *message,
							int fd,
							int code
							)
{
	if (*message != '\0')
		dprintf(fd, "%s\n", message);
	_show_help(fd);
	exit(code);
}
