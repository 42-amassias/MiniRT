/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:39 by amassias         ###   ########.fr       */
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
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__camera(
			t_scene *scene,
			t_token tokens[]
			)
{
	if (tokens[2].fp < 0.f || tokens[2].fp > 180.f)
		return (false);
	scene->camera.position = tokens[0].position;
	scene->camera.orientation = tokens[1].position;
	scene->camera.fov = M_PI * tokens[2].fp / 180.f;
	return (true);
}
