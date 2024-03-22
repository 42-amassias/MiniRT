/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:25:27 by amassias          #+#    #+#             */
/*   Updated: 2024/03/22 08:55:23 by amassias         ###   ########.fr       */
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
 * @brief Frees all the resources allocated to `ptr`.
 * `ptr` should be a `NULL` terminated array and every one of its cells should
 * have been `malloc`'d. If `ptr` is `NULL`, does nothing.
 * @param ptr The list to free.
 */
void	free_list(
			void **ptr
			);

#endif