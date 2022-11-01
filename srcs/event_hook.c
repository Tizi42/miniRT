/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:15:34 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 11:15:38 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		button_release_hook(int button, int x, int y, t_scene *sc)
{
	if (x < (sc->reso.x / 4.0))
		sc->cam->dir = rotation(sc->cam->dir, get_vec(0, 1, 0),
						degree_to_radian(ROTATE_SCALE));
	else if (x > (sc->reso.x / 4.0 * 3))
		sc->cam->dir = rotation(sc->cam->dir, get_vec(0, 1, 0),
						degree_to_radian(-ROTATE_SCALE));
	if (y > (sc->reso.y / 4.0 * 3))
		sc->cam->dir = rotation(sc->cam->dir, sc->cam->left,
						degree_to_radian(ROTATE_SCALE));
	else if (y < (sc->reso.y / 4.0))
		sc->cam->dir = rotation(sc->cam->dir, sc->cam->left,
						degree_to_radian(-ROTATE_SCALE));
	ray_tracing(sc);
	mlx_put_image_to_window(sc->mlx_ptr, sc->win_ptr, sc->cam->img.ptr, 0, 0);
	ft_printf("Click screen (x:%i,y:%i) with button %i\n", x, y, button);
	return (0);
}

int		key_press_hook(int keycode, t_scene *sc)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_UP ||
		keycode == KEY_DOWN || keycode == KEY_A || keycode == KEY_D ||
		keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (sc->obj->select == 1)
		{
			move_obj(keycode, sc);
			if (sc->obj->id == PYRAMID)
				set_py(sc->obj);
			else if (sc->obj->id == CUBE)
				set_cu(sc->obj);
		}
		else
			move_cam(keycode, sc);
	}
	else if (keycode == KEY_J || keycode == KEY_L ||
			keycode == KEY_I || keycode == KEY_M)
		move_para_light(keycode, sc);
	ft_printf("key_press: %i\n", keycode);
	return (0);
}

int		key_release_hook(int keycode, t_scene *sc)
{
	event_re_render(keycode, sc);
	if (keycode == KEY_ESC)
		free_exit(sc, EXIT_SUCCESS);
	else if (keycode == KEY_C)
	{
		change_cam(sc);
		mlx_put_image_to_window(sc->mlx_ptr, sc->win_ptr,
								sc->cam->img.ptr, 0, 0);
	}
	ft_printf("key_release: %i\n", keycode);
	return (0);
}

void	event_re_render(int keycode, t_scene *sc)
{
	t_obj *tmp_obj;
	t_cam *tmp_cam;

	para_light_re_render(keycode, sc);
	select_type(keycode, sc);
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_UP ||
		keycode == KEY_DOWN || keycode == KEY_A || keycode == KEY_D ||
		keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (sc->obj->select == 1)
		{
			tmp_cam = sc->cam;
			tmp_obj = sc->obj;
			creat_image_for_all_cams(sc);
			sc->cam = tmp_cam;
			sc->obj = tmp_obj;
		}
		else
			ray_tracing(sc);
		mlx_put_image_to_window(sc->mlx_ptr, sc->win_ptr,
								sc->cam->img.ptr, 0, 0);
	}
}

void	select_type(int keycode, t_scene *sc)
{
	if (keycode == KEY_Q)
		select_obj(sc, SQUARE);
	else if (keycode == KEY_P)
		select_obj(sc, PYRAMID);
	else if (keycode == KEY_U)
		select_obj(sc, CUBE);
	else if (keycode == KEY_H)
		select_obj(sc, SPHERE);
	else if (keycode == KEY_Y)
		select_obj(sc, CYLINDER);
	else if (keycode == KEY_K)
		select_obj(sc, 0);
}
