/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:31:55 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/30 14:31:56 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	set_py(t_obj *py)
{
	t_vec	p[4];
	t_vec	top;

	if (py->list)
		ft_lstclear(&py->list, free);
	if (py->ori.x != 0 && py->ori.y != -1 && py->ori.x != 0)
		find_square_side_vecs(py);
	top = vec_add(py->pt, vec_mul(get_vec(0, 1, 0), py->height));
	p[0] = vec_add(vec_add(py->pt, vec_mul(py->pt2, 0.5 * py->diameter)),
					vec_mul(py->pt3, 0.5 * py->diameter));
	p[1] = vec_add(p[0], vec_mul(py->pt3, -py->diameter));
	p[2] = vec_add(p[1], vec_mul(py->pt2, -py->diameter));
	p[3] = vec_add(p[0], vec_mul(py->pt2, -py->diameter));
	ft_lstadd_front(&py->list, ft_lstnew(
		creat_tr(p[0], top, p[3], py->color)));
	ft_lstadd_front(&py->list, ft_lstnew(
		creat_tr(p[1], top, p[0], py->color)));
	ft_lstadd_front(&py->list, ft_lstnew(
		creat_tr(p[2], top, p[1], py->color)));
	ft_lstadd_front(&py->list, ft_lstnew(
		creat_tr(p[3], top, p[2], py->color)));
	ft_lstadd_front(&py->list, ft_lstnew(
		creat_sq(py->pt, py->ori, py->diameter, py->color)));
	set_side_for_sq(py->list->content, py->pt2, py->pt3);
}

void	set_cu(t_obj *cu)
{
	t_vec p[5];
	t_vec center;

	if (cu->list)
		ft_lstclear(&cu->list, free);
	if (cu->ori.x != 0 && cu->ori.y != 1 && cu->ori.z != 0)
		find_square_side_vecs(cu);
	center = vec_add(cu->pt, vec_mul(cu->ori, 0.5 * cu->diameter));
	p[0] = vec_add(cu->pt, vec_mul(cu->ori, cu->diameter));
	p[1] = vec_add(center, vec_mul(cu->pt2, 0.5 * cu->diameter));
	p[2] = vec_add(center, vec_mul(cu->pt2, -0.5 * cu->diameter));
	p[3] = vec_add(center, vec_mul(cu->pt3, 0.5 * cu->diameter));
	p[4] = vec_add(center, vec_mul(cu->pt3, -0.5 * cu->diameter));
	creat_cu_sqs(cu, p);
}

void	creat_cu_sqs(t_obj *cu, t_vec p[5])
{
	ft_lstadd_front(&cu->list, ft_lstnew(
		creat_sq(cu->pt, vec_mul(cu->ori, -1), cu->diameter, cu->color)));
	set_side_for_sq(cu->list->content, cu->pt2, cu->pt3);
	ft_lstadd_front(&cu->list, ft_lstnew(
		creat_sq(p[0], cu->ori, cu->diameter, cu->color)));
	set_side_for_sq(cu->list->content, cu->pt2, cu->pt3);
	ft_lstadd_front(&cu->list, ft_lstnew(
		creat_sq(p[1], cu->pt2, cu->diameter, cu->color)));
	ft_lstadd_front(&cu->list, ft_lstnew(
		creat_sq(p[2], vec_mul(cu->pt2, -1), cu->diameter, cu->color)));
	ft_lstadd_front(&cu->list, ft_lstnew(
		creat_sq(p[3], cu->pt3, cu->diameter, cu->color)));
	ft_lstadd_front(&cu->list, ft_lstnew(
		creat_sq(p[4], vec_mul(cu->pt3, -1), cu->diameter, cu->color)));
}

t_obj	*creat_sq(t_vec cen, t_vec ori, double side, t_color color)
{
	t_obj	*new;

	if (!(new = malloc(sizeof(t_obj))))
	{
		ft_printf("Failed to malloc square.\n");
		exit(EXIT_FAILURE);
	}
	new->id = SQUARE;
	new->pt = cen;
	new->ori = ori;
	new->diameter = side;
	ft_memcpy(&new->color, &color, sizeof(t_color));
	find_square_side_vecs(new);
	return (new);
}

t_obj	*creat_tr(t_vec pt, t_vec pt2, t_vec pt3, t_color color)
{
	t_obj	*new;

	if (!(new = malloc(sizeof(t_obj))))
	{
		ft_printf("Failed to malloc triangle.\n");
		exit(EXIT_FAILURE);
	}
	new->id = TRIANGLE;
	new->pt = pt;
	new->pt2 = pt2;
	new->pt3 = pt3;
	ft_memcpy(&new->color, &color, sizeof(t_color));
	new->ori = normalize(vec_cross(vec_sub(new->pt2,
		new->pt), vec_sub(new->pt3, new->pt)));
	return (new);
}
