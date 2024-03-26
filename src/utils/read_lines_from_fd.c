/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines_from_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:29:05 by amassias          #+#    #+#             */
/*   Updated: 2024/03/26 17:29:49 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file read_lines_from_fd.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-26
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	read_lines_from_fd(
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
