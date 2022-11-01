/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:44:36 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/06 19:45:20 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

double	vec_length(t_vec v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec	get_vec(double a, double b, double c)
{
	t_vec new;

	new.x = a;
	new.y = b;
	new.z = c;
	return (new);
}

double	*vec_to_arr(t_vec s)
{
	static double arr[3];

	arr[0] = s.x;
	arr[1] = s.y;
	arr[2] = s.z;
	return (arr);
}
