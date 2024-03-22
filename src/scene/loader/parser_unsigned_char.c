/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_unsigned_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:07:35 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 16:25:16 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_unsigned_char.c
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

#include <stdbool.h>
#include <libft.h>

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

char	*parser_get_unsigned_char(
			char *str,
			unsigned char *v
			)
{
	int	_v;

	_v = 0;
	if (!ft_isdigit(*str))
		return (NULL);
	while (ft_isdigit(*str))
	{
		_v = 10 * _v + *str++ - '0';
		if (_v > 255)
			return (NULL);
	}
	*v = (unsigned char) _v;
	return (str);
}
