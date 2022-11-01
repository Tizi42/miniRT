/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 18:37:35 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/20 18:37:38 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		hit_cy(t_vec ray_dir, double *t, t_obj *cy, t_vec cam_pos)
{
	double t0;
	double t1;

	if (!hit_cy_round(ray_dir, &t0, cy, cam_pos))
		t0 = -1;
	if (cy->hollow || !hit_cy_caps(ray_dir, &t1, *cy, cam_pos))
		t1 = -1;
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

int		hit_cy_round(t_vec ray_dir, double *t, t_obj *cy, t_vec cam_pos)
{
	double t0;
	double t1;
	double abc[3];

	get_cy_abc(abc, ray_dir, cy, cam_pos);
	if (solve_quadratic(abc, &t0, &t1))
	{
		if (t0 > t1)
			swap(&t0, &t1);
		if (t0 < 0 || !within_finite_cy(t0, *cy, ray_dir, cam_pos))
		{
			t0 = t1;
			if (t0 < 0 || !within_finite_cy(t0, *cy, ray_dir, cam_pos))
				return (FALSE);
		}
		*t = t0;
		return (TRUE);
	}
	return (FALSE);
}

int		hit_cy_caps(t_vec ray_dir, double *t, t_obj cy, t_vec cam_pos)
{
	double t0;
	double t1;

	cy.ori = vec_mul(cy.ori, -1);
	if (!hit_disk(ray_dir, &t0, cy, cam_pos))
		t0 = -1;
	cy.ori = vec_mul(cy.ori, -1);
	cy.pt = cy.pt2;
	if (!hit_disk(ray_dir, &t1, cy, cam_pos))
		t1 = -1;
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

int		within_finite_cy(double t, t_obj cy, t_vec ray_dir, t_vec cam_pos)
{
	t_vec q;
	t_vec bottom;
	t_vec top;

	q = vec_add(cam_pos, vec_mul(ray_dir, t));
	bottom = cy.pt;
	top = cy.pt2;
	if (vec_dot(cy.ori, vec_sub(q, bottom)) > 0
		&& vec_dot(cy.ori, vec_sub(q, top)) < 0)
		return (TRUE);
	return (FALSE);
}

void	get_cy_abc(double abc[3], t_vec ray_dir, t_obj *cy, t_vec cam_pos)
{
	t_vec p0;
	t_vec t1;
	t_vec t2;

	p0 = vec_sub(cam_pos, cy->pt);
	t1 = vec_mul(cy->ori, vec_dot(ray_dir, cy->ori));
	t2 = vec_mul(cy->ori, vec_dot(p0, cy->ori));
	abc[0] = vec_dot(vec_sub(ray_dir, t1), vec_sub(ray_dir, t1));
	abc[1] = 2 * vec_dot(vec_sub(ray_dir, t1), vec_sub(p0, t2));
	abc[2] = vec_dot(vec_sub(p0, t2),
				vec_sub(p0, t2)) - pow(cy->diameter / 2.0, 2);
}
