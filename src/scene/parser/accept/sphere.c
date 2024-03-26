/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:45 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file sphere.c
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
#define DIAMETER 1
#define COLOR 2

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__sphere(
			t_scene *scene,
			t_token tokens[]
			)
{
	t_object		**objects;
	t_object		*object;

	if (tokens[DIAMETER].fp < 0.f)
		return (false);
	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		return (false);
	object->type = OT_SPHERE;
	object->data.sphere.origin = tokens[ORIGIN].position;
	object->data.sphere.diameter = tokens[DIAMETER].fp;
	object->data.sphere.color = tokens[COLOR].color;
	objects = (t_object **)list_append((void **)scene->objects, object);
	if (objects == NULL)
		return (free(object), false);
	scene->objects = objects;
	return (true);
}
