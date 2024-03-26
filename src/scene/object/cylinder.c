/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:34:21 by amassias          #+#    #+#             */
/*   Updated: 2024/03/26 19:52:18 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cylinder.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
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

static void		_cylinder_hit_compute(
					t_object_cylinder *cylinder,
					const t_ray *ray,
					t_cylinder_vars *vars
					);

static int		_cylinder_hit_compute_height(
					t_object_cylinder *cylinder,
					const t_ray *ray,
					t_hit *hit,
					t_coord t
					);

static int		_cylinder_hit_create_hit(
					t_object_cylinder *cylinder,
					const t_ray *ray,
					t_hit *hit,
					t_cylinder_vars *vars
					);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	cylinder_hit(
		t_object *object,
		const t_ray *ray,
		t_hit *hit
		)
{
	t_object_cylinder *const	cylinder = &object->data.cylinder;
	t_cylinder_vars				vars;

	_cylinder_hit_compute(cylinder, ray, &vars);
	if (vars.d < 0.)
		return (0);
	return (_cylinder_hit_create_hit(cylinder, ray, hit, &vars));
}

t_color	cylinder_get_color(
			t_object *object
			)
{
	t_object_cylinder *const	cylinder = &object->data.cylinder;

	return (cylinder->color);
}

// ************************************************************************** //
// *                                                                        * //
// * Helper function                                                        * //
// *                                                                        * //
// ************************************************************************** //

static void	_cylinder_hit_compute(
				t_object_cylinder *cylinder,
				const t_ray *ray,
				t_cylinder_vars *vars
				)
{
	t_vector3	x;
	t_vector3	diff;
	t_vector3	x_x_diff;
	t_vector3	d_x_diff;
	t_coord		radius;

	vec3_sub(&x, &ray->origin, &cylinder->origin);
	vec3_sub(&diff, &cylinder->origin,
		vec3_add(&diff, &cylinder->origin,
			vec3_mul(&diff, &cylinder->axis, cylinder->height)));
	vec3_cross(&x_x_diff, &x, &diff);
	vec3_cross(&d_x_diff, &ray->dir, &diff);
	radius = vec3_dot(&diff, &diff);
	vars->a = vec3_dot(&d_x_diff, &d_x_diff);
	vars->b = 2 * vec3_dot(&d_x_diff, &x_x_diff);
	vars->c = vec3_dot(&x_x_diff, &x_x_diff)
		- ((cylinder->diameter / 2.) * (cylinder->diameter / 2.) * radius);
	vars->d = vars->b * vars->b - 4 * vars->a * vars->c;
	vars->d_sqrt = sqrt(vars->d);
}

static int	_cylinder_hit_compute_height(
				t_object_cylinder *cylinder,
				const t_ray *ray,
				t_hit *hit,
				t_coord t
				)
{
	t_vector3	p;
	t_vector3	o_diff;
	t_ray		cyl_ray;
	t_coord		dist_to_point;

	ray_at(ray, &p, t);
	vec3_sub(&o_diff, &cylinder->origin, &p);
	dist_to_point = vec3_dot(&o_diff, &cylinder->axis);
	if (fabs(dist_to_point) > cylinder->height / 2)
		return (0);
	cyl_ray.origin = cylinder->origin;
	cyl_ray.dir = cylinder->axis;
	hit->t = t;
	hit->p = p;
	hit->from_dir = ray->dir;
	ray_at(&cyl_ray, &hit->normal, -dist_to_point);
	vec3_normalize(&hit->normal, vec3_sub(&hit->normal, &p, &hit->normal));
	hit->color = cylinder->color;
	return (1);
}

static int	_cylinder_hit_create_hit(
				t_object_cylinder *cylinder,
				const t_ray *ray,
				t_hit *hit,
				t_cylinder_vars *vars
				)
{
	t_coord	t;

	t = (-vars->b - vars->d_sqrt) / (vars->a * 2.);
	if (t >= NEAR && t <= FAR
		&& _cylinder_hit_compute_height(cylinder, ray, hit, t))
		return (1);
	t = (-vars->b + vars->d_sqrt) / (vars->a * 2.);
	if (t >= NEAR && t <= FAR
		&& _cylinder_hit_compute_height(cylinder, ray, hit, t))
		return (vec3_mul(&hit->normal, &hit->normal, -1), 1);
	return (0);
}
