/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:44:36 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/06 19:45:20 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	normalize(t_vec v)
{
	double	norm;
	t_vec	nv;

	norm = vec_length(v);
	if (norm == 0)
		return (v);
	nv.x = v.x / norm;
	nv.y = v.y / norm;
	nv.z = v.z / norm;
	return (nv);
}

t_vec	get_surface_normal(t_obj obj, t_vec pt)
{
	double	t;

	if (obj.id == SPHERE)
		return (normalize(vec_sub(pt, obj.pt)));
	else if (obj.id == CYLINDER)
	{
		if (vec_length(vec_sub(pt, obj.pt2)) < obj.diameter / 2.0)
			return (obj.ori);
		else if (vec_length(vec_sub(pt, obj.pt)) < obj.diameter / 2.0)
			return (vec_mul(obj.ori, -1));
		else
		{
			t = vec_dot(vec_sub(pt, obj.pt), obj.ori);
			obj.pt3 = vec_add(obj.pt, vec_mul(obj.ori, t));
			return (normalize(vec_sub(pt, obj.pt3)));
		}
	}
	else if (obj.id == PYRAMID || obj.id == CUBE)
		return (obj.norm);
	else
		return (obj.ori);
}
