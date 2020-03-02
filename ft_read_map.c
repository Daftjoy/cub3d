/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:00:40 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/02 20:25:43 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_loop(t_cub *cub, char *line)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == '2')
			cub->sprites_numb++;
		i++;
	}
	cub->map_h++;
}

int		ft_loop2(t_cub *cub, char *line, int j, int n)
{
	int i;

	i = 0;
	while (line[i])
	{
		cub->map[j][i] = line[i] - '0';
		if (line[i] == '2')
		{
			cub->spritex[n] = i;
			cub->spritey[n] = j;
			n++;
		}
		if (line[i] == 'W' || line[i] == 'N' ||
		line[i] == 'S' || line[i] == 'E')
		{
			cub->posx = j;
			cub->posy = i;
			cub->orientation = line[i];
			cub->map[j][i] = 0;
		}
		i++;
	}
	return (n);
}

void	ft_map_size(t_cub *cub, char *map_path, char *line)
{
	int	j;
	int fd;

	j = 0;
	fd = open(map_path, O_RDONLY);
	while (get_next_line(&line, fd) > 0)
		if (line[0] >= '0' && line[0] <= '9')
			ft_loop(cub, line);
	if (line[0] >= '0' && line[0] <= '9')
		ft_loop(cub, line);
	cub->map_w = ft_strlen(line);
	free(line);
	line = NULL;
	if (!(cub->map = malloc(sizeof(int *) * cub->map_h)))
		return ;
	while (j < cub->map_h)
	{
		if (!(cub->map[j] = malloc(sizeof(int) * cub->map_w)))
			return ;
		j++;
	}
}

void	ft_map(t_cub *cub, char *line, char *map_path)
{
	int i;
	int fd;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	fd = open(map_path, O_RDONLY);
	while (get_next_line(&line, fd) > 0)
	{
		if (line[0] >= '0' && line[0] <= '9')
		{
			n = ft_loop2(cub, line, j, n);
			j++;
		}
	}
	if (line[0] >= '0' && line[0] <= '9')
		ft_loop2(cub, line, j, n);
}

void	ft_resolution(t_cub *cub, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (cub->screenwidth == 0)
			while (line[i] >= '0' && line[i] <= '9')
			{
				cub->screenwidth = cub->screenwidth * 10 +
				(line[i] - '0');
				i++;
			}
		else if (cub->screenheight == 0)
			while (line[i] >= '0' && line[i] <= '9')
			{
				cub->screenheight = cub->screenheight * 10 +
				(line[i] - '0');
				i++;
			}
		if (line[i])
			i++;
	}
}
