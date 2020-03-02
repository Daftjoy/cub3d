/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:30:02 by agianico          #+#    #+#             */
/*   Updated: 2020/03/02 21:01:57 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_first_part(t_cub *cub, int x)
{
	cub->camerax = 2 * x / (double)cub->screenwidth - 1;
	cub->raydirx = cub->dirx + cub->planex * cub->camerax;
	cub->raydiry = cub->diry + cub->planey * cub->camerax;
	cub->mapx = (int)cub->posx;
	cub->mapy = (int)cub->posy;
	cub->deltadistx = fabs(1 / cub->raydirx);
	cub->deltadisty = fabs(1 / cub->raydiry);
	cub->hit = 0;
	if (cub->raydiry == 0)
	{
		cub->deltadistx = 0;
		cub->deltadisty = (cub->raydirx == 0) ? 0 : 1;
	}
	else if (cub->raydirx == 0)
	{
		cub->deltadisty = 0;
		cub->deltadistx = 1;
	}
	else
	{
		cub->deltadistx = fabs(1 / cub->raydirx);
		cub->deltadisty = fabs(1 / cub->raydiry);
	}
}

void	raycasting_second_part(t_cub *cub)
{
	if (cub->raydirx < 0)
	{
		cub->stepx = -1;
		cub->sidedistx = (cub->posx - cub->mapx) * cub->deltadistx;
	}
	else
	{
		cub->stepx = 1;
		cub->sidedistx = (cub->mapx + 1.0 - cub->posx) * cub->deltadistx;
	}
	if (cub->raydiry < 0)
	{
		cub->stepy = -1;
		cub->sidedisty = (cub->posy - cub->mapy) * cub->deltadisty;
	}
	else
	{
		cub->stepy = 1;
		cub->sidedisty = (cub->mapy + 1.0 - cub->posy) * cub->deltadisty;
	}
}

void	raycasting_third_part(t_cub *cub)
{
	if (cub->sidedistx < cub->sidedisty)
	{
		cub->sidedistx += cub->deltadistx;
		cub->mapx += cub->stepx;
		cub->side = 0;
	}
	else
	{
		cub->sidedisty += cub->deltadisty;
		cub->mapy += cub->stepy;
		cub->side = 1;
	}
	if (cub->map[cub->mapx][cub->mapy] == 1)
		cub->hit = 1;
}

void	raycasting_fourth_part(t_cub *cub, int *y)
{
	if (cub->side == 0)
		cub->perpwalldist = (cub->mapx - cub->posx +
	(1 - cub->stepx) / 2) / cub->raydirx;
	else
		cub->perpwalldist = (cub->mapy - cub->posy +
	(1 - cub->stepy) / 2) / cub->raydiry;
	cub->lineheight = (int)(cub->screenheight / cub->perpwalldist);
	cub->drawstart = -cub->lineheight / 2 + cub->screenheight / 2;
	if (cub->drawstart < 0)
		cub->drawstart = 0;
	cub->drawend = cub->lineheight / 2 + cub->screenheight / 2;
	if (cub->drawend >= cub->screenheight)
		cub->drawend = cub->screenheight - 1;
	*y = cub->drawstart;
	if (cub->side == 0)
		cub->wallx = cub->posy + cub->perpwalldist * cub->raydiry;
	else
		cub->wallx = cub->posx + cub->perpwalldist * cub->raydirx;
	cub->wallx -= floor(cub->wallx);
	cub->texx = (int)(cub->wallx * (double)cub->textwidth);
	if (cub->side == 0 && cub->raydirx > 0)
		cub->texx = cub->textwidth - cub->texx - 1;
	if (cub->side == 1 && cub->raydiry < 0)
		cub->texx = cub->textwidth - cub->texx - 1;
}

void	raycasting_fifth_part(t_cub *cub, int y, int x)
{
	while (y < cub->drawend)
	{
		cub->texy = (int)cub->texpos & (cub->textheight - 1);
		cub->texpos += cub->step;
		if (cub->side == 1 && cub->mapy > cub->posy)
			cub->img_info[y * cub->screenwidth + x] = cub->texture[3]
		[cub->textheight * cub->texy + cub->texx];
		else if (cub->side == 1 && cub->mapy < cub->posy)
			cub->img_info[y * cub->screenwidth + x] = cub->texture[2]
		[cub->textheight * cub->texy + cub->texx];
		else if (cub->side == 0 && cub->mapx > cub->posx)
			cub->img_info[y * cub->screenwidth + x] = cub->texture[0]
		[cub->textheight * cub->texy + cub->texx];
		else
			cub->img_info[y * cub->screenwidth + x] = cub->texture[1]
		[cub->textheight * cub->texy + cub->texx];
		y++;
	}
}
