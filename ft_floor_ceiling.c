/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:09:23 by agianico          #+#    #+#             */
/*   Updated: 2020/02/28 17:20:58 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_floor(t_cub *cub, int x, int y)
{
	while (x < cub->screenwidth)
	{
		cub->cellx = (int)cub->floorx;
		cub->celly = (int)cub->floory;
		cub->tx = (int)(cub->textwidth * (cub->floorx - cub->cellx))
		& (cub->textwidth - 1);
		cub->ty = (int)(cub->textheight * (cub->floory - cub->celly))
		& (cub->textheight - 1);
		cub->floorx += cub->floorstepx;
		cub->floory += cub->floorstepy;
		cub->img_info[y * cub->screenwidth + x] = cub->texture[6]
		[cub->textheight * cub->tx + cub->ty];
		x++;
	}
}

void	ft_floor_ceiling(t_cub *cub)
{
	int		y;
	int		x;

	y = 0;
	while (y < cub->screenheight)
	{
		cub->raydirx0 = cub->dirx - cub->planex;
		cub->raydiry0 = cub->diry - cub->planey;
		cub->raydirx1 = cub->dirx + cub->planex;
		cub->raydiry1 = cub->diry + cub->planey;
		cub->p = y - cub->screenheight / 2;
		cub->posz = 0.5 * cub->screenheight;
		cub->rowdistance = cub->posz / cub->p;
		cub->floorstepx = cub->rowdistance * (cub->raydirx1 - cub->raydirx0)
		/ cub->screenwidth;
		cub->floorstepy = cub->rowdistance * (cub->raydiry1 - cub->raydiry0)
		/ cub->screenwidth;
		cub->floorx = cub->posx + cub->rowdistance * cub->raydirx0;
		cub->floory = cub->posy + cub->rowdistance * cub->raydiry0;
		x = 0;
		ft_draw_floor(cub, x, y);
		y++;
	}
}
