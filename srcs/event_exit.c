/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:15:34 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/16 11:15:38 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	error_handle(char *msg, t_scene *sc)
{
	ft_printf(RED "Error\n%s\n" RESET, msg);
	free_exit(sc, EXIT_FAILURE);
}

void	free_exit(t_scene *sc, int exit_id)
{
	if (sc)
	{
		if (sc->name)
			free(sc->name);
		if (!sc->list_cams && sc->cam)
			free(sc->cam);
		if (!sc->list_objs && sc->obj)
			free(sc->obj);
		if (!sc->list_lights && sc->light)
			free(sc->light);
		free_img(sc);
		free_lst_py_cu(sc);
		ft_lstclear(&sc->list_cams, free);
		ft_lstclear(&sc->list_objs, free);
		ft_lstclear(&sc->list_lights, free);
		if (sc->win_ptr)
			mlx_destroy_window(sc->mlx_ptr, sc->win_ptr);
		if (sc->mlx_ptr)
			free(sc->mlx_ptr);
		free(sc);
	}
	exit(exit_id);
}

void	free_lst_py_cu(t_scene *sc)
{
	t_list *lst;

	lst = sc->list_objs;
	while (lst)
	{
		sc->obj = lst->content;
		if (sc->obj->id == PYRAMID || sc->obj->id == CUBE)
			ft_lstclear(&sc->obj->list, free);
		lst = lst->next;
	}
}

void	free_img(t_scene *sc)
{
	t_list *lst;

	lst = sc->list_cams;
	while (lst)
	{
		sc->cam = lst->content;
		if (sc->cam->img.ptr)
			mlx_destroy_image(sc->mlx_ptr, sc->cam->img.ptr);
		lst = lst->next;
	}
}

int		exit_hook(t_scene *sc)
{
	free_exit(sc, EXIT_SUCCESS);
	return (0);
}
