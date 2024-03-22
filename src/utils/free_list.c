/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:27:29 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 08:28:47 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file free_list.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdlib.h>

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	free_list(
			void **ptr
			)
{
	void	**itr;

	itr = ptr;
	while (*itr)
		free(*itr++);
	free(ptr);
}
