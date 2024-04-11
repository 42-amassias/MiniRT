/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:12:05 by amassias          #+#    #+#             */
/*   Updated: 2024/04/09 15:53:22 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parsing_table.c
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
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

t_primitive_parser			g_token_parser[TOKEN__COUNT] = {
[TOKEN_FLOAT] = (t_primitive_parser)parser_next_float,
[TOKEN_COLOR] = (t_primitive_parser)parser_next_color,
[TOKEN_POSITION] = (t_primitive_parser)parser_next_point3,
};

t_element_descriptor		g_parsing_table[ELEMENT__COUNT] = {
[ELEMENT_AMBIENT_LIGHT] = {
	.name = "A",
	.associated_tokens_count = 2,
	.associated_tokens = {TOKEN_FLOAT, TOKEN_COLOR},
	.acceptor = element_acceptor__ambient_light,
},
[ELEMENT_CAMERA] = {
	.name = "C",
	.associated_tokens_count = 3,
	.associated_tokens = {TOKEN_POSITION, TOKEN_POSITION, TOKEN_FLOAT},
	.acceptor = element_acceptor__camera,
},
[ELEMENT_LIGHT] = {
	.name = "L",
	.associated_tokens_count = 3,
	.associated_tokens = {TOKEN_POSITION, TOKEN_FLOAT, TOKEN_COLOR},
	.acceptor = element_acceptor__light,
},
[ELEMENT_SPHERE] = {
	.name = "sp",
	.associated_tokens_count = 3,
	.associated_tokens = {TOKEN_POSITION, TOKEN_FLOAT, TOKEN_COLOR},
	.acceptor = element_acceptor__sphere,
},
[ELEMENT_PLANE] = {
	.name = "pl",
	.associated_tokens_count = 3,
	.associated_tokens = {TOKEN_POSITION, TOKEN_POSITION, TOKEN_COLOR},
	.acceptor = element_acceptor__plane,
},
[ELEMENT_CYLINDER] = {
	.name = "cy",
	.associated_tokens_count = 5,
	.associated_tokens = {TOKEN_POSITION, TOKEN_POSITION, TOKEN_FLOAT,
	TOKEN_FLOAT, TOKEN_COLOR},
	.acceptor = element_acceptor__cylinder,
},
[ELEMENT_CONE] = {
	.name = "co",
	.associated_tokens_count = 5,
	.associated_tokens = {TOKEN_POSITION, TOKEN_POSITION, TOKEN_FLOAT,
	TOKEN_FLOAT, TOKEN_COLOR},
	.acceptor = element_acceptor__cone,
},
};
