/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:31:50 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 13:48:37 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file color.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Color resolution function.
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include "graphics/framebuffer.h"

#include "renderer.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

void	render_put_color(
			t_render_unit *runit,
			const t_color *color,
			int x,
			int y
			)
{
	uint32_t	encoded_color;
	int			r;
	int			g;
	int			b;

	r = (int)((float)0xFF * color->r);
	g = (int)((float)0xFF * color->g);
	b = (int)((float)0xFF * color->b);
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	if (r > 0xFF)
		r = 0xFF;
	if (g > 0xFF)
		g = 0xFF;
	if (b > 0xFF)
		b = 0xFF;
	encoded_color = ((b & 0xFF) << 0)
		| ((g & 0xFF) << 8)
		| ((r & 0xFF) << 16)
		| (0xFF << 24);
	fb_put_pixel(runit->fb, encoded_color, x, y);
}
