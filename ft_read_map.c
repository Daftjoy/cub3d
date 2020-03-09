/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:22:13 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/09 20:43:06 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_path(char *line)
{
	int		j;
	int		i;
	char	*path;

	j = 0;
	i = 0;
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

void	ft_color(char *line, int *type, t_cub *cub)
{
	int		i;
	int		time;
	int		j;
	char	*buff_color;

	time = 0;
	i = 0;
	while (line[i++])
	{
		if (line[i] == '-')
			ft_error(cub, 2);
		j = 0;
		if (line[i] >= '0' && line[i] <= '9')
		{
			buff_color = malloc(sizeof(char) * 4);
			while (line[i] >= '0' && line[i] <= '9')
				buff_color[j++] = line[i++];
			time++;
			buff_color[j] = '\0';
			ft_rgb_to_hex(buff_color, time, type, cub);
			free(buff_color);
		}
	}
	if (time <= 0 || time < 3)
		ft_error(cub, 2);
}

void	ft_read_map2(t_cub *cub, char *map_path, char *line)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(map_path, O_RDONLY);
	while (get_next_line(&line, fd) > 0)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		ft_read_map3(cub, line, i);
		free(line);
	}
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
	{
		ft_loop(cub, line);
		if (cub->map_w < ft_strlen(line))
			cub->map_w = ft_strlen(line);
	}
	ft_map_size(cub);
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
	ft_read_map2(cub, map_path, line);
	if (!(cub->spritex = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	if (!(cub->spritey = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	ft_map(cub, line, map_path);
	free(line);
	line = NULL;
}

void	ft_rgb_to_hex(char *buff_color, int time, int *pointer, t_cub *cub)
{
	int		i;
	int		num;
	int		div;

	if (time == 1)
		div = 256 * 256;
	else if (time == 2)
		div = 256;
	else if (time == 3)
		div = 1;
	else
		ft_error(cub, 2);
	i = 0;
	num = 0;
	while (buff_color[i])
	{
		num = num * 10 + (buff_color[i] - '0');
		i++;
	}
	if (num > 255 || num < 0)
		ft_error(cub, 2);
	*pointer = *pointer + num * div;
}
