/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:50:50 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/04 14:50:55 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	color_store(t_scene *sc, int x, int y, t_color color)
{
	int pixel;

	pixel = (y * sc->cam->img.line_bytes) + (x * 4);
	if (sc->cam->img.endian == 0)
	{
		sc->cam->img.add[pixel + 0] = color.b;
		sc->cam->img.add[pixel + 1] = color.g;
		sc->cam->img.add[pixel + 2] = color.r;
		sc->cam->img.add[pixel + 3] = 0;
	}
	else if (sc->cam->img.endian == 1)
	{
		sc->cam->img.add[pixel + 0] = 0;
		sc->cam->img.add[pixel + 1] = color.r;
		sc->cam->img.add[pixel + 2] = color.g;
		sc->cam->img.add[pixel + 3] = color.b;
	}
}

void	check_color_i(t_vec *i)
{
	if (i->x > 1)
		i->x = 1;
	else if (i->x < 0)
		i->x = 0;
	if (i->y > 1)
		i->y = 1;
	else if (i->y < 0)
		i->y = 0;
	if (i->z > 1)
		i->z = 1;
	else if (i->z < 0)
		i->z = 0;
}

void	color_to_i(t_color *color)
{
	color->i.x = color->r / 255.0;
	color->i.y = color->g / 255.0;
	color->i.z = color->b / 255.0;
}

t_color	i_to_color(t_color *color)
{
	color->r = (int)(color->i.x * 255);
	color->g = (int)(color->i.y * 255);
	color->b = (int)(color->i.z * 255);
	return (*color);
}

/*
** int RGB = (R * 2^16) + ( G * 2^8)+B
*/

int		i_to_rgb(t_vec i)
{
	int r;
	int g;
	int b;

	r = (int)(i.x * 255);
	g = (int)(i.y * 255);
	b = (int)(i.z * 255);
	return (r * 65536 + g * 256 + b);
}
