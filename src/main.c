/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:08:07 by amassias          #+#    #+#             */
/*   Updated: 2024/03/24 12:57:27 by amassias         ###   ########.fr       */
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

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <unistd.h>

#include <math.h>
#include <libft.h>
#include "utils.h"

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

// static t_scene			*_scene_load(
// 							t_scene *scene,
// 							const char *path
// 							);

static bool				_quit_on_q(
							int keycode,
							t_window_ctx *ctx
							);

static bool				_render(
							t_minirt_ctx *ctx
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
	const t_scene	*scene = &ctx.scene;

	g_pn = *argv;
	if (argc < 2)
		_quit_no_cleanup("Missing scene file.", STDERR_FILENO, 1);
	if (argc > 2)
		_quit_no_cleanup("Too many arguments.", STDERR_FILENO, 1);
	if (scene_load(&ctx.scene, argv[1]) == NULL)
	{
		printf("FINISH\n");
		scene_cleanup(&ctx.scene);
		_quit_no_cleanup("", STDERR_FILENO, 1);
	}
	printf("FINISH\n");
	printf("Scene loaded !\n");
	
	printf("CAMERA:\n");
	printf("\t- %-15s %f\n", "fov (rad):", scene->camera.fov);
	printf("\t- %-15s\n", "position:");
	printf("\t\t- %-15s %f\n", "x:", scene->camera.position.x);
	printf("\t\t- %-15s %f\n", "y:", scene->camera.position.y);
	printf("\t\t- %-15s %f\n", "z:", scene->camera.position.z);
	printf("\t- %-15s\n", "orientation:");
	printf("\t\t- %-15s %f\n", "x:", scene->camera.orientation.x);
	printf("\t\t- %-15s %f\n", "y:", scene->camera.orientation.y);
	printf("\t\t- %-15s %f\n", "z:", scene->camera.orientation.z);

	printf("AMBIANT:\n");
	printf("\t- %-15s\n", "color (* ratio):");
	printf("\t\t- %-15s %f\n", "r:", scene->ambient.color.r);
	printf("\t\t- %-15s %f\n", "g:", scene->ambient.color.g);
	printf("\t\t- %-15s %f\n", "b:", scene->ambient.color.b);

	printf("LIGHTS:\n");
	t_light_simple	**light_itr;
	size_t			i;

	light_itr = scene->lights;
	i = 0;
	while (*light_itr)
	{
		printf("\t- %3zu - %-15s\n", i++, "simple light:");
		printf("\t\t- %-15s\n", "origin:");
		printf("\t\t\t- %-15s %f\n", "x:", (*light_itr)->origin.x);
		printf("\t\t\t- %-15s %f\n", "y:", (*light_itr)->origin.y);
		printf("\t\t\t- %-15s %f\n", "z:", (*light_itr)->origin.z);
		printf("\t\t- %-15s\n", "color (* ratio):");
		printf("\t\t\t- %-15s %f\n", "r:", (*light_itr)->color.r);
		printf("\t\t\t- %-15s %f\n", "g:", (*light_itr)->color.g);
		printf("\t\t\t- %-15s %f\n", "b:", (*light_itr)->color.b);
		++light_itr;
	}

	printf("OBJECTS:\n");
	t_object	**object_itr;

	object_itr = scene->objects;
	i = 0;
	while (*object_itr)
	{
		if ((*object_itr)->type == OT_SPHERE)
		{
			printf("\t- %3zu - %-15s\n", i, "shphere:");
			printf("\t\t- %-15s\n", "origin:");
			printf("\t\t\t- %-15s %f\n", "x:", (*object_itr)->data.sphere.origin.x);
			printf("\t\t\t- %-15s %f\n", "y:", (*object_itr)->data.sphere.origin.y);
			printf("\t\t\t- %-15s %f\n", "z:", (*object_itr)->data.sphere.origin.z);
			printf("\t\t- %-15s %f\n", "diameter:", (*object_itr)->data.sphere.diameter);
			printf("\t\t- %-15s\n", "color:");
			printf("\t\t\t- %-15s %f\n", "r:", (*object_itr)->data.sphere.color.r);
			printf("\t\t\t- %-15s %f\n", "g:", (*object_itr)->data.sphere.color.g);
			printf("\t\t\t- %-15s %f\n", "b:", (*object_itr)->data.sphere.color.b);
		}
		else if ((*object_itr)->type == OT_PLANE)
		{
			printf("\t- %3zu - %-15s\n", i, "plane:");
			printf("\t\t- %-15s\n", "origin:");
			printf("\t\t\t- %-15s %f\n", "x:", (*object_itr)->data.plane.origin.x);
			printf("\t\t\t- %-15s %f\n", "y:", (*object_itr)->data.plane.origin.y);
			printf("\t\t\t- %-15s %f\n", "z:", (*object_itr)->data.plane.origin.z);
			printf("\t\t- %-15s\n", "normal:");
			printf("\t\t\t- %-15s %f\n", "x:", (*object_itr)->data.plane.normal.x);
			printf("\t\t\t- %-15s %f\n", "y:", (*object_itr)->data.plane.normal.y);
			printf("\t\t\t- %-15s %f\n", "z:", (*object_itr)->data.plane.normal.z);
			printf("\t\t- %-15s\n", "color:");
			printf("\t\t\t- %-15s %f\n", "r:", (*object_itr)->data.plane.color.r);
			printf("\t\t\t- %-15s %f\n", "g:", (*object_itr)->data.plane.color.g);
			printf("\t\t\t- %-15s %f\n", "b:", (*object_itr)->data.plane.color.b);
		}
		else if ((*object_itr)->type == OT_CYLINDER)
		{
			printf("\t- %3zu - %-15s\n", i, "cylinder:");
			printf("\t\t- %-15s\n", "origin:");
			printf("\t\t\t- %-15s %f\n", "x:", (*object_itr)->data.cylinder.origin.x);
			printf("\t\t\t- %-15s %f\n", "y:", (*object_itr)->data.cylinder.origin.y);
			printf("\t\t\t- %-15s %f\n", "z:", (*object_itr)->data.cylinder.origin.z);
			printf("\t\t- %-15s\n", "axis:");
			printf("\t\t\t- %-15s %f\n", "x:", (*object_itr)->data.cylinder.axis.x);
			printf("\t\t\t- %-15s %f\n", "y:", (*object_itr)->data.cylinder.axis.y);
			printf("\t\t\t- %-15s %f\n", "z:", (*object_itr)->data.cylinder.axis.z);
			printf("\t\t- %-15s %f\n", "diameter:", (*object_itr)->data.cylinder.diameter);
			printf("\t\t- %-15s %f\n", "height:", (*object_itr)->data.cylinder.height);
			printf("\t\t- %-15s\n", "color:");
			printf("\t\t\t- %-15s %f\n", "r:", (*object_itr)->data.cylinder.color.r);
			printf("\t\t\t- %-15s %f\n", "g:", (*object_itr)->data.cylinder.color.g);
			printf("\t\t\t- %-15s %f\n", "b:", (*object_itr)->data.cylinder.color.b);
		}
		++i;
		++object_itr;
	}

	if (window_initialize(&ctx.window) == NULL)
	{
		scene_cleanup(&ctx.scene);
		_quit_no_cleanup("", STDERR_FILENO, 1);
	}
	window_set_key_hook(&ctx.window, (t_key_hook)_quit_on_q, &ctx.window);
	window_set_render_hook(&ctx.window, (t_render_hook)_render, &ctx);
	window_run(&ctx.window);
	scene_cleanup(&ctx.scene);
	window_cleanup(&ctx.window);
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

// static t_scene	*_scene_load(
// 					t_scene *scene,
// 					const char *path
// 					)
// {
// 	(void)path;
// 	scene->camera.fov = M_PI / 2.f;
// 	scene->ambient.color = (t_color){52.f / 255.f, 91.f / 255.f, 235.f / 255.f};
// 	scene->lights = (t_light_simple **)ft_calloc(3, sizeof(t_light_simple *));
// 	if (scene->lights == NULL)
// 		return (NULL);
// 	scene->lights[0] = malloc(sizeof(t_light_simple));
// 	scene->lights[1] = malloc(sizeof(t_light_simple));
// 	if (scene->lights[0] == NULL || scene->lights[1] == NULL)
// 		return (free(scene->lights[0]), free(scene->lights[1]),
// 			free(scene->lights), NULL);
// 	*scene->lights[0] = (t_light_simple){
// 		.color = (t_color){0.f, 0.f, 0.f},
// 		.origin = (t_point3){0.f, 0.f, 0.f}
// 	};
// 	*scene->lights[1] = (t_light_simple){
// 		.color = (t_color){0.f, 0.f, 0.f},
// 		.origin = (t_point3){0.f, 0.f, 0.f}
// 	};
// 	scene->objects = (t_object **)ft_calloc(3, sizeof(t_object *));
// 	if (scene->objects == NULL)
// 		return (free_list((void **)scene->lights), NULL);
// 	scene->objects[0] = malloc(sizeof(t_object));
// 	scene->objects[1] = malloc(sizeof(t_object));
// 	if (scene->objects[0] == NULL || scene->objects[1] == NULL)
// 		return (free(scene->objects[0]), free(scene->objects[1]),
// 			free(scene->objects), free_list((void **)scene->lights), NULL);
// 	*scene->objects[0] = (t_object){
// 		.type = OT_SPHERE,
// 		.data.sphere = (t_object_sphere){
// 		.color = (t_color){0.f, 0.f, 0.f},
// 		.origin = (t_point3){0.f, 0.f, 0.f},
// 		.diameter = 0.f
// 	}};
// 	*scene->objects[1] = (t_object){
// 		.type = OT_SPHERE,
// 		.data.sphere = (t_object_sphere){
// 		.color = (t_color){0.f, 0.f, 0.f},
// 		.origin = (t_point3){0.f, 0.f, 0.f},
// 		.diameter = 0.f
// 	}};
// 	return (scene);
// }

static bool	_quit_on_q(
				int keycode,
				t_window_ctx *ctx
				)
{
	(void)ctx;
	if (keycode == 'q')
		return (true);
	return (false);
}

static bool	_render(
				t_minirt_ctx *ctx
				)
{
	render_scene(&ctx->scene, &ctx->window.frame_buffer);
	return (false);
}
