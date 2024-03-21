/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:18:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/21 17:50:01 by ale-boud         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/* Enums                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_object_type
{
	OT_SPHERE,
	OT_PLANE,
	OT_CYLINDER,
	OT__COUNT
}	t_object_type;

/* ************************************************************************** */
/*                                                                            */
/* Structures - Utilitaries                                                   */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

/* ************************************************************************** */
/*                                                                            */
/* Structures - Objects                                                       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_object_sphere
{
	t_point	origin;
	float	diameter;
	t_color	color;
}	t_object_sphere;

typedef struct s_object_plane
{
	t_point	origin;
	t_point	normal;
	t_color	color;
}	t_object_plane;

typedef struct s_object_cylinder
{
	t_point	origin;
	t_point	axis;
	float	diameter;
	float	height;
	t_color	color;
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

/* ************************************************************************** */
/*                                                                            */
/* Structures - Lights                                                        */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_light_simple
{
	t_point	origin;
	float	brightness;
	t_color	color;
}	t_light_simple;

typedef struct s_light_ambiant
{
	float	ratio;
	t_color	color;
}	t_light_ambiant;

/* ************************************************************************** */
/*                                                                            */
/* Structures - Scene                                                         */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_camera
{
	t_point	position;
	t_point	orientation;
	float	fov;
}	t_camera;

typedef struct s_scene
{
	t_camera		camera;
	t_light_ambiant	ambiant;
	t_light_simple	*lights;
	t_object		*objects;
}	t_scene;

typedef struct s_framebuffer {
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_framebuffer;

/* ************************************************************************** */
/*                                                                            */
/* Header protoypes                                                           */
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