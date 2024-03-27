/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:25:27 by amassias          #+#    #+#             */
/*   Updated: 2024/03/27 11:51:13 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

#ifndef UTILS_H
# define UTILS_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include "utils/dynamic_array.h"

# include <libft.h>
# include <stdbool.h>

/* ************************************************************************** */
/*                                                                            */
/* Enums                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_log_type
{
	LOG_MSG,
	LOG_ERR,
}	t_log_type;

/* ************************************************************************** */
/*                                                                            */
/* Header prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Reads all the lines of `fd` and registers them in `*lines`.
 * @param fd The file descriptor from which to read the lines.
 * @param lines A pointer to a linked list.
 * @return `true` if an error occured, `false` otherwise.
 */
bool	read_lines_from_fd(
			int fd,
			t_list **lines
			);

/**
 * @brief Appends `data` to `list`.
 * @param list A list.
 * @param data The element to append.
 * @return The newly allocated list or NULL it an allocation failed.
 */
void	**list_append(
			void **list,
			void *data
			);

/**
 * @brief Frees all the resources allocated to `ptr`.
 * `ptr` should be a `NULL` terminated array and every one of its cells should
 * have been `malloc`'d. If `ptr` is `NULL`, does nothing.
 * @param ptr The list to free.
 */
void	free_list(
			void **ptr
			);

void	log_msg(
			t_log_type type,
			const char *msg,
			...
			);

#endif