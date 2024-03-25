/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:44 by amassias          #+#    #+#             */
/*   Updated: 2024/03/25 10:28:35 by amassias         ###   ########.fr       */
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

/**
 * @brief Reads all the lines of `fd` and registers them in `*lines`.
 * @param fd The file descriptor from which to read the lines.
 * @param lines A pointer to a linked list.
 * @return `true` if an error occured, `false` otherwise.
 */
static bool	_read_lines(
				int fd,
				t_list **lines
				);

static char	**_tokenize(
				char *line
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
	int		fd;
	t_list	*lines;

	scene->objects = (t_object **)ft_calloc(1, sizeof(t_object *));
	if (scene->objects == NULL)
		return (NULL);
	scene->lights = (t_light_simple **)ft_calloc(1, sizeof(t_light_simple *));
	if (scene->lights == NULL)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror("EXEC"), NULL);
	if (_read_lines(fd, &lines))
		return (close(fd), NULL);
	close(fd);
	//-----
	t_list	*itr = lines;
	while (itr)
	{
		char	**tokens = _tokenize(itr->content);
		if (tokens == NULL)
			return (ft_lstclear(&lines, free), NULL);
		if (tokens[0] == NULL)
		{
			free_list((void **)tokens);
			itr = itr->next;
			continue ;
		}
		size_t	i = 0;
		while (i < ELEMENT__COUNT && ft_strcmp(g_parsing_table[i].name, tokens[0]) != 0)
			++i;
		if (i == ELEMENT__COUNT)
		{
			dprintf(STDERR_FILENO, "Unknown element: %s\n", tokens[0]);
			free_list((void **)tokens);
			return (ft_lstclear(&lines, free), NULL);
		}
		// 1. Construct value buffer (iterate over g_parsing_table[i].associated_tokens)
		// 2. If the table indicates that a token should be parsed, goto 3 else goto 8
		// 3. If there is no remaining token on the input, throw error.
		// 4. Parse token using table
		// 5. If not at the end of the token, throw error
		// 6. Accept token.
		// 7. goto 2
		// 8. If there are more tokens, throw error.
		t_token	*token_data = (t_token *)ft_calloc(g_parsing_table[i].associated_tokens_count, sizeof(t_token));
		if (token_data == NULL)
			return (free_list((void **)tokens), ft_lstclear(&lines, free), NULL);
		size_t	j = 0;
		while (j < g_parsing_table[i].associated_tokens_count)
		{
			if (tokens[j + 1] == NULL)
			{
				dprintf(STDERR_FILENO, "Missing token for element %s.\n", tokens[0]);
				return (free(token_data), free_list((void **)tokens), ft_lstclear(&lines, free), NULL);
			}
			char	*end;
			if (g_parsing_table[i].associated_tokens[j] == TOKEN_FLOAT)
				end = parser_get_float(tokens[j + 1], &token_data[j].fp);
			else if (g_parsing_table[i].associated_tokens[j] == TOKEN_COLOR)
				end = parser_color(tokens[j + 1], &token_data[j].color);
			else if (g_parsing_table[i].associated_tokens[j] == TOKEN_POSITION)
				end = parser_point3(tokens[j + 1], &token_data[j].position);
			else
				((void)0, ft_putendl_fd("Unreachable", STDERR_FILENO), exit(1));
			if (end == NULL || *end)
			{
				dprintf(STDERR_FILENO, "%s --> %s\n", tokens[j + 1], end);
				return (free(token_data), free_list((void **)tokens), ft_lstclear(&lines, free), NULL);
			}
			++j;
		}
		if (!g_parsing_table[i].acceptor(scene, token_data))
		{
			dprintf(STDERR_FILENO, "Did not accept: %s\n", (char *)itr->content);
			return (free(token_data), free_list((void **)tokens), ft_lstclear(&lines, free), NULL);
		}
		free(token_data);
		free_list((void **)tokens);
		itr = itr->next;
	}
	//-----
	ft_lstclear(&lines, free);
	return (scene);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static bool	_read_lines(
				int fd,
				t_list **lines
				)
{
	char	*line;
	char	*end;
	t_list	*node;

	*lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		end = ft_strchr(line, '\n');
		if (end)
			*end = '\0';
		node = ft_lstnew(line);
		if (node == NULL)
			return (free(line), ft_lstclear(lines, free), true);
		ft_lstadd_back(lines, node);
		line = get_next_line(fd);
	}
	return (false);
}

static char	**_tokenize(
				char *line
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