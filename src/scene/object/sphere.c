/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:37:49 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/21 20:46:47 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file sphere.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief 
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include <math.h>

#include "mathrt.h"

#include "scene/object.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition                                             * //
// *                                                                        * //
// ************************************************************************** //

static int	_sphere_hitten(
				t_object_sphere *sphere,
				const t_ray *ray,
				t_hit *hit,
				t_coord discriminant
				);

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	sphere_hitten(
		t_object *object,
		const t_ray *ray,
		t_hit *hit
		)
{
	const t_coord	radius = object->data.sphere.diameter / 2.;
	t_vector3		oc;
	t_coord			half_b;
	t_coord			discriminant;
	t_coord			root;

	vec3_sub(&oc, &ray->origin, &object->data.sphere.origin);
	half_b = vec3_dot(&oc, &ray->dir);
	discriminant = half_b * half_b - vec3_len_squared(&ray->dir)
		* (vec3_len_squared(&oc) - radius * radius);
	root = (-half_b - sqrt(discriminant)) / vec3_len_squared(&ray->dir);
	if (root < NEAR)
		root = (-half_b + sqrt(discriminant)) / vec3_len_squared(&ray->dir);
	if (root < NEAR)
		return (0);
	return (_sphere_hitten(&object->data.sphere, ray, hit, root));
}

t_color	sphere_get_color(
			t_object *object
			)
{
	t_object_sphere *const	sphere = &object->data.sphere;

	return (sphere->color);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //

static int	_sphere_hitten(
				t_object_sphere *sphere,
				const t_ray *ray,
				t_hit *hit,
				t_coord root
				)
{
	t_vector3	normal;

	ray_at(ray, &normal, root);
	vec3_normalize(vec3_sub(&normal, &normal, &sphere->origin), &normal);
	hit_create(hit, ray, &normal, root);
	hit->color = sphere->color;
	return (1);
}
