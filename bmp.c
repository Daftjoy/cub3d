/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:21:40 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/09 19:51:54 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		write_dib_header(int fd, int hex, t_cub *cub)
{
	hex = 0x00000028;
	write(fd, &hex, 4);
	hex = cub->screenwidth;
	write(fd, &hex, 4);
	hex = cub->screenheight;
	write(fd, &hex, 4);
	hex = 0x0001;
	write(fd, &hex, 2);
	hex = 0x0020;
	write(fd, &hex, 2);
	hex = 0x00000000;
	write(fd, &hex, 4);
	hex = cub->screenheight * cub->screenwidth * 4;
	write(fd, &hex, 4);
	hex = 0x00000B13;
	write(fd, &hex, 4);
	hex = 0x00000B13;
	write(fd, &hex, 4);
	hex = 0x00000000;
	write(fd, &hex, 4);
	hex = 0x00000000;
	write(fd, &hex, 4);
}

static int		write_bmp_header(int fd, t_cub *cub)
{
	int hex;

	hex = 0x4D42;
	write(fd, &hex, 2);
	hex = cub->screenwidth * cub->screenwidth * 4 + 54;
	write(fd, &hex, 4);
	hex = 0x00000;
	write(fd, &hex, 2);
	hex = 0x0000;
	write(fd, &hex, 2);
	hex = 0x00000036;
	write(fd, &hex, 4);
	write_dib_header(fd, hex, cub);
	return (1);
}

static int		write_bmp_data(int fd, t_cub *cub)
{
	int	h;
	int	w;
	int	color;

	h = 0;
	while (h < cub->screenheight)
	{
		w = 0;
		while (w < cub->screenwidth)
		{
			color = cub->img_info[cub->screenwidth *
			(cub->screenheight - 1 - h) + w];
			if (write(fd, &color, 4) < 0)
				return (0);
			w++;
		}
		h++;
	}
	return (1);
}

int				save_bmp(t_cub *cub)
{
	int fd;

	ft_view(cub);
	if (!(fd = open("Screenshot.bmp", O_WRONLY | O_TRUNC |
	O_APPEND | O_CREAT, 0666)))
	{
		close(fd);
		ft_exit_hook(cub);
	}
	write_bmp_header(fd, cub);
	if (!(write_bmp_data(fd, cub)))
		ft_exit_hook(cub);
	close(fd);
	return (1);
}
