/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:17:02 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/09 19:17:06 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	intersect(t_vec ray_dir, t_scene *sc, int x, int y)
{
	double	t;
	t_color	i_pt;
	t_list	*lst;
	t_vec	p;

	i_pt.i = sc->background_color.i;
	lst = sc->list_lights;
	if (get_hit_point(ray_dir, &t, sc, sc->cam->pos))
	{
		i_pt.i = get_vec(0, 0, 0);
		p = vec_add(sc->cam->pos, vec_mul(ray_dir, t));
		sc->obj->color = if_texture(*sc->obj, p);
		i_pt.i = vec_mul_vec(sc->amb.i, sc->obj->color.i);
		while (lst)
		{
			sc->light = lst->content;
			if ((sc->light->para && !is_shadow_para(*sc, p))
					|| (!sc->light->para && !is_shadow(*sc, p)))
				i_pt.i = vec_add(i_pt.i, shadow_ray(ray_dir, *sc, p));
			lst = lst->next;
		}
		check_color_i(&i_pt.i);
	}
	color_store(sc, x, y, i_to_color(&i_pt));
}

t_color	if_texture(t_obj obj, t_vec p)
{
	t_color c;

	if ((obj.id == SPHERE || obj.id == CYLINDER || obj.id == PLANE)
				&& obj.checker.width != 0)
	{
		c = pattern_at(obj.id, obj.checker, adjust_p_for_mapping(obj, p));
		return (c);
	}
	return (obj.color);
}

t_vec	adjust_p_for_mapping(t_obj obj, t_vec p)
{
	t_vec	k;
	double	a;

	if (obj.id == SPHERE)
		p = vec_sub(p, obj.pt);
	else if (obj.id == PLANE || obj.id == CYLINDER)
	{
		if (obj.id == CYLINDER)
			p = vec_sub(p, obj.pt);
		if (obj.ori.y != 1)
		{
			k = normalize(vec_cross(obj.ori, get_vec(0, 1, 0)));
			a = acos(vec_dot(obj.ori, get_vec(0, 1, 0)));
			p = rotation(p, k, a);
		}
	}
	return (p);
}

int		get_hit_point(t_vec ray_dir, double *t, t_scene *sc, t_vec pos)
{
	double	tmp_dis;
	t_obj	*obj;
	t_list	*lst;

	lst = sc->list_objs;
	*t = -1;
	while (lst)
	{
		if (hit_objects(ray_dir, &tmp_dis, lst->content, pos))
		{
			if (*t < 0 || (*t >= 0 && *t > tmp_dis))
			{
				*t = tmp_dis;
				obj = lst->content;
			}
		}
		lst = lst->next;
	}
	if (*t >= 0)
	{
		sc->obj = obj;
		return (TRUE);
	}
	return (FALSE);
}

int		hit_objects(t_vec ray_dir, double *t, t_obj *obj, t_vec cam_pos)
{
	int hit;

	hit = FALSE;
	if (obj->id == SPHERE)
		hit = hit_sp(ray_dir, t, obj, cam_pos);
	else if (obj->id == PLANE)
		hit = hit_pl(ray_dir, t, obj, cam_pos);
	else if (obj->id == SQUARE)
		hit = hit_sq(ray_dir, t, obj, cam_pos);
	else if (obj->id == CYLINDER)
		hit = hit_cy(ray_dir, t, obj, cam_pos);
	else if (obj->id == TRIANGLE)
		hit = hit_tr(ray_dir, t, obj, cam_pos);
	else if (obj->id == PYRAMID || obj->id == CUBE)
		hit = hit_py_cu(ray_dir, t, obj, cam_pos);
	else if (obj->id == DISK)
		hit = hit_disk(ray_dir, t, *obj, cam_pos);
	return (hit);
}
