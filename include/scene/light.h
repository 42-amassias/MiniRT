/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:27:24 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/21 18:33:56 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file light.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Light definition.
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef LIGHT_H
# define LIGHT_H

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

typedef struct s_light_simple
{
	t_point3	origin;
	float		brightness;
	t_color		color;
}	t_light_simple;

typedef struct s_light_ambient
{
	float		ratio;
	t_color		color;
}	t_light_ambient;

#endif
