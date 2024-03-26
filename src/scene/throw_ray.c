/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:51:08 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/26 19:57:35 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file throw_ray.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Throw ray in the scene.
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include <stdlib.h>

#include "scene.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

int	scene_throw_ray(
		t_scene *scene,
		const t_ray *ray,
		t_hit *hit_info)
{
	t_object	**obj;
	t_hit		tmp_hit;
	t_coord		min;
	int			r;

	min = FAR;
	r = 0;
	obj = scene->objects;
	while (*obj != NULL)
	{
		if (g_object_vt[(*obj)->type].hit(*obj, ray, &tmp_hit))
		{
			r = 1;
			if (tmp_hit.t < min)
			{
				*hit_info = tmp_hit;
				min = tmp_hit.t;
			}
		}
		++obj;
	}
	return (r);
}

int	scene_collision(
		t_scene *scene,
		const t_point3 *p1,
		const t_point3 *p2
		)
{
	t_object	**obj;
	t_hit		tmp_hit;
	t_coord		dist;
	t_ray		ray;

	ray.origin = *p1;
	ray.dir = *p2;
	vec3_sub(&ray.dir, &ray.dir, p1);
	dist = vec3_len(&ray.dir);
	vec3_normalize(&ray.dir, &ray.dir);
	obj = scene->objects;
	while (*obj != NULL)
	{
		if (g_object_vt[(*obj)->type].hit(*obj, &ray, &tmp_hit)
			&& tmp_hit.t < dist)
			return (1);
		++obj;
	}
	return (0);
}
