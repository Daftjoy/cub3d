/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:38 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/09 20:42:53 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_read_map3(t_cub *cub, char *line, int i)
{
	if (line[i] == 'R')
		ft_resolution(cub, line);
	else if (line[i] == 'N' && line[i + 1] == 'O'
	&& ft_path_duplicate(cub, cub->path_no))
		cub->path_no = ft_path(&(line[i + 2]));
	else if (line[i] == 'S' && line[i + 1] == 'O'
	&& ft_path_duplicate(cub, cub->path_so))
		cub->path_so = ft_path(&(line[i + 2]));
	else if (line[i] == 'W' && line[i + 1] == 'E'
	&& ft_path_duplicate(cub, cub->path_we))
		cub->path_we = ft_path(&(line[i + 2]));
	else if (line[i] == 'E' && line[i + 1] == 'A'
	&& ft_path_duplicate(cub, cub->path_ea))
		cub->path_ea = ft_path(&(line[i + 2]));
	else if (line[i] == 'S' && line[i + 1] == ' '
	&& ft_path_duplicate(cub, cub->path_sprite))
		cub->path_sprite = ft_path(&(line[i + 2]));
	else if (line[i] == 'F' && line[i + 1] == ' '
	&& ft_color_duplicate(cub, cub->floor_color))
		ft_color(&(line[i + 1]), &cub->floor_color, cub);
	else if (line[i] == 'C' && line[i + 1] == ' '
	&& ft_color_duplicate(cub, cub->ceiling_color))
		ft_color(&(line[i + 1]), &cub->ceiling_color, cub);
	else if (line[i])
		ft_read_map4(cub, line, i);
}

void	ft_read_map4(t_cub *cub, char *line, int i)
{
	if (line[i] == '1')
	{
		ft_loop(cub, line);
		if (cub->map_w < ft_strlen(line))
			cub->map_w = ft_strlen(line);
	}
	else if (line[i])
		ft_error_2(cub, 0);
}
