/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:32:15 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 14:32:16 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180.0);
}

double	fmax_3(double a, double b, double c)
{
	if (fabs(a) >= fabs(b) && fabs(a) >= fabs(c))
		return (a);
	else if (fabs(b) >= fabs(a) && fabs(b) >= fabs(c))
		return (b);
	else
		return (c);
}

void	find_square_side_vecs(t_obj *sq)
{
	double axis;

	axis = fmax_3(sq->ori.x, sq->ori.y, sq->ori.z);
	if (axis == sq->ori.x)
	{
		sq->pt2 = normalize(get_vec(-sq->ori.z / sq->ori.x, 0, 1));
		sq->pt3 = normalize(get_vec(-sq->ori.y / sq->ori.x, 1, 0));
	}
	else if (axis == sq->ori.y)
	{
		sq->pt2 = normalize(get_vec(1, -sq->ori.x / sq->ori.y, 0));
		sq->pt3 = normalize(get_vec(0, -sq->ori.z / sq->ori.y, 1));
	}
	else
	{
		sq->pt2 = normalize(get_vec(0, 1, -sq->ori.y / sq->ori.z));
		sq->pt3 = normalize(get_vec(1, 0, -sq->ori.x / sq->ori.z));
	}
}

void	put_string_select(int id, t_scene sc)
{
	char		*str;
	static int	n;

	n += 20;
	if (n > sc.reso.y - 20)
		n = 20;
	if (id == PYRAMID)
		str = ft_strdup("Select Pyramid");
	else if (id == SQUARE)
		str = ft_strdup("Select Square");
	else if (id == CUBE)
		str = ft_strdup("Select Cube");
	else if (id == SPHERE)
		str = ft_strdup("Select Sphere");
	else if (id == CYLINDER)
		str = ft_strdup("Select Cylinder");
	else
		str = ft_strdup("Select no object");
	mlx_string_put(sc.mlx_ptr, sc.win_ptr, 20, n, 16777215, str);
	free(str);
}

void	set_side_for_sq(t_obj *sq, t_vec pt2, t_vec pt3)
{
	sq->pt2 = pt2;
	sq->pt3 = pt3;
}
