/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:26:05 by ale-boud          #+#    #+#             */
/*   Updated: 2024/04/09 15:57:28 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file object.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief 
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef OBJECT_H
# define OBJECT_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include "mathrt.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

typedef enum e_object_type
{
	OT_SPHERE,
	OT_PLANE,
	OT_CYLINDER,
	OT_CONE,
	OT__COUNT
}	t_object_type;

typedef struct s_object_sphere
{
	t_point3	origin;
	t_coord		diameter;
	t_color		color;
}	t_object_sphere;

typedef struct s_object_plane
{
	t_point3	origin;
	t_point3	normal;
	t_color		color;
}	t_object_plane;

typedef struct s_object_cylinder
{
	t_point3	origin;
	t_point3	axis;
	t_coord		diameter;
	t_coord		height;
	t_color		color;
}	t_object_cylinder;

typedef struct s_object_cone
{
	t_point3	origin;
	t_point3	axis;
	t_coord		height;
	t_coord		tang;
	t_color		color;
}	t_object_cone;

typedef struct s_object
{
	union	u_object
	{
		t_object_sphere		sphere;
		t_object_plane		plane;
		t_object_cylinder	cylinder;
		t_object_cone		cone;
	}					data;
	t_object_type		type;
}	t_object;

typedef struct s_object_vt
{
	int		(*hit)(t_object *object, const t_ray *ray, t_hit *hit);
}	t_object_vt;

// ************************************************************************** //
// *                                                                        * //
// * Helper structure                                                       * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_cylinder_vars
{
	t_coord	a;
	t_coord	b;
	t_coord	c;
	t_coord	d;
	t_coord	d_sqrt;
}	t_cylinder_vars;

typedef struct s_cone_vars
{
	t_coord	a;
	t_coord	b;
	t_coord	c;
	t_coord	d;
	t_coord	d_sqrt;
}	t_cone_vars;

// ************************************************************************** //
// *                                                                        * //
// * Sphere functions                                                       * //
// *                                                                        * //
// ************************************************************************** //

int		sphere_hit(
			t_object *object,
			const t_ray *ray,
			t_hit *hit
			);

// ************************************************************************** //
// *                                                                        * //
// * Plane functions                                                        * //
// *                                                                        * //
// ************************************************************************** //

int		plane_hit(
			t_object *object,
			const t_ray *ray,
			t_hit *hit
			);

// ************************************************************************** //
// *                                                                        * //
// * Cylinder functions                                                     * //
// *                                                                        * //
// ************************************************************************** //

int		cylinder_hit(
			t_object *object,
			const t_ray *ray,
			t_hit *hit
			);

// ************************************************************************** //
// *                                                                        * //
// * Cylinder functions                                                     * //
// *                                                                        * //
// ************************************************************************** //

int		cone_hit(
			t_object *object,
			const t_ray *ray,
			t_hit *hit
			);

// ************************************************************************** //
// *                                                                        * //
// * Object virtual table                                                   * //
// *                                                                        * //
// ************************************************************************** //

extern const t_object_vt	g_object_vt[OT__COUNT];

#endif