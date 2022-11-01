/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_uvmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 10:40:20 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/28 10:40:21 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_uv		spherical_map(t_vec p)
{
	t_uv	o;
	double	theta;
	double	radius;
	double	phi;
	double	raw_u;

	theta = atan2(p.x, p.z);
	radius = vec_length(p);
	phi = acos(p.y / radius);
	raw_u = theta / (2 * M_PI);
	o.u = 1 - (raw_u + 0.5);
	o.v = 1 - phi / M_PI;
	return (o);
}

t_uv		planar_map(t_vec p)
{
	t_uv	o;

	o.u = fmod(p.x, 1);
	o.v = fmod(p.z, 1);
	return (o);
}

t_uv		cylindrical_map(t_vec p)
{
	t_uv	o;
	double	theta;
	double	raw_u;

	theta = atan2(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	o.u = 1 - (raw_u + 0.5);
	o.v = fmod(p.y, 1);
	return (o);
}
