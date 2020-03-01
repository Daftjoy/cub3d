/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:39:01 by agianico          #+#    #+#             */
/*   Updated: 2020/03/01 15:41:43 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_back(t_cub *cub)
{
	if (cub->map[(int)(cub->posx - cub->dirx * cub->movespeed)]
	[(int)cub->posy] != 1)
		cub->posx -= cub->dirx * cub->movespeed;
	if (cub->map[(int)cub->posx]
	[(int)(cub->posy - cub->diry * cub->movespeed)] != 1)
		cub->posy -= cub->diry * cub->movespeed;
}

void	move_player_forward(t_cub *cub)
{
	if (cub->map[(int)(cub->posx + cub->dirx * cub->movespeed)]
	[(int)cub->posy] != 1)
		cub->posx += cub->dirx * cub->movespeed;
	if (cub->map[(int)cub->posx]
	[(int)(cub->posy + cub->diry * cub->movespeed)] != 1)
		cub->posy += cub->diry * cub->movespeed;
}
