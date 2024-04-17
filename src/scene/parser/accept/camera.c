/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:20 by amassias          #+#    #+#             */
/*   Updated: 2024/04/17 19:03:17 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file camera.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define VIEW 0
#define ORIENTATION 1
#define FOV 2

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__camera(
			t_scene *scene,
			t_token tokens[]
			)
{
	if (scene->_has_camera)
		return (false);
	if (tokens[FOV].fp < 0.f || tokens[FOV].fp > 180.f)
		return (false);
	if (tokens[ORIENTATION].position.x == 0
		&& tokens[ORIENTATION].position.y == 0
		&& tokens[ORIENTATION].position.z == 0)
		return (false);
	scene->camera.position = tokens[VIEW].position;
	scene->camera.orientation = tokens[ORIENTATION].position;
	scene->camera.fov = M_PI * tokens[FOV].fp / 180.f;
	vec3_normalize(&scene->camera.orientation, &scene->camera.orientation);
	if (scene->camera.orientation.y == 1 || scene->camera.orientation.y == -1)
	{
		scene->camera.orientation.y *= 0.9999999999999999999999;
		scene->camera.orientation.x = 0.0000000000000000000001;
	}
	scene->_has_camera = true;
	return (true);
}
