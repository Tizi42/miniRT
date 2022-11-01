/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:54:39 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/05 15:55:45 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	get_cam_ray(int x, int y, t_scene *sc)
{
	t_vec	image_point;
	double	aspect_ratio;
	double	fov_ratio;
	t_vec	ray_dir;

	aspect_ratio = sc->reso.x / (double)sc->reso.y;
	fov_ratio = tan(sc->cam->fov / 2 * M_PI / 180);
	image_point.x = (2 * ((x + 0.5) / sc->reso.x) - 1)
					* aspect_ratio * fov_ratio;
	image_point.y = (1 - 2 * ((y + 0.5) / sc->reso.y)) * fov_ratio;
	image_point.z = -1;
	image_point = rotation(image_point, sc->cam->rotate_k0,
					sc->cam->rotate_a0);
	if (sc->cam->dir.x != 0 || sc->cam->dir.z != 0)
		image_point = rotation(image_point,
					sc->cam->rotate_k, sc->cam->rotate_angle);
	ray_dir = normalize(image_point);
	return (ray_dir);
}

/*
** Rodrigues' rotation formula
*/

t_vec	rotation(t_vec pt, t_vec k, double angle)
{
	pt = vec_add(vec_add(vec_mul(pt, cos(angle)), vec_mul(vec_cross(k, pt),
			sin(angle))), vec_mul(k, vec_dot(k, pt) * (1 - cos(angle))));
	return (pt);
}

void	set_cam(t_scene *sc)
{
	t_vec m;

	if (sc->cam->dir.x != 0 || sc->cam->dir.z != 0)
		m = normalize(get_vec(sc->cam->dir.x, 0, sc->cam->dir.z));
	else
		m = sc->cam->dir;
	sc->cam->rotate_a0 = acos(vec_dot(get_vec(0, 0, -1), m));
	sc->cam->rotate_k0 = normalize(vec_cross(get_vec(0, 0, -1), m));
	if (sc->cam->dir.x != 0 || sc->cam->dir.z != 0)
	{
		sc->cam->rotate_k = normalize(vec_cross(m, sc->cam->dir));
		sc->cam->rotate_angle = acos(vec_dot(m, sc->cam->dir));
	}
	sc->cam->left = rotation(get_vec(-1, 0, 0), sc->cam->rotate_k0,
					sc->cam->rotate_a0);
	sc->cam->right = rotation(get_vec(1, 0, 0), sc->cam->rotate_k0,
					sc->cam->rotate_a0);
}

void	change_cam(t_scene *sc)
{
	int		id;
	t_cam	*tmp;
	t_list	*lst;

	id = sc->cam->id;
	lst = sc->list_cams;
	while (lst)
	{
		tmp = lst->content;
		if (tmp->id == id)
		{
			if (lst->next)
				sc->cam = lst->next->content;
			else
				sc->cam = sc->list_cams->content;
			return ;
		}
		lst = lst->next;
	}
}
