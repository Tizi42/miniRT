/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rt_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:29:49 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 14:29:52 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ray_tracing_thread_b(t_thread *th)
{
	int		x;
	int		y;
	t_vec	ray_dir;

	x = th->x;
	while (x < th->x + th->sc.reso.x / (THREAD_NB - 1) && x < th->sc.reso.x)
	{
		y = 0;
		while (y < th->sc.reso.y)
		{
			ray_dir = get_cam_ray(x, y, &th->sc);
			intersect(ray_dir, &th->sc, x, y);
			y++;
		}
		x++;
	}
}

void	ray_tracing_thread_a(t_scene *sc)
{
	int			x;
	pthread_t	thread[THREAD_NB];
	t_thread	th[THREAD_NB];
	int			i[2];

	x = 0;
	i[0] = 0;
	set_cam(sc);
	while (x < sc->reso.x)
	{
		ft_memcpy(&th[i[0]].sc, sc, sizeof(t_scene));
		th[i[0]].x = x;
		if (pthread_create(
				&thread[i[0]], NULL, (void *)ray_tracing_thread_b, &th[i[0]]))
			error_handle("Failed to creat thread.", sc);
		i[0]++;
		x += sc->reso.x / (THREAD_NB - 1);
	}
	i[1] = 0;
	while (i[1] < i[0])
		pthread_join(thread[i[1]++], NULL);
}
