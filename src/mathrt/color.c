/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:06:27 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 17:08:44 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file color.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Color function.
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include "mathrt.h"

// ************************************************************************** //
// *                                                                        * //
// * Header function                                                        * //
// *                                                                        * //
// ************************************************************************** //

t_color	*color_add(
			t_color *r,
			const t_color *c1,
			const t_color *c2
			)
{
	*r = (t_color){
		c1->r + c2->r,
		c1->g + c2->g,
		c1->b + c2->b,
	};
	return (r);
}

t_color	*color_mul_scalar(
			t_color *r,
			const t_color *c,
			float scalar
			)
{
	*r = (t_color){
		c->r * scalar,
		c->g * scalar,
		c->b * scalar,
	};
	return (r);
}

t_color	*color_mul(
			t_color *r,
			const t_color *c1,
			const t_color *c2
			)
{
	*r = (t_color){
		c1->r * c2->r,
		c1->g * c2->g,
		c1->b * c2->b,
	};
	return (r);
}
