/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:14:10 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/26 19:53:16 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file renderer.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Renderer definition
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef RENDERER_H
# define RENDERER_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include "scene.h"
# include "graphics/framebuffer.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_render_unit
{
	t_scene			*scene;
	t_point3		pixel00;
	t_vector3		u;
	t_vector3		v;
	t_point3		center;
	t_framebuffer	*fb;
}	t_render_unit;

// ************************************************************************** //
// *                                                                        * //
// * Function definition                                                    * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Renders the `scene` into the `buffer`.
 * @param fb The framebuffer to fill.
 * @param scene The scene to render.
 */
void	render_scene(
			t_scene *scene,
			t_framebuffer *fb
			);

void	render_init(
			t_render_unit *runit,
			t_scene *scene,
			t_framebuffer *fb
			);

void	render_throw_rays(
			t_render_unit *runit
			);

void	render_throw_ray(
			t_render_unit *runit,
			const t_ray *ray,
			t_color *color
			);

void	render_put_color(
			t_render_unit *runit,
			const t_color *color,
			int x,
			int y
			);

void	render_resolve_color(
			t_render_unit *runit,
			const t_hit *hit
			);

void	render_get_brightness(
			t_render_unit *runit,
			const t_hit *hit,
			t_color *brightness
			);

void	_render_add_diffuse_brightness(
			t_render_unit *runit,
			const t_hit *hit,
			t_light_simple *light,
			t_color *brightness
			);

void	_render_add_specular_brightness(
			t_render_unit *runit,
			const t_hit *hit,
			t_light_simple *light,
			t_color *brightness
			);

#endif
