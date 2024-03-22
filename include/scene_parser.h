/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:56:44 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:12 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file scene_parser.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

#ifndef SCENE_PARSER_H
# define SCENE_PARSER_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include "scene.h"

# include <stdbool.h>
# include <stdlib.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

# define MAX_TOKEN_COUNT 16

/* ************************************************************************** */
/*                                                                            */
/* Enums                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_FLOAT,
	TOKEN_COLOR,
	TOKEN_POSITION,
	TOKEN__COUNT
}	t_token_type;

typedef enum e_element_type
{
	ELEMENT_AMBIENT_LIGHT,
	ELEMENT_CAMERA,
	ELEMENT_LIGHT,
	ELEMENT_SPHERE,
	ELEMENT_PLANE,
	ELEMENT_CYLINDER,
	ELEMENT__COUNT,
}	t_element_type;

/* ************************************************************************** */
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

typedef union u_token
{
	float		fp;
	t_color		color;
	t_point3	position;
}	t_token;

typedef bool				(*t_element_acceptor)(t_scene *, t_token[]);

typedef struct s_element_descriptor
{
	const char			*name;
	size_t				associated_tokens_count;
	t_token_type		associated_tokens[MAX_TOKEN_COUNT];
	t_element_acceptor	acceptor;
}	t_element_descriptor;

/* ************************************************************************** */
/*                                                                            */
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

extern t_element_descriptor	g_parsing_table[ELEMENT__COUNT];

/* ************************************************************************** */
/*                                                                            */
/* Acceptors                                                                  */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__ambient_light(
			t_scene *scene,
			t_token tokens[]
			);

bool	element_acceptor__camera(
			t_scene *scene,
			t_token tokens[]
			);

bool	element_acceptor__light(
			t_scene *scene,
			t_token tokens[]
			);

bool	element_acceptor__sphere(
			t_scene *scene,
			t_token tokens[]
			);

bool	element_acceptor__plane(
			t_scene *scene,
			t_token tokens[]
			);

bool	element_acceptor__cylinder(
			t_scene *scene,
			t_token tokens[]
			);

/* ************************************************************************** */
/*                                                                            */
/* Utils                                                                      */
/*                                                                            */
/* ************************************************************************** */

char	*parser_get_float(
			char *str,
			float *value
			);

char	*parser_get_unsigned_char(
			char *str,
			unsigned char *value
			);

char	*parser_color(
			char *str,
			t_color *color
			);

char	*parser_point3(
			char *str,
			t_point3 *point
			);

#endif