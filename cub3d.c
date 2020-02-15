/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:36 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/15 18:39:00 by antmarti         ###   ########.fr       */
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

typedef struct 	s_cub
{
	double	posx; // posiciones de inicio del personaje
	double	posy;
	double	dirx; // dirección a la que mira el jugador
	double	diry;
	double	planex; // plano de cámara del jugador -> es perpendicular al de dirección
	double	planey;
	double	time; // frame actual
	double	oldtime; // frame anterior -> la diferencia entre time-oldtime sirve para calcular lo que tienes que moverte cuando se aprieta una tecla
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
} 				t_cub;

typedef struct 	s_ml
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
}				t_ml;

#endif
#endif
#endif
#endif
int deal_key(int key, void *param)
{
	t_cub *cub;
	cub = (t_cub *) param;
	if (key == 0)
	{
		cub->posx -= 1;
		write(1,"G", 1);
	}
	if (key == 1)
		cub->posy += 1;
	if (key == 2)
		cub->posx +=1;
	if	(key == 13)
		cub->posy -= 1;
	return (0);
}
int main()
{
	t_cub	*cub;
	t_ml	*ml;
	int x;
	int y;
	int worldMap[mapWidth][mapHeight]=
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
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	if (!(cub = malloc(sizeof(t_cub))))
		return (0);
	if (!(ml = malloc(sizeof(t_ml))))
		return (0);
	cub->posx = 22;
	cub->posy = 12;
	cub->dirx = -1;
	cub->diry = 0;
	cub->planex = 0;
	cub->planey = 0.66;
	cub->time = 0;
	cub->oldtime = 0;
	
	ml->mlx_ptr = mlx_init();
	ml->win_ptr = mlx_new_window(ml->mlx_ptr, screenWidth, screenHeight, "Marisco");
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
			if (worldMap[cub->mapx][cub->mapy] > 0)
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
		mlx_pixel_put(ml->mlx_ptr, ml->win_ptr, x, y, 0xFFFFFF);
		y++;
	}
	x++;
	}
	mlx_key_hook(ml->win_ptr, deal_key, (void *)cub);
	mlx_loop(ml->mlx_ptr);
	return (0);
}