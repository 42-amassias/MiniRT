/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:34 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ambiant.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define RATIO 0
#define COLOR 1

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	element_acceptor__ambient_light(
			t_scene *scene,
			t_token tokens[]
			)
{
	scene->ambient.color.r = tokens[COLOR].color.r * tokens[RATIO].fp;
	scene->ambient.color.g = tokens[COLOR].color.g * tokens[RATIO].fp;
	scene->ambient.color.b = tokens[COLOR].color.b * tokens[RATIO].fp;
	return (true);
}
