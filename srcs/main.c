/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:40:51 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/03 17:12:07 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_id(t_scene *sc, char *line)
{
	if (line[0] == 'R')
		parse_reso(sc, line);
	else if (line[0] == 'A')
		parse_amb(sc, line);
	else if (line[0] == 'l')
		parse_light(sc, line);
	else if (line[0] == 's' && line[1] == 'p')
		parse_sp(sc, line);
	else if (line[0] == 'p' && line[1] == 'l')
		parse_pl(sc, line);
	else if (line[0] == 's' && line[1] == 'q')
		parse_sq(sc, line);
	else if (line[0] == 'c' && line[1] == 'y')
		parse_cy(sc, line);
	else if (line[0] == 't' && line[1] == 'r')
		parse_tr(sc, line);
	else
		parse_id2(sc, line);
}

void	parse_id2(t_scene *sc, char *line)
{
	if (line[0] == 'c' && line[1] == 'u')
		parse_cu(sc, line);
	else if (line[0] == 'p' && line[1] == 'y')
		parse_py(sc, line);
	else if (line[0] == 'd' && line[1] == 'i')
		parse_disk(sc, line);
	else if (line[0] == 'c')
		parse_cam(sc, line);
	else if (line[0] == 'b')
		parse_background_color(sc, line);
	else
		error_handle("Invalide element identifier.", sc);
}

int		parse_getline(char *file, t_scene *sc)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		error_handle("Failed to open .rt file.", sc);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line[0] != '\0' && line[0] != '#')
			parse_id(sc, line);
		free(line);
	}
	file[ft_strlen(file) - 3] = '\0';
	sc->name = ft_strdup(file);
	close(fd);
	return (0);
}

void	arguments_check(int ac, char **av, t_scene *sc)
{
	if (ac < 2 || ac > 3)
		error_handle("Wrong number of arguments.", sc);
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - 3], ".rt", 3) != 0)
		error_handle("File extension should be .rt.", sc);
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "--save", 6) == 0 ||
			ft_strncmp(av[2], "-save", 5) == 0)
			sc->save = 1;
		else
			error_handle("Invalide argument.\nTo save image: -save.", sc);
	}
	else
		sc->save = 0;
}

int		main(int ac, char **av)
{
	t_scene	*sc;

	if (!(sc = malloc(sizeof(t_scene))))
		error_handle("Failed to malloc for sc", sc);
	init_sc(sc);
	arguments_check(ac, av, sc);
	parse_getline(av[1], sc);
	start_rt(sc);
	return (EXIT_SUCCESS);
}
