/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:26:24 by ale-boud          #+#    #+#             */
/*   Updated: 2024/03/21 19:29:42 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file framebuffer.h
 * @author ale-boud (ale-boud@student.42lehavre.fr)
 * @brief 
 * @date 2024-03-21
 * @copyright Copyright (c) 2024
 */

#ifndef FRAMEBUFFER_H
# define FRAMEBUFFER_H

// ************************************************************************** //
// *                                                                        * //
// * Structure definition                                                   * //
// *                                                                        * //
// ************************************************************************** //

typedef struct s_framebuffer
{
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		height;
}	t_framebuffer;

#endif
