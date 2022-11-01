/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objets2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:31:55 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/30 14:31:56 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_cu(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc cube.", sc);
	sc->obj->id = CUBE;
	line += 2;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->diameter, sc);
	line = skip_spaces(line);
	line = atoi_color(line, &sc->obj->color, sc);
	sc->obj->ori = get_vec(0, 1, 0);
	sc->obj->pt3 = get_vec(0, 0, 1);
	sc->obj->pt2 = get_vec(1, 0, 0);
	sc->obj->list = NULL;
	set_cu(sc->obj);
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}

void	parse_py(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc pyramid.", sc);
	sc->obj->id = PYRAMID;
	line += 2;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->diameter, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->height, sc);
	line = skip_spaces(line);
	line = atoi_color(line, &sc->obj->color, sc);
	sc->obj->ori = get_vec(0, -1, 0);
	sc->obj->pt3 = get_vec(0, 0, 1);
	sc->obj->pt2 = get_vec(1, 0, 0);
	sc->obj->list = NULL;
	set_py(sc->obj);
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}

void	parse_disk(t_scene *sc, char *line)
{
	if (!(sc->obj = malloc(sizeof(t_obj))))
		error_handle("Failed to malloc disk.", sc);
	sc->obj->id = DISK;
	line += 2;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->obj->pt, sc);
	line = skip_spaces(line);
	line = atoi_orient(line, &sc->obj->ori, sc);
	line = skip_spaces(line);
	line = atoi_double(line, &sc->obj->diameter, sc);
	line = skip_spaces(line);
	line = atoi_color(line, &sc->obj->color, sc);
	ft_lstadd_front(&sc->list_objs, ft_lstnew(sc->obj));
}

void	parse_background_color(t_scene *sc, char *line)
{
	line++;
	line = skip_spaces(line);
	line = atoi_color(line, &sc->background_color, sc);
}

char	*atoi_checker(char *line, t_scene *sc)
{
	if (*line == 'c')
	{
		line++;
		line = skip_spaces(line);
		line = atoi_int(line, &sc->obj->checker.width, sc);
		line = skip_spaces(line);
		line = atoi_int(line, &sc->obj->checker.height, sc);
		line = skip_spaces(line);
		line = atoi_color(line, &sc->obj->checker.color1, sc);
		line = skip_spaces(line);
		line = atoi_color(line, &sc->obj->checker.color2, sc);
		line = skip_spaces(line);
	}
	else
	{
		sc->obj->checker.width = 0;
		line = atoi_color(line, &sc->obj->color, sc);
	}
	return (line);
}
