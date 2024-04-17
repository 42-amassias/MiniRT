/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:20 by amassias          #+#    #+#             */
/*   Updated: 2024/04/17 19:03:43 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cylinder.c
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
#include "utils.h"

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ORIGIN 0
#define AXIS 1
#define DIAMETER 2
#define HEIGHT 3
#define COLOR 4

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__cylinder(
			t_scene *scene,
			t_token tokens[]
			)
{
	t_object		**objects;
	t_object		*object;

	if (tokens[AXIS].position.x == 0
		&& tokens[AXIS].position.y == 0
		&& tokens[AXIS].position.z == 0)
		return (false);
	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		return (false);
	object->type = OT_CYLINDER;
	object->data.cylinder.origin = tokens[ORIGIN].position;
	object->data.cylinder.axis = tokens[AXIS].position;
	object->data.cylinder.diameter = tokens[DIAMETER].fp;
	object->data.cylinder.height = tokens[HEIGHT].fp;
	object->data.cylinder.color = tokens[COLOR].color;
	vec3_normalize(&object->data.cylinder.axis, &object->data.cylinder.axis);
	objects = (t_object **)list_append((void **)scene->objects, object);
	if (objects == NULL)
		return (free(object), false);
	scene->objects = objects;
	return (true);
}
