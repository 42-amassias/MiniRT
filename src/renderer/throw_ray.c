/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:48:00 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 13:11:39 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file throw_ray.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Core of the ray tracer.
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include "renderer.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

void	render_throw_rays(
			t_render_unit *runit
			)
{
	int			x;
	int			y;
	t_vector3	v;
	t_ray		ray;
	t_color		color;

	ray.origin = runit->center;
	y = 0;
	while (y < runit->fb->height)
	{
		x = 0;
		while (x < runit->fb->line_len)
		{
			vec3_add(&ray.dir,
				vec3_mul(&ray.dir, &runit->u, x),
				vec3_mul(&v, &runit->v, y));
			vec3_add(&ray.dir, &runit->pixel00, &ray.dir);
			//render_throw_ray(runit, &color);
			//render_put_color(runit, &color, x, y);
			(void)(color);
			fb_put_pixel(runit->fb, 0xFF00FFFF, x, y);
			++x;
		}
		++y;
	}
}

void	render_throw_ray(
			t_render_unit *runit,
			t_color *color
			);
