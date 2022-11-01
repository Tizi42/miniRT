/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:32:18 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/25 15:32:21 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		hit_sp(t_vec ray_dir, double *t, t_obj *sphere, t_vec cam_pos)
{
	double	abc[3];
	t_vec	tmp;
	double	t0;
	double	t1;

	tmp = vec_sub(cam_pos, sphere->pt);
	abc[0] = 1;
	abc[1] = 2 * vec_dot(ray_dir, tmp);
	abc[2] = vec_dot(tmp, tmp) - pow(sphere->diameter / 2.0, 2);
	if (!solve_quadratic(abc, &t0, &t1))
		return (FALSE);
	if (t0 > t1)
		swap(&t0, &t1);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (FALSE);
	}
	*t = t0;
	return (TRUE);
}

int		hit_pl(t_vec ray_dir, double *t, t_obj *plane, t_vec cam_pos)
{
	double denom;
	double distance;

	denom = vec_dot(plane->ori, ray_dir);
	if (denom == 0 && vec_dot(vec_sub(plane->pt, cam_pos), plane->ori) == 0)
	{
		*t = 0;
		return (TRUE);
	}
	else if (fabs(denom) > 0.00001)
	{
		distance = vec_dot(vec_sub(plane->pt, cam_pos), plane->ori) / denom;
		if (distance >= 0)
		{
			*t = distance;
			return (TRUE);
		}
	}
	return (FALSE);
}

int		hit_sq(t_vec ray_dir, double *t, t_obj *square, t_vec cam_pos)
{
	t_vec	hit_pt;

	if (hit_pl(ray_dir, t, square, cam_pos))
	{
		hit_pt = vec_add(cam_pos, vec_mul(ray_dir, *t));
		if (fabs(vec_dot(vec_sub(hit_pt, square->pt), square->pt2))
			<= 0.5 * square->diameter && fabs(vec_dot(vec_sub(hit_pt,
				square->pt), square->pt3)) <= 0.5 * square->diameter)
			return (TRUE);
	}
	return (FALSE);
}

int		hit_tr(t_vec ray_dir, double *t, t_obj *triangle, t_vec cam_pos)
{
	t_vec hit_pt;

	if (hit_pl(ray_dir, t, triangle, cam_pos))
	{
		hit_pt = vec_add(cam_pos, vec_mul(ray_dir, *t));
		if (in_line(triangle->pt2, triangle->pt, hit_pt, triangle->ori))
			if (in_line(triangle->pt3, triangle->pt2, hit_pt, triangle->ori))
				if (in_line(triangle->pt, triangle->pt3, hit_pt, triangle->ori))
					return (TRUE);
	}
	return (FALSE);
}
