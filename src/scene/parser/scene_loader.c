/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:44 by amassias          #+#    #+#             */
/*   Updated: 2024/04/11 16:04:22 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file scene_loader.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "mathrt.h"
#include "scene.h"
#include "utils.h"
#include "scene_parser.h"

#include <fcntl.h>
#include <libft.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ERR_MSG_LIGHT "Scene is missing an ambiant light.\n"
#define ERR_MSG_CAMERA "Scene is missing a camera.\n"
#define ERR_MSG_MISSING_TOK "Missing token for element %s.\n"
#define ERR_MSG_UNKNOWN_ELEM "Unknown element: %s\n"
#define ERR_MSG_PARSING "Could not finish parsing for line: %s\n"
#define ERR_MSG_ACCEPT "Did not accept: %s\n"
#define ERR_MSG_UNEXPECTED_VALUE "Unexpected value for a token %s: %s\n"
#define ERR_MSG_UNEXPECTED_TOK "Unexpected token: %s\n"

/* ************************************************************************** */
/*                                                                            */
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

size_t	g_current_line;

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static char					**_tokenize(
								const char *line
								);

static t_element_descriptor	*_get_element_descripror(
								const char *id
								);

static bool					_parse_associated_tokens(
								t_element_descriptor *element_descriptor,
								t_token *token_data,
								char **tokens
								);

static bool					_parse_line(
								t_scene *scene,
								const char *line
								);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_scene	*scene_load(
			t_scene *scene,
			const char *path
			)
{
	int						fd;
	t_list					*lines;
	t_list					*itr;

	scene->objects = (t_object **)ft_calloc(1, sizeof(t_object *));
	scene->lights = (t_light_simple **)ft_calloc(1, sizeof(t_light_simple *));
	if (scene->objects == NULL || scene->lights == NULL)
		return (free(scene->objects), free(scene->lights), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror(path), NULL);
	if (read_lines_from_fd(fd, &lines))
		return (close(fd), NULL);
	(close(fd), itr = lines);
	while (itr)
	{
		if (_parse_line(scene, (const char *)itr->content))
			return (ft_lstclear(&lines, free), NULL);
		itr = itr->next;
	}
	if (!scene->_has_ambiant)
		(log_msg(LOG_ERR, ERR_MSG_LIGHT), scene = NULL);
	if (scene && !scene->_has_camera)
		(log_msg(LOG_ERR, ERR_MSG_CAMERA), scene = NULL);
	return (ft_lstclear(&lines, free), scene);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static char	**_tokenize(
				const char *line
				)
{
	char	**tokens;
	char	**itr;
	char	**itr2;
	char	*tmp;

	tokens = ft_split(line, ' ');
	if (tokens == NULL || tokens[0] == NULL)
		return (tokens);
	itr = tokens;
	while (itr[1] != NULL)
	{
		if (ft_strchr(itr[0], '\0')[-1] != ',' && itr[1][0] != ',' && ++itr)
			continue ;
		tmp = ft_strjoin(itr[0], itr[1]);
		if (tmp == NULL)
			return (free_list((void **)tokens), NULL);
		(free(itr[0]), free(itr[1]), itr2 = itr + 2);
		while (*itr2)
		{
			itr2[-1] = *itr2;
			++itr2;
		}
		((void)(0), itr2[-1] = NULL, itr[0] = tmp);
	}
	return (tokens);
}

static t_element_descriptor	*_get_element_descripror(
								const char *id
								)
{
	size_t	i;

	i = 0;
	while (i < ELEMENT__COUNT)
		if (ft_strcmp(g_parsing_table[i++].name, id) == 0)
			return (&g_parsing_table[i - 1]);
	return (NULL);
}

static bool	_parse_associated_tokens(
				t_element_descriptor *element_descriptor,
				t_token *token_data,
				char **tokens
				)
{
	const char			*element_name = tokens[0];
	const char			*end;
	size_t				j;
	t_token_type		token_type;

	j = 0;
	while (j < element_descriptor->associated_tokens_count)
	{
		if (tokens[j + 1] == NULL)
			return (log_msg(LOG_ERR, ERR_MSG_MISSING_TOK, element_name), true);
		token_type = element_descriptor->associated_tokens[j++];
		end = g_token_parser[token_type](tokens[j], &token_data[j - 1]);
		if (end == NULL || (*end && *end != '#'))
			return (log_msg(LOG_ERR, ERR_MSG_UNEXPECTED_VALUE,
					g_token_name[token_type], tokens[j]), true);
	}
	if (tokens[j + 1] == NULL || tokens[j + 1][0] == '#')
		return (false);
	return (log_msg(LOG_ERR, ERR_MSG_UNEXPECTED_TOK,
			tokens[j + 1]), true);
}

static bool	_parse_line(
				t_scene *scene,
				const char *line
				)
{
	char					**tokens;
	t_element_descriptor	*element_descriptor;
	t_token					token_data[MAX_TOKEN_COUNT];

	tokens = _tokenize(line);
	if (tokens == NULL || tokens[0] == NULL || tokens[0][0] == '#')
		return (free_list((void **)tokens), tokens == NULL);
	element_descriptor = _get_element_descripror(tokens[0]);
	if (element_descriptor == NULL)
		return (log_msg(LOG_ERR, ERR_MSG_UNKNOWN_ELEM, tokens[0]),
			free_list((void **)tokens), true);
	if (_parse_associated_tokens(element_descriptor, token_data, tokens))
		return (log_msg(LOG_ERR, ERR_MSG_PARSING, line),
			free_list((void **)tokens), true);
	if (!element_descriptor->acceptor(scene, token_data))
		return (log_msg(LOG_ERR, ERR_MSG_ACCEPT, line),
			free_list((void **)tokens), true);
	return (free_list((void **)tokens), false);
}
