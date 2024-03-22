/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:44 by amassias          #+#    #+#             */
/*   Updated: 2024/03/21 20:42:30 by amassias         ###   ########.fr       */
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

static void	_free(
				void **ptr
				);

static char	**_tokenize(
				char *line
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_scene	*load_scene(
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
		char **tokens = _tokenize(itr->content);
		char **token = tokens;
		while (*token)
			printf("(%s) ", *token++);
		printf("\n");
		_free((void **)tokens);
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
	t_list	*node;

	*lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		node = ft_lstnew(line);
		if (node == NULL)
			return (free(line), ft_lstclear(lines, free), true);
		ft_lstadd_back(lines, node);
		line = get_next_line(fd);
	}
	return (false);
}

static void	_free(
				void **ptr
				)
{
	void	**itr;

	itr = ptr;
	while (*itr)
		free(*itr++);
	free(ptr);
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
			return (_free((void **)tokens), NULL);
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
