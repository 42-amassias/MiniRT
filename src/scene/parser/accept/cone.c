/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:03:24 by ale-boud          #+#    #+#             */
/*   Updated: 2024/04/09 15:51:43 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cone.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @date 2024-04-09
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
#define HEIGHT 2
#define TANG 3
#define COLOR 4

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__cone(
			t_scene *scene,
			t_token tokens[]
			)
{
	t_object		**objects;
	t_object		*object;

	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		return (false);
	object->type = OT_CONE;
	object->data.cone.origin = tokens[ORIGIN].position;
	object->data.cone.axis = tokens[AXIS].position;
	object->data.cone.height = tokens[HEIGHT].fp;
	object->data.cone.tang = tokens[TANG].fp;
	object->data.cone.color = tokens[COLOR].color;
	vec3_normalize(&object->data.cone.axis, &object->data.cone.axis);
	objects = (t_object **)list_append((void **)scene->objects, object);
	if (objects == NULL)
		return (free(object), false);
	scene->objects = objects;
	return (true);
}
