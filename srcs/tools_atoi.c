/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:23:22 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/04 10:23:27 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

char	*atoi_int(char *line, int *num, t_scene *sc)
{
	int n;
	int signe;

	n = 0;
	signe = 1;
	if (*line == '-')
	{
		signe = -1;
		line++;
	}
	if (!(*line >= '0' && *line <= '9'))
		error_handle("Unexpected char at the place of int.", sc);
	while (*line >= '0' && *line <= '9')
	{
		n *= 10;
		n += (*line - '0');
		line++;
	}
	*num = signe * n;
	return (line);
}

/*
** .rt file float number precision: 2
*/

char	*atoi_double(char *line, double *fnum, t_scene *sc)
{
	int	interger;
	int	decimals;
	int	signe;

	signe = 1;
	interger = 0;
	decimals = 0;
	if (line[0] == '-' && line[1] == '0')
		signe = -1;
	line = atoi_int(line, &interger, sc);
	if (*line == '.')
	{
		line++;
		line = atoi_int(line, &decimals, sc);
		while (decimals >= 100)
			decimals /= 100;
		if (decimals < 10 && decimals > 0)
			decimals *= 10;
		if (decimals < 0)
			error_handle("Negative sign after point '.'", sc);
	}
	*fnum = signe * (double)(interger + decimals * 0.01);
	return (line);
}

char	*atoi_coordinates(char *line, t_vec *co, t_scene *sc)
{
	line = atoi_double(line, &(co->x), sc);
	line++;
	line = atoi_double(line, &(co->y), sc);
	line++;
	line = atoi_double(line, &(co->z), sc);
	return (line);
}

char	*atoi_color(char *line, t_color *color, t_scene *sc)
{
	line = atoi_int(line, &(color->r), sc);
	line++;
	line = atoi_int(line, &(color->g), sc);
	line++;
	line = atoi_int(line, &(color->b), sc);
	if ((color->r < 0 || color->r > 255) || (color->g < 0 || color->g > 255)
		|| (color->b < 0 || color->b > 255))
		error_handle("Please set a valide color in the range [0, 255].", sc);
	color_to_i(color);
	return (line);
}

char	*atoi_orient(char *line, t_vec *orient, t_scene *sc)
{
	line = atoi_double(line, &(orient->x), sc);
	line++;
	line = atoi_double(line, &(orient->y), sc);
	line++;
	line = atoi_double(line, &(orient->z), sc);
	if (orient->x < -1 || orient->x > 1 ||
			orient->y < -1 || orient->y > 1 || orient->z < -1 || orient->z > 1)
		error_handle("Orientation element should be within [-1, 1].", sc);
	*orient = normalize(*orient);
	return (line);
}
