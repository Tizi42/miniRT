/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:15:34 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 11:15:38 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	move_obj(int keycode, t_scene *sc)
{
	int		i;
	t_obj	*obj;

	i = sc->obj->id == PYRAMID ? -1 : 1;
	if (move_obj_cy_sp(keycode, sc))
		return ;
	obj = sc->obj;
	if (keycode == KEY_W)
		obj->pt = vec_add(obj->pt, vec_mul(obj->pt3, -TRANS_SCALE));
	else if (keycode == KEY_S)
		obj->pt = vec_add(obj->pt, vec_mul(obj->pt3, TRANS_SCALE));
	else if (keycode == KEY_A)
		obj->pt = vec_add(obj->pt, vec_mul(obj->pt2, -TRANS_SCALE));
	else if (keycode == KEY_D)
		obj->pt = vec_add(obj->pt, vec_mul(obj->pt2, TRANS_SCALE));
	else if (keycode == KEY_UP)
		obj->pt = vec_add(obj->pt, vec_mul(obj->ori, i * TRANS_SCALE));
	else if (keycode == KEY_DOWN)
		obj->pt = vec_add(obj->pt, vec_mul(obj->ori, -i * TRANS_SCALE));
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		i = keycode == KEY_LEFT ? ROTATE_SCALE : -ROTATE_SCALE;
		obj->pt2 = rotation(obj->pt2, get_vec(0, 1, 0), degree_to_radian(i));
		obj->pt3 = rotation(obj->pt3, get_vec(0, 1, 0), degree_to_radian(i));
	}
}

void	move_cam(int keycode, t_scene *sc)
{
	t_cam *cam;

	cam = sc->cam;
	if (keycode == KEY_W)
		cam->pos = vec_add(cam->pos, vec_mul(cam->dir, TRANS_SCALE));
	else if (keycode == KEY_S)
		cam->pos = vec_sub(cam->pos, vec_mul(cam->dir, TRANS_SCALE));
	else if (keycode == KEY_A)
		cam->pos = vec_add(cam->pos, vec_mul(cam->left, TRANS_SCALE));
	else if (keycode == KEY_D)
		cam->pos = vec_add(cam->pos, vec_mul(cam->right, TRANS_SCALE));
	else if (keycode == KEY_UP)
		cam->pos.y += TRANS_SCALE;
	else if (keycode == KEY_DOWN)
		cam->pos.y -= TRANS_SCALE;
	else if (keycode == KEY_LEFT)
		cam->dir = rotation(cam->dir, get_vec(0, 1, 0),
					degree_to_radian(ROTATE_SCALE));
	else if (keycode == KEY_RIGHT)
		cam->dir = rotation(cam->dir, get_vec(0, 1, 0),
					degree_to_radian(-ROTATE_SCALE));
}

void	select_obj(t_scene *sc, int id)
{
	t_obj	*tmp_obj;
	t_list	*lst;

	if (id == 0)
	{
		sc->obj->select = 0;
		put_string_select(id, *sc);
		return ;
	}
	lst = find_obj_in_lst(sc->list_objs, sc->obj);
	while (lst)
	{
		tmp_obj = lst->content;
		if (tmp_obj->id == id && (sc->obj->select != 1 ||
			(sc->obj->select == 1 && tmp_obj != sc->obj)))
		{
			sc->obj->select = 0;
			tmp_obj->select = 1;
			put_string_select(id, *sc);
			sc->obj = tmp_obj;
			return ;
		}
		if (lstiter_till_obj(&lst, sc))
			return ;
	}
}

void	para_light_re_render(int keycode, t_scene *sc)
{
	if (keycode == KEY_J || keycode == KEY_L
		|| keycode == KEY_I || keycode == KEY_M)
	{
		ray_tracing(sc);
		mlx_put_image_to_window(sc->mlx_ptr, sc->win_ptr,
						sc->cam->img.ptr, 0, 0);
	}
}

void	move_para_light(int keycode, t_scene *sc)
{
	t_light *l;
	t_vec	n;

	l = sc->light;
	if (l->dir.x != 0)
		n = normalize(get_vec(-l->dir.z / l->dir.x, 0, 1));
	else if (l->dir.z != 0)
		n = normalize(get_vec(1, 0, -l->dir.x / l->dir.z));
	else
		n = get_vec(1, 0, 1);
	if (keycode == KEY_J)
		l->dir = rotation(l->dir, get_vec(0, 1, 0),
							degree_to_radian(ROTATE_SCALE));
	else if (keycode == KEY_L)
		l->dir = rotation(l->dir, get_vec(0, 1, 0),
						degree_to_radian(-ROTATE_SCALE));
	else if (keycode == KEY_I)
		l->dir = rotation(l->dir, n, degree_to_radian(ROTATE_SCALE));
	else if (keycode == KEY_M)
		l->dir = rotation(l->dir, n, degree_to_radian(-ROTATE_SCALE));
}
