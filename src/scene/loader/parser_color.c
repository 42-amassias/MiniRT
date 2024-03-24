/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:47:44 by amassias          #+#    #+#             */
/*   Updated: 2024/03/24 11:57:29 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_color.c
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
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

char	*parser_color(
			char *str,
			t_color *color
			)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	str = parser_get_unsigned_char(str, &r);
	if (str == NULL || *str++ != ',')
		return (NULL);
	str = parser_get_unsigned_char(str, &g);
	if (str == NULL || *str++ != ',')
		return (NULL);
	str = parser_get_unsigned_char(str, &b);
	if (str == NULL)
		return (NULL);
	color->r = (float)r / 255.f;
	color->g = (float)g / 255.f;
	color->b = (float)b / 255.f;
	return (str);
}
