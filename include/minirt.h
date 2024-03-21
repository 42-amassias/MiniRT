/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:18:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/21 18:34:23 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file minirt.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-19
 * @copyright Copyright (c) 2024
 */

#ifndef MINIRT_H
# define MINIRT_H

// ************************************************************************** //
// *                                                                        * //
// * Includes                                                               * //
// *                                                                        * //
// ************************************************************************** //

# include "scene.h"

/* ************************************************************************** */
/*                                                                            */
/* Header prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Renders the `scene` into the `buffer`.
 * @param width The width of the `buffer`.
 * @param height The height of the `buffer`.
 * @param buffer The buffer in which to render.
 * @param scene The scene to render.
 */
void	scene_render(
			unsigned int width,
			unsigned int height,
			char *buffer,
			t_scene *scene
			);

#endif