/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:25:35 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/21 18:33:50 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file scene.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief Scene definition.
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef SCENE_H
# define SCENE_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include "mathrt.h"

# include "scene/object.h"
# include "scene/light.h"
# include "scene/camera.h"

// ************************************************************************** //
// *                                                                        * //
// * Structure definiton                                                    * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_scene
{
	t_camera		camera;
	t_light_ambient	ambient;
	t_light_simple	*lights;
	t_object		*objects;
}	t_scene;

#endif
