/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:55:35 by ale-boud          #+#    #+#             */
/*   Updated: 2024/04/11 16:22:31 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cone.c
 * @author Alan Le Bouder (ale-boud@student.42.fr)
 * @date 2024-03-22
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "scene/object.h"

// ************************************************************************** //
// *                                                                        * //
// * Helper function definition                                             * //
// *                                                                        * //
// ************************************************************************** //

static void		_cone_hit_compute(
					t_object_cone *cone,
					const t_ray *ray,
					t_cone_vars *vars
					);

static int		_cone_hit_compute_height(
					t_object_cone *cone,
					const t_ray *ray,
					t_hit *hit,
					t_coord t
					);

static int		_cone_hit_create_hit(
					t_object_cone *cone,
					const t_ray *ray,
					t_hit *hit,
					t_cone_vars *vars
					);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	cone_hit(
		t_object *object,
		const t_ray *ray,
		t_hit *hit
		)
{
	t_object_cone *const	cone = &object->data.cone;
	t_cone_vars				vars;

	_cone_hit_compute(cone, ray, &vars);
	if (vars.d < 0.)
		return (0);
	return (_cone_hit_create_hit(cone, ray, hit, &vars));
}

t_color	cone_get_color(
			t_object *object
			)
{
	t_object_cone *const	cone = &object->data.cone;

	return (cone->color);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //

static void	_cone_hit_compute(
				t_object_cone *cone,
				const t_ray *ray,
				t_cone_vars *vars
				)
{
	t_coord		kk1;
	t_vector3	x;
	t_coord		dv;
	t_coord		xv;
	t_coord		dd;

	vec3_sub(&x, &ray->origin, &cone->origin);
	dd = vec3_dot(&ray->dir, &ray->dir);
	kk1 = cone->tang * cone->tang + 1;
	dv = vec3_dot(&ray->dir, &cone->axis);
	xv = vec3_dot(&x, &cone->axis);
	vars->a = dd - kk1 * dv * dv;
	vars->b = 2 * (vec3_dot(&ray->dir, &x) - kk1 * dv * xv);
	vars->c = vec3_dot(&x, &x) - kk1 * xv * xv;
	vars->d = vars->b * vars->b - 4 * vars->a * vars->c;
	vars->d_sqrt = sqrt(vars->d);
}

static int	_cone_hit_compute_height(
				t_object_cone *cone,
				const t_ray *ray,
				t_hit *hit,
				t_coord t
				)
{
	t_vector3	p;
	t_vector3	pc;
	t_vector3	o_diff;
	t_coord		m;

	ray_at(ray, &p, t);
	vec3_sub(&o_diff, &cone->origin, &p);
	m = vec3_dot(&o_diff, &cone->axis);
	if (m > cone->height || m < 0.)
		return (0);
	hit->t = t;
	hit->p = p;
	hit->from_dir = ray->dir;
	vec3_normalize(&hit->normal, vec3_sub(&hit->normal,
			vec3_sub(&pc, &p, &cone->origin), vec3_mul(&hit->normal,
					&cone->axis, (cone->tang * cone->tang + 1) * (-m))));
	hit->color = cone->color;
	return (1);
}

static int	_cone_hit_create_hit(
				t_object_cone *cone,
				const t_ray *ray,
				t_hit *hit,
				t_cone_vars *vars
				)
{
	t_coord	t;

	t = (-vars->b - vars->d_sqrt) / (vars->a * 2.);
	if (t >= NEAR && t <= FAR
		&& _cone_hit_compute_height(cone, ray, hit, t))
		return (1);
	t = (-vars->b + vars->d_sqrt) / (vars->a * 2.);
	if (t >= NEAR && t <= FAR
		&& _cone_hit_compute_height(cone, ray, hit, t))
		return (vec3_mul(&hit->normal, &hit->normal, -1), 1);
	return (0);
}
