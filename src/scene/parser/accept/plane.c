/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:47 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file plane.c
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
#define NORMAL 1
#define COLOR 2

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__plane(
			t_scene *scene,
			t_token tokens[]
			)
{
	t_object		**objects;
	t_object		*object;

	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		return (false);
	object->type = OT_PLANE;
	object->data.plane.origin = tokens[ORIGIN].position;
	object->data.plane.normal = tokens[NORMAL].position;
	object->data.plane.color = tokens[COLOR].color;
	objects = (t_object **)list_append((void **)scene->objects, object);
	if (objects == NULL)
		return (free(object), false);
	scene->objects = objects;
	return (true);
}
