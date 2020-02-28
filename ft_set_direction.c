/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:06:56 by agianico          #+#    #+#             */
/*   Updated: 2020/02/28 17:08:04 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_direction_west(t_cub *cub)
{
	cub->dirx = 0.0;
	cub->diry = -1.0;
	cub->planex = -0.66;
	cub->planey = 0.0;
}

void	ft_set_direction(t_cub *cub)
{
	if (cub->orientation == 'N')
	{
		cub->dirx = -1.0;
		cub->diry = 0.0;
		cub->planex = 0.0;
		cub->planey = 0.66;
	}
	else if (cub->orientation == 'S')
	{
		cub->dirx = 1.0;
		cub->diry = 0.0;
		cub->planex = 0.0;
		cub->planey = -0.66;
	}
	else if (cub->orientation == 'E')
	{
		cub->dirx = 0.0;
		cub->diry = 1.0;
		cub->planex = 0.66;
		cub->planey = 0.0;
	}
	else if (cub->orientation == 'W')
		ft_set_direction_west(cub);
}
