/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:21:34 by agianico          #+#    #+#             */
/*   Updated: 2020/02/28 17:22:29 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move_player(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->w == 1)//W
	{
		if (cub->map[(int)(cub->posx + cub->dirx * cub->movespeed)][(int)cub->posy] != 1)
			cub->posx += cub->dirx * cub->movespeed;
		if (cub->map[(int)cub->posx][(int)(cub->posy + cub->diry * cub->movespeed)] != 1)
			cub->posy += cub->diry * cub->movespeed;
	}
	if (cub->s == 1)//S
	{
		if (cub->map[(int)(cub->posx - cub->dirx * cub->movespeed)][(int)cub->posy] != 1)
			cub->posx -= cub->dirx * cub->movespeed;
		if (cub->map[(int)cub->posx][(int)(cub->posy - cub->diry * cub->movespeed)] != 1)
			cub->posy -=cub->diry * cub->movespeed;
	}
	if (cub->d == 1)//D
	{
		if (cub->map[(int)(cub->posx + cub->planex * cub->movespeed)][(int)cub->posy] != 1)
			cub->posx += cub->planex * cub->movespeed;
		if (cub->map[(int)cub->posx][(int)(cub->posy + cub->planey * cub->movespeed)] != 1)
			cub->posy += cub->planey * cub->movespeed;
	}
	if (cub->a == 1)//A
	{
		if (cub->map[(int)(cub->posx - cub->planex * cub->movespeed)][(int)cub->posy] != 1)
			cub->posx -= cub->planex * cub->movespeed;
		if (cub->map[(int)cub->posx][(int)(cub->posy - cub->planey * cub->movespeed)] != 1)
			cub->posy -= cub->planey * cub->movespeed;
	}
	if (cub->left == 1)
	{
		cub->olddirx = cub->dirx;
		cub->dirx = cub->dirx * cos(cub->rotspeed) - cub->diry * sin(cub->rotspeed);
		cub->diry = cub->olddirx * sin(cub->rotspeed) + cub->diry * cos(cub->rotspeed);
		cub->oldplanex = cub->planex;
		cub->planex = cub->planex * cos(cub->rotspeed) - cub->planey * sin(cub->rotspeed);
		cub->planey = cub->oldplanex * sin(cub->rotspeed) + cub->planey * cos(cub->rotspeed);
	}
	if (cub->right == 1)
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

int		key_pressed(int key, void *param)
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

int		key_released(int key, void *param)
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
