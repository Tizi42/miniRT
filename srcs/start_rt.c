/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:29:49 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 14:29:52 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	start_rt(t_scene *sc)
{
	if (!(sc->mlx_ptr = mlx_init()))
		error_handle("Failed to initialize mlx.", sc);
	creat_image_for_all_cams(sc);
	if (sc->save)
		save_bmp(sc);
	if (!(sc->win_ptr = mlx_new_window(sc->mlx_ptr,
						sc->reso.x, sc->reso.y, "rt")))
		error_handle("Failed to create new window.", sc);
	mlx_put_image_to_window(sc->mlx_ptr, sc->win_ptr, sc->cam->img.ptr, 0, 0);
	mlx_hook(sc->win_ptr, EVENT_RED_CROSS, 0, exit_hook, sc);
	mlx_hook(sc->win_ptr, EVENT_KEY_PRESS, 0, key_press_hook, sc);
	mlx_hook(sc->win_ptr, EVENT_KEY_RELEASE, 0, key_release_hook, sc);
	mlx_hook(sc->win_ptr, EVENT_BUTTON_RELEASE, 0, button_release_hook, sc);
	mlx_loop(sc->mlx_ptr);
}

void	creat_image_for_all_cams(t_scene *sc)
{
	t_list	*lst;
	int		i;

	i = 1;
	lst = sc->list_cams;
	while (lst)
	{
		ft_printf(BOLDGREEN "\rRendering image for camera no.%i/%i..."
					RESET, i++, sc->cam_count);
		sc->cam = lst->content;
		if (!sc->cam->img.ptr)
		{
			sc->cam->img.ptr = mlx_new_image(
								sc->mlx_ptr, sc->reso.x, sc->reso.y);
			sc->cam->img.add = mlx_get_data_addr(
								sc->cam->img.ptr, &sc->cam->img.pixel_bits,
								&sc->cam->img.line_bytes, &sc->cam->img.endian);
		}
		if (THREAD_NB < 2)
			ray_tracing(sc);
		else if (THREAD_NB >= 2)
			ray_tracing_thread_a(sc);
		lst = lst->next;
	}
	ft_printf("\n");
}

void	ray_tracing(t_scene *sc)
{
	int		x;
	int		y;
	t_vec	ray_dir;

	x = 0;
	set_cam(sc);
	while (x < sc->reso.x)
	{
		y = 0;
		while (y < sc->reso.y)
		{
			ray_dir = get_cam_ray(x, y, sc);
			intersect(ray_dir, sc, x, y);
			y++;
		}
		x++;
	}
}
