/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathrt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:10:38 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/26 14:36:50 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file mathrt.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Math utilities.
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef MATHRT_H
# define MATHRT_H

# define FAR 250.0
# define NEAR 0.01

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include <mathrt.h>

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Coordinate type.
 */
typedef float		t_coord;

/**
 * @brief Vector definition.
 */
typedef struct s_vector3
{
	t_coord	x;
	t_coord	y;
	t_coord	z;
}	t_vector3;

typedef t_vector3	t_point3;
typedef t_vector3	t_point3;

/**
 * @brief Color definition.
 */
typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

/**
 * @brief Ray definition.
 */
typedef struct s_ray
{
	t_point3	origin;
	t_vector3	dir;
}	t_ray;

/**
 * @brief Hit definition.
 */
typedef struct s_hit
{
	/**
	 * @brief Hit position.
	 */
	t_point3	p;
	t_vector3	normal;
	t_vector3	from_dir;
	t_color		color;
	/**
	 * @brief Ray len between origin and the hit.
	 */
	t_coord		t;
}	t_hit;

// ************************************************************************** //
// *                                                                        * //
// * Vector function prototypes                                             * //
// *                                                                        * //
// ************************************************************************** //

t_coord		vec3_dot(
				const t_vector3 *v1,
				const t_vector3 *v2
				);

t_vector3	*vec3_cross(
				t_vector3 *r,
				const t_vector3 *v1,
				const t_vector3 *v2
				);

t_vector3	*vec3_add(
				t_vector3 *r,
				const t_vector3 *v1,
				const t_vector3 *v2
				);

t_vector3	*vec3_mul(
				t_vector3 *r,
				const t_vector3 *v,
				t_coord scale
				);

t_vector3	*vec3_div(
				t_vector3 *r,
				const t_vector3 *v,
				t_coord n
				);

t_vector3	*vec3_sub(
				t_vector3 *r,
				const t_vector3 *v1,
				const t_vector3 *v2
				);

t_vector3	*vec3_normalize(
				t_vector3 *r,
				const t_vector3 *v
				);

t_coord		vec3_len_squared(
				const t_vector3 *v
				);

t_coord		vec3_len(
				const t_vector3 *v
				);

t_vector3	*vec3_reflect_by(
				t_vector3 *r,
				const t_vector3 *v,
				const t_vector3 *normal
				);

// ************************************************************************** //
// *                                                                        * //
// * Color function definition                                              * //
// *                                                                        * //
// ************************************************************************** //

t_color		*color_add(
				t_color *r,
				const t_color *c1,
				const t_color *c2
				);

t_color		*color_mul_scalar(
				t_color *r,
				const t_color *c,
				float scalar
				);

t_color		*color_mul(
				t_color *r,
				const t_color *c1,
				const t_color *c2
				);

// ************************************************************************** //
// *                                                                        * //
// * Hit function definition                                                * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Set the hit structure (set color manually, thank norminette).
 * @param hit The hit
 * @param ray The ray
 * @param normal The normal
 * @param color The color
 * @return the hit
 */
t_hit		*hit_create(
				t_hit *hit,
				const t_ray *ray,
				const t_vector3 *normal,
				t_coord t
				);

// ************************************************************************** //
// *                                                                        * //
// * Ray function definition                                                * //
// *                                                                        * //
// ************************************************************************** //

t_point3	*ray_at(
				const t_ray *ray,
				t_point3 *p,
				t_coord t
				);

#endif
