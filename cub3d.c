/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:36 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/26 17:51:25 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_music(void)
{
	system("afplay dust.wav");
	return (0);
}

void	ft_floor_ceiling(t_cub *cub)
{
	int		y;
	int		x;
	//void	*img_ptr;
	//int		*img_info;

	y = 0;
	//cub->img_ptr = mlx_new_image(cub->mlx_ptr, cub->screenwidth, cub->screenheight);
	//cub->img_info = (int *)mlx_get_data_addr(cub->img_ptr, &cub->bpp, &cub->ls, &cub->endian);	
	while(y < cub->screenheight)
	{
		cub->raydirx0 = cub->dirx - cub->planex;
		cub->raydiry0 = cub->diry - cub->planey;
		cub->raydirx1 = cub->dirx + cub->planex;
		cub->raydiry1 = cub->diry + cub->planey;
		cub->p = y - cub->screenheight / 2;
		cub->posz = 0.5 * cub->screenheight;
		cub->rowdistance = cub->posz / cub->p;
		cub->floorstepx = cub->rowdistance * (cub->raydirx1 - cub->raydirx0) / cub->screenwidth;
		cub->floorstepy = cub->rowdistance * (cub->raydiry1 - cub->raydiry0) / cub->screenwidth;
		cub->floorx = cub->posx + cub->rowdistance * cub->raydirx0;
		cub->floory = cub->posy + cub->rowdistance * cub->raydiry0;
		x = 0;
		while (x < cub->screenwidth)
		{
			cub->cellx = (int)cub->floorx;
			cub->celly = (int)cub->floory;
			cub->tx = (int)(textwidth * (cub->floorx - cub->cellx)) & (textwidth - 1);
			cub->ty = (int)(textheight * (cub->floory - cub->celly)) & (textheight - 1);
			cub->floorx += cub->floorstepx;
			cub->floory += cub->floorstepy;
			cub->img_info[y * cub->screenwidth + x]= cub->texture[6][textheight * cub->tx + cub->ty];
			//cub->img_info[ y * * cub->screenwidth) - 1 + x]= cub->texture[3][textheight * cub->tx + cub->ty];
			x++;
		}
		y++;
	}
	//mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	//mlx_destroy_image(cub->mlx_ptr, cub->img_ptr);
}

