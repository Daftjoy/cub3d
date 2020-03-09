/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:00:40 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/09 20:25:23 by antmarti         ###   ########.fr       */
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

	i = -1;
	while (line[++i])
	{
		cub->map[j][i] = line[i] - '0';
		if (line[i] == '2')
		{
			cub->spritex[n] = j;
			cub->spritey[n] = i;
			n++;
		}
		if (line[i] == 'W' || line[i] == 'N' ||
		line[i] == 'S' || line[i] == 'E')
		{
			cub->posx = (double)j + 0.51;
			cub->posy = (double)i + 0.51;
			cub->orientation = line[i];
			cub->map[j][i] = cub->counter++ ? 0 : 0;
		}
	}
	i--;
	while (++i < cub->map_w)
		cub->map[j][i] = ' ' - '0';
	return (n);
}

void	ft_map_size(t_cub *cub)
{
	int	j;

	j = 0;
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
		if (line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'))
			n = ft_loop3(cub, line, n, &j);
		free(line);
	}
	if (line[0] >= '0' && line[0] <= '9')
		ft_loop2(cub, line, j, n);
	free(line);
}

void	ft_resolution(t_cub *cub, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (cub->screenwidth == 0)
		{
			if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
				cub->screenwidth = ft_atoi(&(line[i]));
			while (line[i] >= '0' && line[i] <= '9')
				i++;
		}
		else if (cub->screenheight == 0)
		{
			if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
				cub->screenheight = ft_atoi(&(line[i]));
		}
		if (line[i])
			i++;
	}
}
