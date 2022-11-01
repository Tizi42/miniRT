/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shadow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 14:02:29 by tyuan             #+#    #+#             */
/*   Updated: 2021/01/01 14:02:30 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** 	Assume k(diffuse) and k(shine) = k(object)
**  I took out color / 1 * distance^2 because the scene scale is way too big.
*/

t_vec	shadow_ray(t_vec ray_dir, t_scene sc, t_vec pt)
{
	t_vec	normal;
	t_vec	p2l;
	double	diffuse;
	double	shine;
	t_vec	i_pt;

	normal = get_surface_normal(*sc.obj, pt);
	if (vec_dot(ray_dir, normal) > 0)
		normal = vec_mul(normal, -1);
	if (sc.light->para)
		p2l = vec_mul(sc.light->dir, -1);
	else
		p2l = vec_sub(sc.light->pos, pt);
	diffuse = fmax(0, vec_dot(normal, normalize(p2l)));
	shine = pow(fmax(0, vec_dot(normal, normalize(
				vec_add(p2l, vec_mul(ray_dir, -1))))), 40);
	i_pt = vec_mul(vec_mul_vec(sc.light->i, sc.obj->color.i),
					(diffuse + shine));
	check_color_i(&i_pt);
	return (i_pt);
}

int		is_shadow_para(t_scene sc, t_vec p)
{
	double	dis_hit;
	t_obj	*n;
	double	bias;
	t_vec	tmp_norm;

	bias = 0.002;
	p = vec_add(p, vec_mul(sc.light->dir, -bias));
	n = sc.obj;
	if (sc.obj->id == PYRAMID || sc.obj->id == CUBE)
		tmp_norm = sc.obj->norm;
	if (get_hit_point(vec_mul(sc.light->dir, -1),
						&dis_hit, &sc, p) && n != sc.obj)
		return (TRUE);
	else
	{
		if (sc.obj->id == PYRAMID || sc.obj->id == CUBE)
			sc.obj->norm = tmp_norm;
		return (FALSE);
	}
}

/*
** 0,002 is the bias here to evite black points shadow(shadow acne).
*/

int		is_shadow(t_scene sc, t_vec p)
{
	double	dis_hit;
	double	dis_p2l;
	t_vec	p2l;
	t_obj	*n;
	t_vec	tmp_norm;

	p2l = vec_sub(sc.light->pos, p);
	dis_p2l = vec_length(p2l);
	p = vec_add(p, vec_mul(normalize(p2l), 0.002));
	n = sc.obj;
	if (sc.obj->id == PYRAMID || sc.obj->id == CUBE)
		tmp_norm = sc.obj->norm;
	if (get_hit_point(normalize(p2l), &dis_hit, &sc, p)
						&& n != sc.obj && dis_hit < dis_p2l)
		return (TRUE);
	else
	{
		if (sc.obj->id == PYRAMID || sc.obj->id == CUBE)
			sc.obj->norm = tmp_norm;
		return (FALSE);
	}
}
