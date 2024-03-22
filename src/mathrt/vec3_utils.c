/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:57:33 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 17:37:16 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vec3_utils.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Vector utilities function.
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

// ************************************************************************** //
// *                                                                        * //
// * Function header                                                        * //
// *                                                                        * //
// ************************************************************************** //

t_coord	vec3_dot(
			const t_vector3 *v1,
			const t_vector3 *v2
			)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector3	*vec3_cross(
				t_vector3 *r,
				const t_vector3 *v1,
				const t_vector3 *v2
				)
{
	*r = (t_vector3){
		v1->y * v2->z - v1->z * v2->y,
		v1->z * v2->x - v1->x * v2->z,
		v1->x * v2->y - v1->y * v2->x,
	};
	return (r);
}

t_coord	vec3_len_squared(
			const t_vector3 *v
			)
{
	return (vec3_dot(v, v));
}

t_coord	vec3_len(
			const t_vector3 *v
			)
{
	return (sqrt(vec3_len_squared(v)));
}

t_vector3	*vec3_reflect_by(
				t_vector3 *r,
				const t_vector3 *v,
				const t_vector3 *normal
				)
{
	t_vector3	tmp;

	vec3_mul(&tmp, normal, 2 * vec3_dot(v, normal));
	return (vec3_sub(r, v, &tmp));
}