void	ft_textures(t_cub *cub)
{
	int x;
	int y;
	int i;
	int width;
	int height;
	int		*n_text3;
	int 	*n_text_info3;
	int		*n_text4;
	int 	*n_text_info4;
	int		*n_text5;
	int 	*n_text_info5;
	
	i = 0;
	x = 0;
	y = 0;
	width = 64;
	height = 64;
	cub->n_text = mlx_xpm_file_to_image(cub->mlx_ptr, cub->path_so, &width, &height);
	cub->n_text_info = (int *)mlx_get_data_addr(cub->n_text, &cub->bpp, &cub->ls, &cub->endian);
	cub->n_text2 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->path_no, &width, &height);
	cub->n_text_info2 = (int *)mlx_get_data_addr(cub->n_text2, &cub->bpp, &cub->ls, &cub->endian);
	n_text3 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->path_we, &width, &height);
	n_text_info3 = (int *)mlx_get_data_addr(n_text3, &cub->bpp, &cub->ls, &cub->endian);
	n_text4 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->path_ea, &width, &height);
	n_text_info4 = (int *)mlx_get_data_addr(n_text4, &cub->bpp, &cub->ls, &cub->endian);
	n_text5 = mlx_xpm_file_to_image(cub->mlx_ptr, "barrel.xpm", &width, &height);
	n_text_info5 = (int *)mlx_get_data_addr(n_text5, &cub->bpp, &cub->ls, &cub->endian);
	cub->texture = malloc(sizeof(int *) * 8);
	while(i < 8)
	{
		cub->texture[i] = malloc(sizeof(int)* textwidth * textheight);
		i++;
	}
	while (x < textwidth)
	{
		y = 0;
		while (y < textheight)
		{
			
			//int xorcolor = (x * 256 / textwidth) ^ (y * 256 / textheight); Texturas tutorial
			//int ycolor = y * 256 / textheight;							Texturas tutorial
			//int xycolor = y * 128 / textheight + x * 128 / textwidth;		Texturas tutorial
			//Toda esta verga es para poner nuestras texturas, si descomentas pasa a lo de antes
			cub->texture[0] = cub->n_text_info; //65536 * 254 * (x != y && x != textwidth - y); //flat red texture with black cross			
    		cub->texture[1] = cub->n_text_info2; //xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    		cub->texture[2] = n_text_info3; //256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    		cub->texture[3] = n_text_info4;//xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    		cub->texture[4] = n_text_info5;//256 * xorcolor; //xor green
    		cub->texture[5] = cub->n_text_info;//65536 * 192 * (x % 16 && y % 16); //red bricks
    		cub->texture[6] = cub->n_text_info2;//65536 * ycolor; //red gradient
    		cub->texture[7] = cub->n_text_info;//128 + 256 * 128 + 65536 * 128; //flat grey texture
			y++;
		}
		x++;
	}
}

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
	if (!(cub->zBuffer = malloc(sizeof(double) * cub->screenwidth + 1)))
		return ;
	cub->img_ptr = mlx_new_image(cub->mlx_ptr,cub->screenwidth, cub->screenheight);
	cub->img_info = (int *)mlx_get_data_addr(cub->img_ptr, &cub->bpp, &cub->ls, &cub->endian);
	ft_floor_ceiling(cub);
	while (x <cub->screenwidth)
	{
		cub->camerax = 2 * x / (double)cub->screenwidth - 1;
		cub->raydirx = cub->dirx + cub->planex * cub->camerax;
		cub->raydiry = cub->diry + cub->planey * cub->camerax;
		cub->mapx = (int)cub->posx;
		cub->mapy = (int)cub->posy;
		cub->deltadistx = fabs(1 / cub->raydirx);
		cub->deltadisty = fabs(1 / cub->raydiry);
		cub->hit = 0;
		cub->deltadistx = (cub->raydiry == 0) ? 0 : ((cub->raydirx == 0) ? 1 : fabs(1 / cub->raydirx));
		cub->deltadisty = (cub->raydirx == 0) ? 0 : ((cub->raydiry == 0) ? 1 : fabs(1 / cub->raydiry));
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
			if (cub->map[cub->mapx][cub->mapy] > 0)
				cub->hit = 1;
		}
		if (cub->side == 0)
			cub->perpwalldist = (cub->mapx - cub->posx + (1 - cub->stepx) / 2) / cub->raydirx;
		else
			cub->perpwalldist = (cub->mapy - cub->posy + (1 - cub->stepy) / 2) / cub->raydiry;
		cub->lineheight = (int)(cub->screenheight / cub->perpwalldist);
		cub->drawstart = - cub->lineheight / 2 + cub->screenheight / 2 ;
		if (cub->drawstart < 0)
			cub->drawstart = 0;
		cub->drawend = cub->lineheight / 2 + cub->screenheight / 2;
		if (cub->drawend >= cub->screenheight)
			cub->drawend = cub->screenheight -1;
		y = cub->drawstart;
		double	wallx;
		if (cub->side == 0)
			wallx = cub->posy + cub->perpwalldist * cub->raydiry;
		else
			wallx = cub->posx + cub->perpwalldist * cub->raydirx;
		wallx -= floor(wallx);
		int texx = (int)(wallx * (double)textwidth);
		if (cub->side == 0 && cub->raydirx > 0)
			texx = textwidth - texx -1;
		if (cub->side == 1 && cub->raydiry < 0)
			texx = textwidth - texx -1;
		double step = 1.0 * textheight / cub->lineheight;
		double texpos = (cub->drawstart - cub->screenheight / 2 + cub->lineheight / 2) * step; // con 0 debería funcionar igual
		while(z < y)
		{
			cub->img_info[z *cub->screenwidth + x] = 0x99FFFF;
			z++;
		}
		while (y < cub->drawend)
		{
			int texy = (int)texpos & (textheight - 1);
			texpos +=step;
			if(cub->side == 1 && cub->mapy > cub->posy)
				cub->img_info[y *cub->screenwidth + x] = 0x926521;//cub->texture[2][textheight * texy + texx];
			else if(cub->side == 1 && cub->mapy < cub->posy)
				cub->img_info[y *cub->screenwidth + x] = cub->texture[3][textheight * texy + texx];
			else if(cub->side == 0 && cub->mapx > cub->posx)
				cub->img_info[y *cub->screenwidth + x] = cub->texture[0][textheight * texy + texx];
			else
				cub->img_info[y *cub->screenwidth + x] = cub->texture[1][textheight * texy + texx];
			y++;
		}
		/*z = cub->drawend;
		while(z < cub->screenheight)
		{
			cub->img_info[z *cub->screenwidth + x] = 0x926521;
			z++;
		}*/
		z = 0;
		cub->zBuffer[x] = cub->perpwalldist;
		x++;
	}
	x = 0;
	if (!(cub->spritex = malloc(sizeof(double) * 4)))
		return ;
	if (!(cub->spritey = malloc(sizeof(double) * 4)))
		return ;
	if (!(cub->spriteorder = malloc(sizeof(double) * 4)))
		return ;
	if (!(cub->spritedistance = malloc(sizeof(double) * 4)))
		return ;
	cub->spritex[0] = 5;
	cub->spritey[0] = 5;
	cub->spritex[1] = 3;
	cub->spritey[1] = 5;	
	cub->spritex[2] = 5;
	cub->spritey[2] = 3;
	cub->spritex[3] = 3;
	cub->spritey[3] = 3;
	while (x < 4)
	{
		cub->spriteorder[x] = x;
		cub->spritedistance[x] = ((cub->posx - cub->spritex[x]) * (cub->posx - cub->spritex[x]) + (cub->posy - cub->spritey[x]) * (cub->posy - cub->spritey[x]));
		x++;
	}
	x = 0;
	while (x < 3)
	{
		if (cub->spritedistance[x] < cub->spritedistance[x+1])
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
	while (x < 4)
	{
		cub->spriteposx = cub->spritex[cub->spriteorder[x]] - cub->posx;
		cub->spriteposy = cub->spritey[cub->spriteorder[x]] - cub->posy;
		cub->invdet = 1.0 / (cub->planex * cub->diry - cub->dirx * cub->planey);
		cub->transformx = cub->invdet * (cub->diry * cub->spriteposx - cub->dirx * cub->spriteposy);
		cub->transformy = cub->invdet * (-cub->planey * cub->spriteposx + cub->planex * cub->spriteposy);
		cub->spritescreenx = (int)(cub->screenwidth/2 * (1 + cub->transformx / cub->transformy));
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
		int stripe = cub->drawstartx;
		while (stripe < cub->drawendx)
		{
			int texx = (int)(256 * (stripe - (-cub->spritewidth / 2 + cub->spritescreenx)) * textwidth / cub->spritewidth) / 256;
			if (cub->transformy > 0 && stripe > 0 && stripe < cub->screenwidth && cub->transformy < cub->zBuffer[stripe])
			{
				int y = cub->drawstarty;
				while (y < cub->drawendy)
				{
					int d = (y) * 256 - cub->screenheight * 128 + cub->spriteheight * 128;
					int texy = ((d * textheight) / cub->spriteheight) / 256;
					if (cub->texture[4][textwidth * texy + texx] != 0)
						cub->img_info[y * cub->screenwidth + stripe] =  cub->texture[4][textwidth * texy + texx]; //cub->texture[6][textwidth * texy + texx];
					y++;
				}
			}
			stripe++;
		}	
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->img_ptr);
}
int exit_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	free(cub);
	system("killall afplay");
	exit(0);
	return(0);
}
int move_player(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if	(cub->w == 1)//W
	{
		if (!cub->map[(int)(cub->posx + cub->dirx * cub->movespeed)][(int)cub->posy])
			cub->posx += cub->dirx * cub->movespeed;
		if (!cub->map[(int)cub->posx][(int)(cub->posy + cub->diry * cub->movespeed)])
			cub->posy += cub->diry * cub->movespeed;
	}
	if (cub->s == 1)//S
	{
		if (!cub->map[(int)(cub->posx - cub->dirx * cub->movespeed)][(int)cub->posy])
			cub->posx -= cub->dirx * cub->movespeed;
		if (!cub->map[(int)cub->posx][(int)(cub->posy - cub->diry * cub->movespeed)])
			cub->posy -=cub->diry * cub->movespeed;
	}
	if	(cub->d == 1)//D
	{
		if (!cub->map[(int)(cub->posx + cub->planex * cub->movespeed)][(int)cub->posy])
			cub->posx += cub->planex * cub->movespeed;
		if (!cub->map[(int)cub->posx][(int)(cub->posy + cub->planey * cub->movespeed)])
			cub->posy += cub->planey * cub->movespeed;
	}
	if	(cub->a == 1)//A
	{
		if (!cub->map[(int)(cub->posx - cub->planex * cub->movespeed)][(int)cub->posy])
			cub->posx -= cub->planex * cub->movespeed;
		if (!cub->map[(int)cub->posx][(int)(cub->posy - cub->planey * cub->movespeed)])
			cub->posy -= cub->planey * cub->movespeed;
	}
	if	(cub->left == 1)
	{
		cub->olddirx = cub->dirx;
		cub->dirx = cub->dirx * cos(cub->rotspeed) - cub->diry * sin(cub->rotspeed);
		cub->diry = cub->olddirx * sin(cub->rotspeed) + cub->diry * cos(cub->rotspeed);
		cub->oldplanex = cub->planex;
		cub->planex = cub->planex * cos(cub->rotspeed) - cub->planey * sin(cub->rotspeed);
		cub->planey = cub->oldplanex * sin(cub->rotspeed) + cub->planey * cos(cub->rotspeed);
	}
	if	(cub->right == 1)
	{
		cub->olddirx = cub->dirx;
		cub->dirx = cub->dirx * cos(-cub->rotspeed) - cub->diry * sin(-cub->rotspeed);
		cub->diry = cub->olddirx * sin(-cub->rotspeed) + cub->diry * cos(-cub->rotspeed);
		cub->oldplanex = cub->planex;
		cub->planex = cub->planex * cos(-cub->rotspeed) - cub->planey * sin(-cub->rotspeed);
		cub->planey = cub->oldplanex * sin(-cub->rotspeed) + cub->planey * cos(-cub->rotspeed);
	}
	ft_view(cub);
	return (0);
}


