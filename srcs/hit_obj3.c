/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:53:47 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/30 14:53:48 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		hit_py_cu(t_vec ray_dir, double *t, t_obj *py_cu, t_vec cam_pos)
{
	double	tmp_t;
	t_list	*lst;
	t_obj	*obj;

	*t = -1;
	lst = py_cu->list;
	while (lst)
	{
		obj = lst->content;
		if (hit_objects(ray_dir, &tmp_t, obj, cam_pos)
			&& (*t < 0 || tmp_t < *t))
		{
			*t = tmp_t;
			py_cu->norm = obj->ori;
		}
		lst = lst->next;
	}
	if (*t >= 0)
		return (TRUE);
	return (FALSE);
}

int		hit_disk(t_vec ray_dir, double *t, t_obj disk, t_vec cam_pos)
{
	t_vec	q;
	double	t0;

	if (hit_pl(ray_dir, &t0, &disk, cam_pos))
	{
		q = vec_add(cam_pos, vec_mul(ray_dir, t0));
		if (vec_length(vec_sub(q, disk.pt)) < disk.diameter / 2.0)
		{
			*t = t0;
			return (TRUE);
		}
	}
	return (FALSE);
}
