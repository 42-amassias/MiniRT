/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:42 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file light.c
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
#define BRIGHTNESS 1
#define COLOR 2

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__light(
			t_scene *scene,
			t_token tokens[]
			)
{
	t_light_simple	**lights;
	t_light_simple	*light;

	if (tokens[BRIGHTNESS].fp < 0.f || tokens[BRIGHTNESS].fp > 1.f)
		return (false);
	light = (t_light_simple *)malloc(sizeof(t_light_simple));
	if (light == NULL)
		return (false);
	light->origin = tokens[ORIGIN].position;
	light->color.r = tokens[COLOR].color.r * tokens[BRIGHTNESS].fp;
	light->color.g = tokens[COLOR].color.g * tokens[BRIGHTNESS].fp;
	light->color.b = tokens[COLOR].color.b * tokens[BRIGHTNESS].fp;
	lights = (t_light_simple **)list_append((void **)scene->lights, light);
	if (lights == NULL)
		return (free(light), false);
	scene->lights = lights;
	return (true);
}
