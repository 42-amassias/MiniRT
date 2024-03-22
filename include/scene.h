/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:25:35 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/22 16:15:09 by ale-boud         ###   ########.fr       */
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
	/**
	 * @brief NULL terminated #s_lights list.
	 */
	t_light_simple	**lights;
	/**
	 * @brief NULL terminated #s_objects list.
	 */
	t_object		**objects;
}	t_scene;

// ************************************************************************** //
// *                                                                        * //
// * Function prototype                                                     * //
// *                                                                        * //
// ************************************************************************** //

/**
 * @brief Loads a scene given a `path`.
 * @param scene A pointer to the scene to build.
 * @param path The path of the file describing the scene.
 * @return `NULL` if an error occured, `scene` otherwise.
 */
t_scene	*scene_load(
			t_scene *scene,
			const char *path
			);

float	scene_hit_brightness(
			const t_scene *scene,
			const t_hit *hit
			);

/**
 * @brief Throw a hit in the scene.
 * @param scene the scene.
 * @param ray Ray to throw.
 * @param hit_info The hit info if there is a hit.
 * @return int != 0 if there is a hit.
 */
int		scene_throw_ray(
			t_scene *scene,
			const t_ray *ray,
			t_hit *hit_info);

int		scene_collision(
			t_scene *scene,
			const t_point3 *p1,
			const t_point3 *p2
			);

/**
 * @brief Cleans up all resources allocated to `scene`.
 * @param scene The scene to cleanup.
 */
void	scene_cleanup(
			t_scene *scene
			);

#endif
