/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:36 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/18 18:27:17 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#ifndef mapWidth
# define mapWidth 24
#ifndef mapHeight 
# define mapHeight 24
#ifndef screenWidth 
# define screenWidth 800
#ifndef screenHeight 
# define screenHeight 600

#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_ESC 53

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

typedef struct 	s_cub
{
	double	posx; // posiciones de inicio del personaje
	double	posy;
	double	dirx; // dirección a la que mira el jugador
	double	olddirx;
	double	diry;
	double	planex; // plano de cámara del jugador -> es perpendicular al de dirección
	double	oldplanex;
	double	planey;
	double	camerax; // lado de la pantalla en el que te encuentras, siendo  0 = centro, 1 = derecha y -1 = izquierda
	double	raydirx; // dirección rayo de ray casting
	double	raydiry;
	int		mapx; // posición actual del mapa en la que se encuentra el rayo
	int		mapy;
	double	sidedistx; // distancia que el rayo tiene que hacer para avanzar la primera posición en el mapa 
	double	sidedisty;
	double	deltadistx; // distancia que el rayo tiene que hacer para avanzar una posición en el mapa 
	double	deltadisty;
	int		stepx; // dependen de la dirección del rayo y funciona igual 1 o -1
	int		stepy;
	int		hit; // determina si se choca -> 1
	int		side; // es 0 si se ha chocado con un x-side y 1 si ha sido con un y-side
	double	perpwalldist; // largo del rayo
	int		lineheight;
	int		drawstart;
	int		drawend;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int	*img_info;
	int		bpp;
	int		ls;
	int		endian;
	unsigned int *dst;
	double	rotspeed;
	double	movespeed;
	int		a;
	int		s;
	int		w;
	int		d;
	int		right;
	int		left;
} 				t_cub;

#endif
#endif
#endif
#endif

void	ft_view(t_cub *cub)
{
	int	x;
	int	y;
	int worldmp[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	x = 0;
	cub->img_ptr = mlx_new_image(cub->mlx_ptr, screenWidth, screenHeight);
	cub->img_info = (int *)mlx_get_data_addr(cub->img_ptr, &cub->bpp, &cub->ls, &cub->endian);
	while (x < screenWidth)
	{
		cub->camerax = 2 * x / (double)screenWidth - 1;
		cub->raydirx = cub->dirx + cub->planex * cub->camerax;
		cub->raydiry = cub->diry + cub->planey * cub->camerax;
		cub->mapx = (int)cub->posx;
		cub->mapy = (int)cub->posy
;
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
			if (worldmp[cub->mapx][cub->mapy] > 0)
				cub->hit = 1;
		}
	if (cub->side == 0)
		cub->perpwalldist = (cub->mapx - cub->posx + (1 - cub->stepx) / 2) / cub->raydirx;
	else
		cub->perpwalldist = (cub->mapy - cub->posy + (1 - cub->stepy) / 2) / cub->raydiry;
	cub->lineheight = (int)(screenHeight / cub->perpwalldist);
	cub->drawstart = - cub->lineheight / 2 + screenHeight / 2 ;
	if (cub->drawstart < 0)
		cub->drawstart = 0;
	cub->drawend = cub->lineheight / 2 + screenHeight / 2;
	if (cub->drawend >= screenHeight)
		cub->drawend = screenHeight -1;
	y = cub->drawstart;
	while (y < cub->drawend)
	{
		if (worldmp[cub->mapx][cub->mapy] == 2)
			cub->img_info[y * screenWidth + x] = 0xEB0C0C;
		else if (worldmp[cub->mapx][cub->mapy] == 3)
			cub->img_info[y * screenWidth + x] = 0xB605F6;
		else
			cub->img_info[y * screenWidth + x] = 0xFFE500;
		y++;
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
	exit(0);
	return(0);
}
int move_player(void *param)
{
	t_cub	*cub;
		int worldmp[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

	cub = (t_cub *)param;
	if	(cub->w == 1)//W
	{
		if (!worldmp[(int)(cub->posx + cub->dirx * cub->movespeed)][(int)cub->posy])
			cub->posx += cub->dirx * cub->movespeed;
		if (!worldmp[(int)cub->posx][(int)(cub->posy + cub->diry * cub->movespeed)])
			cub->posy += cub->diry * cub->movespeed;
	}
	if (cub->s == 1)//S
	{
		if (!worldmp[(int)(cub->posx - cub->dirx * cub->movespeed)][(int)cub->posy])
			cub->posx -= cub->dirx * cub->movespeed;
		if (!worldmp[(int)cub->posx][(int)(cub->posy - cub->diry * cub->movespeed)])
			cub->posy -=cub->diry * cub->movespeed;
	}
	if	(cub->d == 1)//D
	{
		if (!worldmp[(int)(cub->posx + cub->planex * cub->movespeed)][(int)cub->posy])
			cub->posx += cub->planex * cub->movespeed;
		if (!worldmp[(int)cub->posx][(int)(cub->posy + cub->planey * cub->movespeed)])
			cub->posy += cub->planey * cub->movespeed;
	}
	if	(cub->a == 1)//A
	{
		if (!worldmp[(int)(cub->posx - cub->planex * cub->movespeed)][(int)cub->posy])
			cub->posx -= cub->planex * cub->movespeed;
		if (!worldmp[(int)cub->posx][(int)(cub->posy - cub->planey * cub->movespeed)])
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

int main()
{
	t_cub	*cub;
	int x;

	x = 0;
	if (!(cub = malloc(sizeof(t_cub))))
		return (0);
	cub->posx = 22;
	cub->posy = 12;
	cub->dirx = -1;
	cub->diry = 0;
	cub->planex = 0;
	cub->planey = 0.66;
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, screenWidth, screenHeight, "Marisco");
	cub->rotspeed  =  0.05;
	cub->movespeed = 0.1;
	ft_view(cub);
	mlx_hook(cub->win_ptr, 2, 0, key_pressed, (void *)cub);
	mlx_hook(cub->win_ptr, 3, 0, key_released, (void *)cub);
	mlx_loop_hook(cub->mlx_ptr, move_player, (void *)cub);
	mlx_hook(cub->win_ptr, 17, 0, exit_hook, (void *)cub);
	mlx_loop(cub->mlx_ptr);
	return (0);
}