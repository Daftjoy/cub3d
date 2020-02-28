/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:36 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/28 17:55:03 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_view(t_cub *cub)
{
	int	x;
	int	y;
	int	z;
	double temp;

	x = 0;
	y = 0;
	z = 0;
	temp = 0;
	if (!(cub->zbuffer = malloc(sizeof(double) * cub->screenwidth + 1)))
		return ;
	cub->img_ptr = mlx_new_image(cub->mlx_ptr,
	cub->screenwidth, cub->screenheight);
	cub->img_info = (int *)mlx_get_data_addr(cub->img_ptr,
	&cub->bpp, &cub->ls, &cub->endian);
	ft_floor_ceiling(cub);
	while (x < cub->screenwidth)
	{
		cub->camerax = 2 * x / (double)cub->screenwidth - 1;
		cub->raydirx = cub->dirx + cub->planex * cub->camerax;
		cub->raydiry = cub->diry + cub->planey * cub->camerax;
		cub->mapx = (int)cub->posx;
		cub->mapy = (int)cub->posy;
		cub->deltadistx = fabs(1 / cub->raydirx);
		cub->deltadisty = fabs(1 / cub->raydiry);
		cub->hit = 0;
		cub->deltadistx = (cub->raydiry == 0) ? 0 : ((cub->raydirx == 0)
		? 1 : fabs(1 / cub->raydirx));
		cub->deltadisty = (cub->raydirx == 0) ? 0 : ((cub->raydiry == 0)
		? 1 : fabs(1 / cub->raydiry));
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
		while (cub->hit == 0)
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
		y = cub->drawstart;
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
		cub->step = 1.0 * cub->textheight / cub->lineheight;
		cub->texpos = (cub->drawstart - cub->screenheight
		/ 2 + cub->lineheight / 2) * cub->step;
		while (z < y)
		{
			cub->img_info[z * cub->screenwidth + x] = cub->ceiling_color;
			z++;
		}
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
		z = cub->drawend;
		while (z < cub->screenheight)
		{
			cub->img_info[z * cub->screenwidth + x] = cub->floor_color;
			z++;
		}
		z = 0;
		cub->zbuffer[x] = cub->perpwalldist;
		x++;
	}
	x = 0;
	if (!(cub->spriteorder = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	if (!(cub->spritedistance = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
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
	x = 0;
	while (x < cub->sprites_numb)
	{
		cub->spriteposx = cub->spritex[cub->spriteorder[x]] - cub->posx;
		cub->spriteposy = cub->spritey[cub->spriteorder[x]] - cub->posy;
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
		while (cub->stripe < cub->drawendx)
		{
			cub->texx2 = (int)(256 * (cub->stripe - (-cub->spritewidth /
			2 + cub->spritescreenx)) * cub->textwidth / cub->spritewidth) / 256;
			if (cub->transformy > 0 && cub->stripe > 0 && cub->stripe
			< cub->screenwidth && cub->transformy < cub->zbuffer[cub->stripe])
			{
				cub->y_sprite = cub->drawstarty;
				while (cub->y_sprite < cub->drawendy)
				{
					cub->d_sprite = (cub->y_sprite) * 256 -
					cub->screenheight * 128 + cub->spriteheight * 128;
					cub->texy2 = ((cub->d_sprite * cub->textheight) /
					cub->spriteheight) / 256;
					if (cub->texture[4][cub->textwidth * cub->texy + cub->texx]
					!= 0)
						cub->img_info[cub->y_sprite * cub->screenwidth +
						cub->stripe] = cub->texture[4]
						[cub->textwidth * cub->texy + cub->texx];
					cub->y_sprite++;
				}
			}
			cub->stripe++;
		}
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->img_ptr);
}

int		ft_exit_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	free(cub);
	system("killall afplay");
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc == 2 || argc == 3)
	{
		if (!(cub = malloc(sizeof(t_cub))))
			return (0);
		ft_read_map(cub, argv[1]);
		ft_set_direction(cub);
		cub->textheight = 64;
		cub->textwidth = 64;
		cub->mlx_ptr = mlx_init();
		cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->screenwidth,
		cub->screenheight, "Marisco");
		cub->rotspeed = 0.05;
		cub->movespeed = 0.1;
		system("afplay rec.mp3 &");
		ft_textures(cub);
		ft_view(cub);
		mlx_hook(cub->win_ptr, 2, 0, key_pressed, (void *)cub);
		mlx_hook(cub->win_ptr, 3, 0, key_released, (void *)cub);
		mlx_loop_hook(cub->mlx_ptr, move_player, (void *)cub);
		mlx_hook(cub->win_ptr, 17, 0, ft_exit_hook, (void *)cub);
		mlx_loop(cub->mlx_ptr);
	}
	return (0);
}
