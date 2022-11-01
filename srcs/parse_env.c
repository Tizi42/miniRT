/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:38:45 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/03 23:38:55 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

void	parse_reso(t_scene *sc, char *line)
{
	static int ct_reso;

	if (ct_reso == 1)
		error_handle("Resolution can only be declared once in the scene.", sc);
	line++;
	line = skip_spaces(line);
	line = atoi_int(line, &(sc->reso.x), sc);
	line = skip_spaces(line);
	line = atoi_int(line, &(sc->reso.y), sc);
	window_size_check(sc);
	ct_reso = 1;
}

void	parse_amb(t_scene *sc, char *line)
{
	static int ct_amb;

	if (ct_amb == 1)
		error_handle("Amb light can only be declared once in the scene.", sc);
	line++;
	line = skip_spaces(line);
	line = atoi_double(line, &sc->amb.brightness, sc);
	if (sc->amb.brightness < 0 || sc->amb.brightness > 1)
		error_handle("Please set a valide amb light brightness: [0, 1].", sc);
	line = skip_spaces(line);
	line = atoi_color(line, &sc->amb.color, sc);
	sc->amb.i = vec_mul(sc->amb.color.i, sc->amb.brightness);
	ct_amb = 1;
}

void	parse_cam(t_scene *sc, char *line)
{
	static int ct_cam;

	if (!(sc->cam = malloc(sizeof(t_cam))))
		error_handle("Failed to malloc camera.", sc);
	sc->cam->id = ct_cam++;
	sc->cam_count = ct_cam;
	sc->cam->img.ptr = NULL;
	line++;
	line = skip_spaces(line);
	line = atoi_coordinates(line, &sc->cam->pos, sc);
	line = skip_spaces(line);
	line = atoi_orient(line, &sc->cam->dir, sc);
	line = skip_spaces(line);
	line = atoi_int(line, &sc->cam->fov, sc);
	if (sc->cam->fov < 0 || sc->cam->fov > 180)
		error_handle("Please set a valide camera fov: [0, 180].", sc);
	ft_lstadd_front(&sc->list_cams, ft_lstnew(sc->cam));
}

void	parse_light(t_scene *sc, char *line)
{
	if (!(sc->light = malloc(sizeof(t_light))))
		error_handle("Failed to malloc light.", sc);
	line++;
	line = skip_spaces(line);
	if (*line == 'p')
	{
		sc->light->para = 1;
		line++;
		line = skip_spaces(line);
		line = atoi_orient(line, &sc->light->dir, sc);
	}
	else
	{
		sc->light->para = 0;
		line = atoi_coordinates(line, &sc->light->pos, sc);
	}
	line = skip_spaces(line);
	line = atoi_double(line, &sc->light->brightness, sc);
	if (sc->light->brightness < 0 || sc->light->brightness > 1)
		error_handle("Please set a valide light brightness: [0, 1].", sc);
	line = skip_spaces(line);
	line = atoi_color(line, &sc->light->color, sc);
	sc->light->i = vec_mul(sc->light->color.i, sc->light->brightness);
	ft_lstadd_front(&sc->list_lights, ft_lstnew(sc->light));
}
