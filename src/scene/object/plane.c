/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:34:21 by amassias          #+#    #+#             */
/*   Updated: 2024/03/26 16:01:49 by ale-boud         ###   ########.fr       */
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
	t_object_plane *const	plane = &object->data.plane;
	t_coord					t;
	t_coord					xv;
	t_vector3				x;

	vec3_sub(&x, &ray->origin, &plane->origin);
	xv = vec3_dot(&ray->dir, &plane->normal);
	if (xv == 0.)
		return (0);
	t = -(vec3_dot(&x, &plane->normal)) / xv;
	if (t < NEAR || t > FAR)
		return (0);
	hit_create(hit, ray, &plane->normal, t);
	hit->color = plane->color;
	if (xv > 0.)
		vec3_mul(&hit->normal, &hit->normal, -1);
	return (1);
}

t_color	plane_get_color(
			t_object *object
			)
{
	t_object_plane *const	plane = &object->data.plane;

	return (plane->color);
}
