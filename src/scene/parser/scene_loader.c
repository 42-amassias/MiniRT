/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:44 by amassias          #+#    #+#             */
/*   Updated: 2024/03/26 18:57:44 by amassias         ###   ########.fr       */
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
	if (scene->objects == NULL)
		return (NULL);
	scene->lights = (t_light_simple **)ft_calloc(1, sizeof(t_light_simple *));
	if (scene->lights == NULL)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror(path), NULL);
	if (read_lines_from_fd(fd, &lines))
		return (close(fd), NULL);
	close(fd);
	itr = lines;
	while (itr)
	{
		if (_parse_line(scene, (const char *)itr->content))
			return (ft_lstclear(&lines, free), NULL);
		itr = itr->next;
	}
	ft_lstclear(&lines, free);
	return (scene);
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
	t_primitive_parser	parser;
	size_t				j;

	j = 0;
	while (j < element_descriptor->associated_tokens_count)
	{
		if (tokens[j + 1] == NULL)
		{
			dprintf(STDERR_FILENO, "Missing token for element %s.\n",
				element_name);
			return (true);
		}
		parser = g_token_parser[element_descriptor->associated_tokens[j]];
		end = parser(tokens[j + 1], &token_data[j]);
		if (end == NULL || *end)
			return (true);
		++j;
	}
	return (false);
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
	if (tokens == NULL)
		return (true);
	if (tokens[0] == NULL)
		return (free_list((void **)tokens), false);
	element_descriptor = _get_element_descripror(tokens[0]);
	if (element_descriptor == NULL)
	{
		dprintf(STDERR_FILENO, "Unknown element: %s\n", tokens[0]);
		return (free_list((void **)tokens), true);
	}
	if (_parse_associated_tokens(element_descriptor, token_data, tokens))
	{
		dprintf(STDERR_FILENO, "Could not finish parsing for line: %s\n", line);
		return (free_list((void **)tokens), true);
	}
	if (!element_descriptor->acceptor(scene, token_data))
	{
		dprintf(STDERR_FILENO, "Did not accept: %s\n", line);
		return (free_list((void **)tokens), true);
	}
	return (free_list((void **)tokens), false);
}
