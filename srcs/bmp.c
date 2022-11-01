/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:06:52 by tyuan             #+#    #+#             */
/*   Updated: 2020/12/09 12:09:38 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	save_bmp(t_scene *sc)
{
	int		fd;
	t_list	*lst;
	char	*filename;

	lst = sc->list_cams;
	while (lst)
	{
		sc->cam = lst->content;
		filename = get_bmp_file_name(sc->name, sc->cam->id, sc);
		if (!(fd = open(filename, O_RDWR | O_CREAT | O_APPEND | O_EXCL)))
			error_handle("Failed to create '.bmp' file.", sc);
		free(filename);
		bitmap_file_header(fd, *sc);
		bitmap_info_header(fd, *sc);
		bitmap_info_header_2(fd);
		bitmap_pixel_data(fd, *sc);
		ft_printf("Saved bmp image: %s\n", filename);
		lst = lst->next;
	}
	free_exit(sc, EXIT_SUCCESS);
}

void	bitmap_pixel_data(int fd, t_scene sc)
{
	int		x;
	t_image	img;

	img = sc.cam->img;
	if (img.endian == 0)
	{
		while (sc.reso.y-- > 0)
			write(fd, img.add + sc.reso.y * img.line_bytes, sc.reso.x * 4);
	}
	else if (img.endian == 1)
	{
		while (sc.reso.y-- > 0)
		{
			x = 0;
			while (x < sc.reso.x)
			{
				write(fd, img.add + sc.reso.y * img.line_bytes + x * 4 + 3, 1);
				write(fd, img.add + sc.reso.y * img.line_bytes + x * 4 + 2, 1);
				write(fd, img.add + sc.reso.y * img.line_bytes + x * 4 + 1, 1);
				write(fd, img.add + sc.reso.y * img.line_bytes + x * 4, 1);
				x++;
			}
		}
	}
}

void	bitmap_file_header(int fd, t_scene sc)
{
	unsigned int	type;
	unsigned int	size;
	unsigned int	reserved1;
	unsigned int	reserved2;
	unsigned int	offset;

	type = ('M' << 8) + 'B';
	size = 54 + sc.reso.x * sc.reso.y * 4;
	reserved1 = 0;
	reserved2 = 0;
	offset = 54;
	write(fd, &type, 2);
	write(fd, &size, 4);
	write(fd, &reserved1, 2);
	write(fd, &reserved2, 2);
	write(fd, &offset, 4);
}

void	bitmap_info_header(int fd, t_scene sc)
{
	unsigned int	dib_header_size;
	int				width_px;
	int				height_px;
	unsigned int	num_planes;
	unsigned int	bits_per_pixel;

	dib_header_size = 40;
	width_px = sc.reso.x;
	height_px = sc.reso.y;
	num_planes = 1;
	bits_per_pixel = 32;
	write(fd, &dib_header_size, 4);
	write(fd, &width_px, 4);
	write(fd, &height_px, 4);
	write(fd, &num_planes, 2);
	write(fd, &bits_per_pixel, 2);
}

void	bitmap_info_header_2(int fd)
{
	unsigned int	compression;
	unsigned int	image_size_bytes;
	unsigned int	x_y_resolution_ppm;
	unsigned int	num_colors;
	unsigned int	important_colors;

	compression = 0;
	image_size_bytes = 0;
	x_y_resolution_ppm = 0;
	num_colors = 0;
	important_colors = 0;
	write(fd, &compression, 4);
	write(fd, &image_size_bytes, 4);
	write(fd, &x_y_resolution_ppm, 4);
	write(fd, &x_y_resolution_ppm, 4);
	write(fd, &num_colors, 4);
	write(fd, &important_colors, 4);
}
