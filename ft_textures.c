/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:15:43 by agianico          #+#    #+#             */
/*   Updated: 2020/03/02 21:02:36 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_create_image2(t_cub *cub, int width, int height)
{
	cub->n_text5 = mlx_xpm_file_to_image(cub->mlx_ptr,
	cub->path_sprite, &width, &height);
	cub->n_text_info5 = (int *)mlx_get_data_addr(cub->n_text5,
	&cub->bpp, &cub->ls, &cub->endian);
	cub->n_text6 = mlx_xpm_file_to_image(cub->mlx_ptr,
	"floor.xpm", &width, &height);
	cub->n_text_info6 = (int *)mlx_get_data_addr(cub->n_text6,
	&cub->bpp, &cub->ls, &cub->endian);
}

void	ft_create_image(t_cub *cub)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	cub->n_text = mlx_xpm_file_to_image(cub->mlx_ptr,
	cub->path_so, &width, &height);
	cub->n_text_info = (int *)mlx_get_data_addr(cub->n_text,
	&cub->bpp, &cub->ls, &cub->endian);
	cub->n_text2 = mlx_xpm_file_to_image(cub->mlx_ptr,
	cub->path_no, &width, &height);
	cub->n_text_info2 = (int *)mlx_get_data_addr(cub->n_text2,
	&cub->bpp, &cub->ls, &cub->endian);
	cub->n_text3 = mlx_xpm_file_to_image(cub->mlx_ptr,
	cub->path_we, &width, &height);
	cub->n_text_info3 = (int *)mlx_get_data_addr(cub->n_text3,
	&cub->bpp, &cub->ls, &cub->endian);
	cub->n_text4 = mlx_xpm_file_to_image(cub->mlx_ptr,
	cub->path_ea, &width, &height);
	cub->n_text_info4 = (int *)mlx_get_data_addr(cub->n_text4,
	&cub->bpp, &cub->ls, &cub->endian);
	ft_create_image2(cub, width, height);
}

void	ft_assign_textures(t_cub *cub)
{
	cub->texture[0] = cub->n_text_info;//SO
	cub->texture[1] = cub->n_text_info2;//NO
	cub->texture[2] = cub->n_text_info3;//WE
	cub->texture[3] = cub->n_text_info4;//EA
	cub->texture[4] = cub->n_text_info5;//SPRITE
	cub->texture[5] = cub->n_text_info;//SKY
	cub->texture[6] = cub->n_text_info6;//FLOOR
}

void	ft_textures(t_cub *cub)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = 0;
	y = 0;
	ft_create_image(cub);
	cub->texture = malloc(sizeof(int *) * 8);
	while (i < 7)
	{
		cub->texture[i] = malloc(sizeof(int)
		* cub->textwidth * cub->textheight);
		i++;
	}
	while (x < cub->textwidth)
	{
		y = 0;
		while (y < cub->textheight)
		{
			ft_assign_textures(cub);
			y++;
		}
		x++;
	}
}
