/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:32:15 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 14:32:16 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	init_sc(t_scene *sc)
{
	sc->name = NULL;
	sc->mlx_ptr = NULL;
	sc->win_ptr = NULL;
	sc->list_cams = NULL;
	sc->list_objs = NULL;
	sc->list_lights = NULL;
	sc->cam = NULL;
	sc->obj = NULL;
	sc->light = NULL;
	sc->background_color.i = get_vec(0, 0, 0);
}

t_list	*find_obj_in_lst(t_list *list_objs, t_obj *obj)
{
	t_list	*lst;

	lst = list_objs;
	while (lst)
	{
		if (lst->content == obj)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}

int		lstiter_till_obj(t_list **lst, t_scene *sc)
{
	*lst = (*lst)->next;
	if (*lst == NULL)
		*lst = sc->list_objs;
	else if ((*lst)->content == sc->obj)
		return (1);
	return (0);
}

int		move_obj_cy_sp(int keycode, t_scene *sc)
{
	t_obj	*obj;

	if (sc->obj->id != CYLINDER && sc->obj->id != SPHERE)
		return (0);
	obj = sc->obj;
	if (keycode == KEY_W)
		obj->pt = vec_add(obj->pt, vec_mul(get_vec(0, 0, -1), TRANS_SCALE));
	else if (keycode == KEY_S)
		obj->pt = vec_add(obj->pt, vec_mul(get_vec(0, 0, 1), TRANS_SCALE));
	else if (keycode == KEY_A)
		obj->pt = vec_add(obj->pt, vec_mul(get_vec(-1, 0, 0), TRANS_SCALE));
	else if (keycode == KEY_D)
		obj->pt = vec_add(obj->pt, vec_mul(get_vec(1, 0, 0), TRANS_SCALE));
	else if (keycode == KEY_UP)
		obj->pt = vec_add(obj->pt, vec_mul(get_vec(0, 1, 0), TRANS_SCALE));
	else if (keycode == KEY_DOWN)
		obj->pt = vec_add(obj->pt, vec_mul(get_vec(0, -1, 0), TRANS_SCALE));
	if (obj->id == CYLINDER)
		obj->pt2 = vec_add(obj->pt, vec_mul(obj->ori, obj->height));
	return (1);
}
