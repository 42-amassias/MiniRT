/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:44 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 18:06:33 by amassias         ###   ########.fr       */
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
		char	*token;

		(void)token;
		size_t	i = ELEMENT__COUNT;
		while (i--)
		{
			if (ft_strcmp(g_parsing_table[i].name, tokens[i]))
				continue ;
			// 1. Construct value buffer (iterate over g_parsing_table[i].associated_tokens)
			// 2. If the table indicates that a token should be parsed, goto 3 else goto 8
			// 3. If there is no remaining token on the input, throw error.
			// 4. Parse token using table
			// 5. If not at the end of the token, throw error
			// 6. Accept token.
			// 7. goto 2
			// 8. If there are more tokens, throw error.
			break ;
		}

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
	itr = tokens;
	if (tokens == NULL || tokens[0] == NULL)
		return (tokens);
	while (itr[1] != NULL)
	{
		if (ft_strchr(itr[0], '\0')[-1] != ',' && itr[1][0] != ',' && ++itr)
			continue ;
		tmp = ft_strjoin(itr[0], itr[1]);
		if (tmp == NULL)
			return (free_list((void **)tokens), NULL);
		(free(itr[0]), itr2 = itr);
		while (itr2[1])
		{
			itr2[0] = itr2[1];
			++itr2;
		}
		((void)(0), itr2[0] = NULL, itr[0] = tmp);
	}
	return (tokens);
}
