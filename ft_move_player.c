/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:21:34 by agianico          #+#    #+#             */
/*   Updated: 2020/03/01 15:44:02 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player_to_left(t_cub *cub)
{
	cub->olddirx = cub->dirx;
	cub->dirx = cub->dirx * cos(cub->rotspeed) -
	cub->diry * sin(cub->rotspeed);
	cub->diry = cub->olddirx * sin(cub->rotspeed) +
	cub->diry * cos(cub->rotspeed);
	cub->oldplanex = cub->planex;
	cub->planex = cub->planex * cos(cub->rotspeed) -
	cub->planey * sin(cub->rotspeed);
	cub->planey = cub->oldplanex * sin(cub->rotspeed) +
	cub->planey * cos(cub->rotspeed);
}

void	rotate_player_to_right(t_cub *cub)
{
	cub->olddirx = cub->dirx;
	cub->dirx = cub->dirx * cos(-cub->rotspeed) -
	cub->diry * sin(-cub->rotspeed);
	cub->diry = cub->olddirx * sin(-cub->rotspeed) +
	cub->diry * cos(-cub->rotspeed);
	cub->oldplanex = cub->planex;
	cub->planex = cub->planex * cos(-cub->rotspeed) -
	cub->planey * sin(-cub->rotspeed);
	cub->planey = cub->oldplanex * sin(-cub->rotspeed) +
	cub->planey * cos(-cub->rotspeed);
}

void	move_player_to_right(t_cub *cub)
{
	if (cub->map[(int)(cub->posx + cub->planex * cub->movespeed)]
	[(int)cub->posy] != 1)
		cub->posx += cub->planex * cub->movespeed;
	if (cub->map[(int)cub->posx]
	[(int)(cub->posy + cub->planey * cub->movespeed)] != 1)
		cub->posy += cub->planey * cub->movespeed;
}

void	move_player_to_left(t_cub *cub)
{
	if (cub->map[(int)(cub->posx - cub->planex * cub->movespeed)]
	[(int)cub->posy] != 1)
		cub->posx -= cub->planex * cub->movespeed;
	if (cub->map[(int)cub->posx]
	[(int)(cub->posy - cub->planey * cub->movespeed)] != 1)
		cub->posy -= cub->planey * cub->movespeed;
}

int		move_player(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->w == 1)//W
		move_player_forward(cub);
	if (cub->s == 1)//S
		move_player_back(cub);
	if (cub->a == 1)//A
		move_player_to_left(cub);
	if (cub->d == 1)//D
		move_player_to_right(cub);
	if (cub->left == 1)
		rotate_player_to_left(cub);
	if (cub->right == 1)
		rotate_player_to_right(cub);
	ft_view(cub);
	return (0);
}
