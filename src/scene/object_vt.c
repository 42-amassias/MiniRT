/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_vt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:38:12 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/21 19:40:58 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file object_vt.c
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Object virtual table declaration.
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

#include "scene/object.h"

// ************************************************************************** //
// *                                                                        * //
// * Object virtual table                                                   * //
// *                                                                        * //
// ************************************************************************** //

const t_object_vt	g_object_vt[OT__COUNT] = {
[OT_SPHERE] = {sphere_hit, sphere_get_color},
[OT_PLANE] = {plane_hit, plane_get_color},
[OT_CYLINDER] = {cylinder_hit, cylinder_get_color},
};
