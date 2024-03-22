/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:19:28 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:52:58 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file list_append.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

static size_t	_size(
					void **list
					);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	**list_append(
			void **list,
			void *data
			)
{
	const size_t	size = _size(list);
	void			**new_list;

	new_list = ft_calloc(size + 2, sizeof(void *));
	if (new_list == NULL)
		return (NULL);
	ft_memcpy(new_list, list, size * sizeof(void *));
	new_list[size] = data;
	free(list);
	return (new_list);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static size_t	_size(
					void **list
					)
{
	size_t	i;

	i = 0;
	while (*list++)
		++i;
	return (i);
}
