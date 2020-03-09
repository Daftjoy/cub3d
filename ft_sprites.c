/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:54:16 by agianico          #+#    #+#             */
/*   Updated: 2020/03/09 17:03:41 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprites_numb_and_order(t_cub *cub, int x, double temp)
{
	while (x < cub->sprites_numb)
	{
		cub->spriteorder[x] = x;
		cub->spritedistance[x] = ((cub->posx - cub->spritex[x]) *
		(cub->posx - cub->spritex[x])
		+ (cub->posy - cub->spritey[x]) * (cub->posy - cub->spritey[x]));
		x++;
	}
	x = 0;
	while (x < (cub->sprites_numb - 1))
	{
		if (cub->spritedistance[x] < cub->spritedistance[x + 1])
		{
			temp = cub->spriteorder[x];
			cub->spriteorder[x] = cub->spriteorder[x + 1];
			cub->spriteorder[x + 1] = temp;
			temp = cub->spritedistance[x];
			cub->spritedistance[x] = cub->spritedistance[x + 1];
			cub->spritedistance[x + 1] = temp;
			x = 0;
		}
		else
			x++;
	}
}

void	draw_sprites(t_cub *cub)
{
	cub->texx2 = (int)(256 * (cub->stripe - (-cub->spritewidth
	/ 2 + cub->spritescreenx))
	* cub->textwidth / cub->spritewidth) / 256;
	if (cub->transformy > 0 && cub->stripe > 0 && cub->stripe
	< cub->screenwidth && cub->transformy < cub->zbuffer[cub->stripe])
	{
		cub->y_sprite = cub->drawstarty;
		while (cub->y_sprite < cub->drawendy)
		{
			cub->d_sprite = (cub->y_sprite) * 256 -
			cub->screenheight * 128 + cub->spriteheight * 128;
			cub->texy2 = ((cub->d_sprite * cub->textheight)
			/ cub->spriteheight) / 256;
			if (cub->texture[4][cub->textwidth * cub->texy2 +
			cub->texx2] != 0)
				cub->img_info[cub->y_sprite * cub->screenwidth +
				cub->stripe] = cub->texture[4]
				[cub->textwidth * cub->texy2 + cub->texx2];
			cub->y_sprite++;
		}
	}
}

void	sprites_first_part(t_cub *cub, int x)
{
	cub->spriteposx = cub->spritex[cub->spriteorder[x]] - cub->posx + 0.5;
	cub->spriteposy = cub->spritey[cub->spriteorder[x]] - cub->posy + 0.5;
	cub->invdet = 1.0 / (cub->planex * cub->diry - cub->dirx * cub->planey);
	cub->transformx = cub->invdet *
	(cub->diry * cub->spriteposx - cub->dirx * cub->spriteposy);
	cub->transformy = cub->invdet *
	(-cub->planey * cub->spriteposx + cub->planex * cub->spriteposy);
	cub->spritescreenx = (int)(cub->screenwidth / 2 *
	(1 + cub->transformx / cub->transformy));
	cub->spriteheight = fabs((int)cub->screenheight / cub->transformy);
	cub->drawstarty = -cub->spriteheight / 2 + cub->screenheight / 2;
	if (cub->drawstarty < 0)
		cub->drawstarty = 0;
	cub->drawendy = cub->spriteheight / 2 + cub->screenheight / 2;
	if (cub->drawendy >= cub->screenheight)
		cub->drawendy = cub->screenheight - 1;
	cub->spritewidth = fabs((int)cub->screenheight / cub->transformy);
	cub->drawstartx = -cub->spritewidth / 2 + cub->spritescreenx;
	if (cub->drawstartx < 0)
		cub->drawstartx = 0;
	cub->drawendx = cub->spritewidth / 2 + cub->spritescreenx;
	if (cub->drawendx >= cub->screenwidth)
		cub->drawendx = cub->screenwidth - 1;
	cub->stripe = cub->drawstartx;
}

void	ft_sprites(t_cub *cub)
{
	int		x;
	double	temp;

	x = 0;
	temp = 0;
	if (!(cub->spriteorder = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	if (!(cub->spritedistance = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	sprites_numb_and_order(cub, x, temp);
	while (x < cub->sprites_numb)
	{
		sprites_first_part(cub, x);
		while (cub->stripe < cub->drawendx)
		{
			draw_sprites(cub);
			cub->stripe++;
		}
		x++;
	}
	free(cub->spriteorder);
	free(cub->spritedistance);
}
