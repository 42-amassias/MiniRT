/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:03:30 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 13:06:06 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file framebuffer.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Framebuffer functions.
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include "graphics/framebuffer.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

void	fb_put_pixel(t_framebuffer *fb,
			uint32_t color,
			int x,
			int y
			)
{
	char	*dst;

	if (x > fb->line_len || y > fb->height)
		return ;
	dst = fb->data
		+ (y * fb->line_len + x * (fb->bits_per_pixel / 8));
	*((uint32_t *)dst) = color;
}
