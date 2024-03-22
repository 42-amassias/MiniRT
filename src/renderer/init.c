/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:16:57 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 11:49:17 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Renderer init function.
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include <math.h>

#include "renderer.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

void	render_init(
			t_render_unit *runit,
			t_scene *scene,
			t_framebuffer *fb
			)
{
	const float		vh = 2 * tan(scene->camera.fov);
	const float		vw = vh * (fb->line_len / fb->height);
	const t_vector3	w = scene->camera.orientation;
	t_vector3		vu;
	t_vector3		vv;

	runit->fb = fb;
	runit->scene = scene;
	runit->center = scene->camera.position;
	runit->u = (t_vector3){0, 1, 0};
	vec3_normalize(&runit->u, vec3_cross(&runit->u, &runit->u, &w));
	vec3_normalize(&runit->v, vec3_cross(&runit->v, &w, &runit->u));
	vec3_mul(&vu, &runit->u, vw);
	vec3_mul(&vv, &runit->v, vh);
	vec3_div(&runit->u, &vu, fb->line_len);
	vec3_div(&runit->v, &vv, fb->height);
	vec3_div(&vu, &runit->u, 2.0);
	vec3_div(&vv, &runit->v, 2.0);
	vec3_add(&vu, &vu, &vv);
	vec3_add(&runit->pixel00, &scene->camera.position, &w);
	vec3_sub(&runit->pixel00, &runit->pixel00, &vu);
}
