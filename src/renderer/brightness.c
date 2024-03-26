/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:13:46 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/26 14:35:35 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file brightness.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Brightness calculation.
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include <math.h>
#include <stdlib.h>

#include "renderer.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

void	render_get_brightness(
			t_render_unit *runit,
			const t_hit *hit,
			t_color *brightness
			)
{
	*brightness = runit->scene->ambient.color;
	_render_add_diffuse_brightness(runit, hit, brightness);
	_render_add_specular_brightness(runit, hit, brightness);
}

void	_render_add_diffuse_brightness(
			t_render_unit *runit,
			const t_hit *hit,
			t_color *brightness
			)
{
	t_light_simple	**lights;
	float			ratio;
	t_vector3		dir;
	t_color			tmp;

	lights = runit->scene->lights;
	while (*lights != NULL)
	{
		if (!scene_collision(runit->scene, &hit->p, &((*lights)->origin)))
		{
			dir = ((*lights)->origin);
			vec3_normalize(&dir, vec3_sub(&dir, &dir, &hit->p));
			ratio = vec3_dot(&dir, &hit->normal);
			color_mul_scalar(&tmp, &(*lights)->color, ratio);
			color_add(brightness, brightness, &tmp);
		}
		++lights;
	}
}

void	_render_add_specular_brightness(
			t_render_unit *runit,
			const t_hit *hit,
			t_color *brightness
			)
{
	t_light_simple	**lights;
	float			ratio;
	t_vector3		dir;
	t_vector3		v;
	t_color			tmp;

	lights = runit->scene->lights;
	while (*lights != NULL)
	{
		if (!scene_collision(runit->scene, &hit->p, &((*lights)->origin)))
		{
			dir = ((*lights)->origin);
			vec3_normalize(&dir, vec3_sub(&dir, &hit->p, &dir));
			vec3_reflect_by(&dir, &dir, &hit->normal);
			v = runit->center;
			ratio = vec3_dot(&dir, vec3_normalize(&v,
						vec3_sub(&v, &v, &hit->p)));
			if (ratio < 0.)
				ratio = 0.;
			ratio = pow(ratio, 32.f);
			color_mul_scalar(&tmp, &(*lights)->color, ratio);
			color_add(brightness, brightness, &tmp);
		}
		++lights;
	}
}
