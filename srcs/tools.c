/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:17:45 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 14:17:47 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

char	*get_bmp_file_name(char *sc_name, int id, t_scene *sc)
{
	char	*bmp_file_name;
	int		sc_name_len;
	int		dstsize;
	char	*n;
	int		i;

	sc_name_len = ft_strlen(sc_name);
	n = ft_itoa(id);
	dstsize = sc_name_len + ft_strlen(n) + 12;
	if (!(bmp_file_name = malloc(sizeof(char) * dstsize)))
		error_handle("Failed to malloc .bmp file name.", sc);
	*bmp_file_name = '\0';
	i = 0;
	while (i < sc_name_len && sc_name[i] != '/')
		i++;
	if (i == sc_name_len)
		i = -1;
	ft_strlcat(bmp_file_name, &sc_name[i + 1], dstsize);
	ft_strlcat(bmp_file_name, "_", dstsize);
	ft_strlcat(bmp_file_name, n, dstsize);
	ft_strlcat(bmp_file_name, ".bmp", dstsize);
	free(n);
	return (bmp_file_name);
}

void	window_size_check(t_scene *sc)
{
	int	sizex;
	int	sizey;

	mlx_get_screen_size(sc->mlx_ptr, &sizex, &sizey);
	sc->reso.ratio = sc->reso.x / (double)sc->reso.y;
	while (sc->reso.x > sizex || sc->reso.y > sizey)
	{
		if (sc->reso.x > sizex)
		{
			sc->reso.x = sizex;
			sc->reso.y = (int)(sc->reso.x / sc->reso.ratio);
		}
		else if (sc->reso.y > sizey)
		{
			sc->reso.y = sizey;
			sc->reso.x = (int)(sc->reso.y * sc->reso.ratio);
		}
	}
}

int		solve_quadratic(double abc[3], double *t0, double *t1)
{
	double delta;
	double q;
	double a;
	double b;
	double c;

	a = abc[0];
	b = abc[1];
	c = abc[2];
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FALSE);
	else if (delta == 0)
	{
		*t0 = -0.5 * b / a;
		*t1 = *t0;
	}
	else
	{
		q = b > 0 ? -0.5 * (b + sqrt(delta)) : -0.5 * (b - sqrt(delta));
		*t0 = q / a;
		*t1 = c / q;
	}
	return (TRUE);
}

int		in_line(t_vec b, t_vec a, t_vec q, t_vec n)
{
	if (vec_dot(vec_cross(vec_sub(b, a), vec_sub(q, a)), n) >= 0)
		return (TRUE);
	return (FALSE);
}

void	swap(double *t0, double *t1)
{
	double tmp;

	tmp = *t0;
	*t0 = *t1;
	*t1 = tmp;
}
