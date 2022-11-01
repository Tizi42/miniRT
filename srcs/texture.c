/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 10:40:20 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/28 10:40:21 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_checker	uv_checkers(int width, int height, t_color color1, t_color color2)
{
	t_checker new;

	new.width = width;
	new.height = height;
	new.color1 = color1;
	new.color2 = color2;
	return (new);
}

t_color		pattern_at(int id, t_checker pattern, t_vec p)
{
	t_uv o;

	if (id == SPHERE)
		o = spherical_map(p);
	else if (id == PLANE)
		o = planar_map(p);
	else if (id == CYLINDER)
		o = cylindrical_map(p);
	return (uv_pattern_at(pattern, o.u, o.v));
}

t_color		uv_pattern_at(t_checker pattern, double u, double v)
{
	double u2;
	double v2;

	u2 = floor(u * pattern.width);
	v2 = floor(v * pattern.height);
	if (fmod((u2 + v2), 2) == 0)
		return (pattern.color1);
	else
		return (pattern.color2);
}
