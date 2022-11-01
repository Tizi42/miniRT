/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:56:31 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/03 22:56:33 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_sp(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc sphere.", sc);
	sc->obj->id = SPHERE;
	line += 2;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->diameter, sc);
	line = skip_spaces(line);
	line = atoi_checker(line, sc);
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}

void	parse_pl(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc plane.", sc);
	sc->obj->id = PLANE;
	line += 2;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_orient(line, &sc->obj->ori, sc);
	line = skip_spaces(line);
	line = atoi_checker(line, sc);
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}

void	parse_sq(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc square.", sc);
	sc->obj->id = SQUARE;
	line += 2;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_orient(line, &sc->obj->ori, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->diameter, sc);
	line = skip_spaces(line);
	line = atoi_color(line, &sc->obj->color, sc);
	find_square_side_vecs(sc->obj);
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}

void	parse_cy(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc cylinder.", sc);
	sc->obj->id = CYLINDER;
	line += 2;
	sc->obj->hollow = *(line++) == 'h' ? 1 : 0;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_orient(line, &sc->obj->ori, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->diameter, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->height, sc);
	line = skip_spaces(line);
	line = atoi_checker(line, sc);
	sc->obj->pt2 = vec_add(sc->obj->pt,
					vec_mul(sc->obj->ori, sc->obj->height));
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}

void	parse_tr(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc triangle", sc);
	sc->obj->id = TRIANGLE;
	line += 2;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt2, sc);
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt3, sc);
	line = skip_spaces(line);
	line = atoi_color(line, &sc->obj->color, sc);
	sc->obj->ori = normalize(vec_cross(vec_sub(sc->obj->pt2,
		sc->obj->pt), vec_sub(sc->obj->pt3, sc->obj->pt)));
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}
