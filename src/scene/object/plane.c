/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:34:21 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 08:36:10 by amassias         ###   ########.fr       */
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

#include "scene/object.h"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	plane_hitten(
		t_object *object,
		const t_ray *ray,
		t_hit *hit
		)
{
	(void)object;
	(void)ray;
	(void)hit;
	return (0);
}

t_color	plane_get_color(
			t_object *object
			)
{
	t_object_plane *const	plane = &object->data.plane;

	return (plane->color);
}
