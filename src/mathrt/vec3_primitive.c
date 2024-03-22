/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:55:18 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 11:34:13 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vec3_primitive.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Vector 3 primitive function.
 * @date 2024-03-21
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

t_vector3	*vec3_add(
				t_vector3 *r,
				const t_vector3 *v1,
				const t_vector3 *v2
				)
{
	r->x = v1->x + v2->x;
	r->y = v1->y + v2->y;
	r->z = v1->z + v2->z;
	return (r);
}

t_vector3	*vec3_mul(
				t_vector3 *r,
				const t_vector3 *v,
				t_coord scale
				)
{
	r->x = v->x * scale;
	r->y = v->y * scale;
	r->z = v->z * scale;
	return (r);
}

t_vector3	*vec3_div(
				t_vector3 *r,
				const t_vector3 *v,
				t_coord n
				)
{
	r->x = v->x / n;
	r->y = v->y / n;
	r->z = v->z / n;
	return (r);
}

t_vector3	*vec3_sub(
				t_vector3 *r,
				const t_vector3 *v1,
				const t_vector3 *v2
				)
{
	r->x = v1->x - v2->x;
	r->y = v1->y - v2->y;
	r->z = v1->z - v2->z;
	return (r);
}
