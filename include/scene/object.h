/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:26:05 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/21 18:42:43 by ale-boud         ###   ########.fr       */
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

typedef struct s_object
{
	union	u_object
	{
		t_object_sphere		sphere;
		t_object_plane		plane;
		t_object_cylinder	cylinder;
	}					data;
	t_object_type		type;
}	t_object;

typedef struct s_object_vt
{
	int		(*hitten)(t_ray);
	t_color	(*get_color)(t_ray);
}	t_object_vt;

#endif