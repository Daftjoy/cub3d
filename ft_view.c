/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:00:27 by agianico          #+#    #+#             */
/*   Updated: 2020/03/09 16:59:51 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_cub *cub)
{
	cub->rotspeed = 0.05;
	cub->movespeed = 0.1;
	cub->img_ptr = mlx_new_image(cub->mlx_ptr,
	cub->screenwidth, cub->screenheight);
	cub->img_info = (int *)mlx_get_data_addr(cub->img_ptr,
	&cub->bpp, &cub->ls, &cub->endian);
}

void	raycasting_init(t_cub *cub, int x, int y, int z)
{
	raycasting_first_part(cub, x);
	raycasting_second_part(cub);
	while (cub->hit == 0)
		raycasting_third_part(cub);
	raycasting_fourth_part(cub, &y);
	cub->step = 1.0 * cub->textheight / cub->lineheight;
	cub->texpos = (cub->drawstart - cub->screenheight
	/ 2 + cub->lineheight / 2) * cub->step;
	while (z < y)
	{
		cub->img_info[z * cub->screenwidth + x] = cub->ceiling_color;
		z++;
	}
	raycasting_fifth_part(cub, y, x);
	z = cub->drawend;
	z = 0;
	cub->zbuffer[x] = cub->perpwalldist;
}

void	ft_view(t_cub *cub)
{
	int		x;
	int		y;
	int		z;
	double	temp;

	x = 0;
	y = 0;
	z = 0;
	temp = 0;
	ft_init(cub);
	ft_floor_ceiling(cub);
	while (x < cub->screenwidth)
	{
		raycasting_init(cub, x, y, z);
		x++;
	}
	ft_sprites(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->img_ptr);
}
