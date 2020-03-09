/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:40:26 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/09 19:09:16 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_map_error(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (++j < cub->map_h)
	{
		while (i < cub->map_w)
		{
			if (cub->map[j][i] != -16 && cub->map[j][i] != 1
			&& cub->map[j][i] != 0 && cub->map[j][i] != 2)
				return (0);
			if ((i == 0 || i == (cub->map_w - 1)) && (cub->map[j][i] != 1 &&
			cub->map[j][i] != -16))
				return (0);
			if ((j == 0 || j == (cub->map_h - 1)) &&
			cub->map[j][i] != 1 && cub->map[j][i] != -16)
				return (0);
			if (!ft_map_error_2(cub, i, j))
				return (0);
			i++;
		}
		i = 0;
	}
	return (1);
}

int		ft_map_error_2(t_cub *cub, int i, int j)
{
	if (i != 0 && cub->map[j][i] == -16 &&
	(cub->map[j][i - 1] != -16 && cub->map[j][i - 1] != 1))
		return (0);
	if (j != 0 && cub->map[j][i] == -16 &&
	(cub->map[j - 1][i] != -16 && cub->map[j - 1][i] != 1))
		return (0);
	if (i != 0 && (cub->map[j][i] != 1 && cub->map[j][i] != -16) &&
	cub->map[j][i - 1] == -16)
		return (0);
	if (j != 0 && (cub->map[j][i] != 1 && cub->map[j][i] != -16) &&
	cub->map[j - 1][i] == -16)
		return (0);
	return (1);
}

int		ft_path_duplicate(t_cub *cub, char *path)
{
	if (path)
	{
		write(1, "Duplicated path", 15);
		ft_exit_hook(cub);
		return (0);
	}
	return (1);
}

int		ft_color_duplicate(t_cub *cub, int color)
{
	if (color != 0)
	{
		write(1, "Duplicated color", 16);
		ft_exit_hook(cub);
		return (0);
	}
	return (1);
}

void	ft_path_check(t_cub *cub)
{
	if (cub->screenwidth > 2560)
		cub->screenwidth = 2560;
	if (cub->screenheight > 1440)
		cub->screenheight = 1440;
	if (cub->screenwidth < 0)
		ft_error(cub, 0);
	if (cub->screenheight < 0)
		ft_error(cub, 0);
	if (open(cub->path_no, O_RDONLY) < 0)
		ft_error(cub, 1);
	if (open(cub->path_so, O_RDONLY) < 0)
		ft_error(cub, 1);
	if (open(cub->path_we, O_RDONLY) < 0)
		ft_error(cub, 1);
	if (open(cub->path_ea, O_RDONLY) < 0)
		ft_error(cub, 1);
	if (open(cub->path_sprite, O_RDONLY) < 0)
		ft_error(cub, 1);
}
