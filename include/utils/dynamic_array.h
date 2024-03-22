/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:05:07 by amassias          #+#    #+#             */
/*   Updated: 2024/03/21 17:40:05 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file dynamic_array.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>

/* ************************************************************************** */
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

struct	s_dynamic_array
{
	void	*data;
	size_t	nmemb;
	size_t	size;
	size_t	_allocated;
};

/* ************************************************************************** */
/*                                                                            */
/* Types                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_dynamic_array	t_dynamic_array;

/* ************************************************************************** */
/*                                                                            */
/* Header protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Initializes a `dynamic_array`.
 * @param dynamic_array A pointer to a dynamic array.
 * @param element_size The size (in bytes) of a single element.
 * @return `dynamic_array` on success, `NULL` otherwise.
 */
t_dynamic_array	*dynamic_array_initialize(
					t_dynamic_array *dynamic_array,
					size_t element_size
					);

/**
 * @brief Appends `data` to `dynamic_array`.
 * @param dynamic_array A pointer to a dynamic array.
 * @param data A pointer to the element to append to `dynamic_array`.
 * @return `dynamic_array` on success, `NULL` otherwise 
 */
t_dynamic_array	*dynamic_array_append(
					t_dynamic_array *dynamic_array,
					void *data
					);

/**
 * @brief Appends `n` elements of `data_list` to `dynamic_array`.
 * @param dynamic_array A pointer to a dynamic array.
 * @param n The ammount of elements in `data_list` to append to `dynamic_array`.
 * @param data_list A list of elements to append to `dynamic_array`.
 * @return `dynamic_array` on success, `NULL` otherwise 
 */
t_dynamic_array	*dynamic_array_nappend(
					t_dynamic_array *dynamic_array,
					size_t n,
					void **data_list
					);

/**
 * @brief Cleans up `dynamic_array`.
 * @param dynamic_array A pointer to a dynamic array.
 */
void			dynamic_array_cleanup(
					t_dynamic_array *dynamic_array
					);

#endif