int key_pressed(int key, void *param)
{
	t_cub	*cub;
	cub = (t_cub *)param;
	
	if (key == 0)
		cub->a = 1;
	if (key == 1)
		cub->s = 1;
	if (key == 2)
		cub->d = 1;
	if (key == 13)
		cub->w = 1;
	if (key == 124)
		cub->right = 1;
	if (key == 123)
		cub->left = 1;
	if (key == 53)
	{
		system("killall afplay");
		free(cub);
		exit(0);
	}
	return (0);
}

int key_released(int key, void *param)
{
	t_cub	*cub;
	cub = (t_cub *)param;
	
	if (key == 0)
		cub->a = 0;
	if (key == 1)
		cub->s = 0;
	if (key == 2)
		cub->d = 0;
	if (key == 13)
		cub->w = 0;
	if (key == 124)
		cub->right = 0;
	if (key == 123)
		cub->left = 0;
	return (0);
}

int main(int argc, char **argv)
{
	t_cub	*cub;
	int x;
	
	x = 0;
	if (argc == 2 || argc == 3)
	{
		if (!(cub = malloc(sizeof(t_cub))))
			return (0);
		ft_read_map(cub, argv[1]);
		cub->posx = 2.0;
		cub->posy = 3.5;
		cub->dirx = -1.0;
		cub->diry = 0.0;
		cub->planex = 0.0;
		cub->planey = 0.66;
		cub->mlx_ptr = mlx_init();
		cub->win_ptr = mlx_new_window(cub->mlx_ptr,cub->screenwidth, cub->screenheight, "Marisco");
		cub->rotspeed  =  0.05;
		cub->movespeed = 0.1;
		system("afplay rec.mp3 &");
		ft_textures(cub);
		ft_view(cub);
		mlx_hook(cub->win_ptr, 2, 0, key_pressed, (void *)cub);
		mlx_hook(cub->win_ptr, 3, 0, key_released, (void *)cub);
		mlx_loop_hook(cub->mlx_ptr, move_player, (void *)cub);
		mlx_hook(cub->win_ptr, 17, 0, exit_hook, (void *)cub);
		mlx_loop(cub->mlx_ptr);
	}
	return (0);
}