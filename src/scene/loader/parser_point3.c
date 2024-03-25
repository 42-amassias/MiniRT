/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_point3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:47:44 by amassias          #+#    #+#             */
/*   Updated: 2024/03/24 12:06:16 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_point3.c
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
#include <stdio.h>
#include <unistd.h>
char	*parser_point3(
			char *str,
			t_point3 *point
			)
{
	str = parser_get_float(str, &point->x);
	if (str == NULL || *str++ != ',')
		return (NULL);
	str = parser_get_float(str, &point->y);
	if (str == NULL || *str++ != ',')
		return (NULL);
	return (parser_get_float(str, &point->z));
}