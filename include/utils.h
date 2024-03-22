/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:25:27 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 17:25:58 by amassias         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/* Header prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

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

#endif