/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:10:38 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/21 18:22:44 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file math.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Math utilitaries.
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef MATH_H
# define MATH_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //



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

// ************************************************************************** //
// *                                                                        * //
// * Function prototypes                                                    * //
// *                                                                        * //
// ************************************************************************** //



#endif
