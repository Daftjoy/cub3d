/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:22:13 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/03 21:37:00 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_path(char *line)
{
	int		j;
	int		i;
	char	*path;

	j = 0;
	i = 2;
	path = malloc(sizeof(char) * 100);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
		{
			path[j] = line[i];
			i++;
			j++;
		}
	}
	path[j] = '\0';
	i = 0;
	return (path);
}

void	ft_color(char *line, int *type)
{
	int		i;
	int		time;
	int		j;
	char	*buff_color;

	time = 0;
	i = 1;
	while (line[i++])
	{
		j = 0;
		if (line[i] >= '0' && line[i] <= '9')
		{
			buff_color = malloc(sizeof(char) * 4);
			while (line[i] >= '0' && line[i] <= '9')
			{
				buff_color[j] = line[i];
				j++;
				i++;
			}
			time++;
			buff_color[j] = '\0';
			ft_rgb_to_hex(buff_color, time, type);
			free(buff_color);
		}
	}
}

void	ft_read_map2(t_cub *cub, char *map_path, char *line)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	while (get_next_line(&line, fd) > 0)
	{
		if (line[0] == 'R')
			ft_resolution(cub, line);
		if (line[0] == 'N' && line[1] == 'O')
			cub->path_no = ft_path(line);
		if (line[0] == 'S' && line[1] == 'O')
			cub->path_so = ft_path(line);
		if (line[0] == 'W' && line[1] == 'E')
			cub->path_we = ft_path(line);
		if (line[0] == 'E' && line[1] == 'A')
			cub->path_ea = ft_path(line);
		if (line[0] == 'S' && line[1] == ' ')
			cub->path_sprite = ft_path(line);
		if (line[0] == 'F' && line[1] == ' ')
			ft_color(line, &cub->floor_color);
		if (line[0] == 'C' && line[1] == ' ')
			ft_color(line, &cub->ceiling_color);
		free(line);
	}
	free(line);
}

void	ft_read_map(t_cub *cub, char *map_path)
{
	char	*line;

	cub->screenheight = 0;
	cub->screenwidth = 0;
	cub->sprites_numb = 0;
	cub->map_h = 0;
	cub->map_w = 0;
	line = NULL;
	ft_map_size(cub, map_path, line);
	if (!(cub->spritex = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	if (!(cub->spritey = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	ft_map(cub, line, map_path);
	free(line);
	line = NULL;
	ft_read_map2(cub, map_path, line);
}

void	ft_rgb_to_hex(char *buff_color, int time, int *pointer)
{
	int		i;
	int		num;
	int		div;

	if (time == 1)
		div = 256 * 256;
	if (time == 2)
		div = 256;
	if (time == 3)
		div = 1;
	i = 0;
	num = 0;
	while (buff_color[i])
	{
		num = num * 10 + (buff_color[i] - '0');
		i++;
	}
	*pointer = *pointer + num * div;
}
