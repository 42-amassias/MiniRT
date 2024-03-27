/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:49:49 by amassias          #+#    #+#             */
/*   Updated: 2024/03/27 11:55:20 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file log_msg.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-27
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdio.h>
#include <stdarg.h>

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	log_msg(
			t_log_type type,
			const char *msg,
			...
			)
{
	int		fd;
	va_list	list;

	if (type == LOG_MSG)
		fd = STDOUT_FILENO;
	else if (type == LOG_ERR)
		fd = STDOUT_FILENO;
	else
		return ;
	va_start(list, msg);
	vdprintf(fd, msg, list);
	va_end(list);
}
