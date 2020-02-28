/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:57:51 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/28 13:35:53 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strlen(char *s)
{
	int len;

	len = 0;
	while(s[len])
		len++;
	return(len);
}

char *ft_strdup(char *s)
{
	char *str;
	int i;

	if (!s || !(str = malloc(ft_strlen(s) + 1)))
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *str;
	int i;
	int j;

	if (!s1 || !s2 || !(str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char *ft_substr(char *s, int start, int len)
{
	char *str;
	int i;

	if (!s || !(str = malloc(len + 1)))
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strchr(char *s, int c)
{
	int i;

	i = 0;
	while(s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *)s + i);
	return (0);
}

int get_next_line(char **line, int fd)
{
	int i;
	char *aux;
	char *temp;
	static char *file;
	char *buffer;
	int ret;

	ret = 32;
	if (!(buffer = malloc(33)) || !line)
		return (-1);
	if (!file)
	{
		ret = read(fd, buffer, 32);
		if (ret == 0)
		{
			*line = ft_strdup("");
			free(buffer);
			return (0);
		}
		if (ret ==-1)
		{
			free(buffer);
			return (-1);
		}
		buffer[ret] = '\0';
		file = ft_strdup(buffer);
		free (buffer);
		if (!(buffer = malloc(33)))
			return (-1);
	}
	while(ret == 32)
	{
		if (ft_strchr(file, '\n'))
			break ;
		ret = read(fd, buffer, 32);
		if (ret ==-1)
		{
			free(buffer);
			free(file);
			return (-1);
		}
		buffer[ret] = '\0';
		aux = ft_strjoin(file, buffer);
		free (file);
		file = aux;
	}
	free(buffer);
	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (file[i] == '\n')
	{
		*line = ft_substr(file, 0, i);
		temp = ft_strdup(&(file[i + 1]));
		free (file);
		file = temp;
	}
	else
	{
		*line = ft_strdup(file);
		free (file);
		file = 0;
		return (0);
	}
	return (1);
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

void ft_read_map(t_cub *cub, char *map_path)
{
	char *line;
	int fd;
	int **map;
	int i;
	int j;
	int n;
	int height;
	int width;
	char *buff_color;
	int time;

	cub->screenheight = 0;
	cub->screenwidth = 0;
	i = 0;
	j = 0;
	cub->sprites_numb = 0;
	height = 0;
	width = 0;
	cub->path_no = malloc(sizeof(char) * 100);
	cub->path_so = malloc(sizeof(char) * 100);
	cub->path_we = malloc(sizeof(char) * 100);
	cub->path_ea = malloc(sizeof(char) * 100);
	cub->path_sprite = malloc(sizeof(char) * 100);
	line = NULL;
	fd = open(map_path, O_RDONLY);
	while(get_next_line(&line, fd) > 0)
	{
		if(line[0] >= '0' && line[0] <= '9')
		{
			i = 0;
			while(line[i])
			{
				if (line[i] == '2')
					cub->sprites_numb++;
				i++;
			}
			height++;
		}
	}
	if(line[0] >= '0' && line[0] <= '9')
	{
		i = 0;
		while(line[i])
		{
			if (line[i] == '2')
				cub->sprites_numb++;
			i++;
		}
		height++;
	}
	i = 0;
	width = ft_strlen(line);
	free(line);
	line = NULL;
	if(!(map = malloc(sizeof(int *) * height)))
		return ;
	while (j < height)
	{
		if(!(map[j] = malloc(sizeof(int) * width)))
			return;
		j++;
	}
	if(!(cub->spritex = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	if(!(cub->spritey = malloc(sizeof(double) * cub->sprites_numb)))
		return ;
	j = 0;
	i = 0;
	n = 0;
	fd = open(map_path, O_RDONLY);
	while(get_next_line(&line, fd) > 0)
	{
		if(line[0] >= '0' && line[0] <= '9')
		{
			while(line[i])
			{
				if (line[i] == '2')
				{
					cub->spritex[n] = i;
					cub->spritey[n] = j;
					n++;
				}
				if (line[i] == 'W' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E')
				{
					cub->posx = j;
					cub->posy = i;
					cub->orientation = line[i];
					map[j][i] = 0;
					i++;
				}
				else
				{
					map[j][i] = line[i] - '0';
					i++;
				}
			}
			i = 0;
			j++;
		}
	}
	if(line[0] >= '0' && line[0] <= '9')
	{
		while(line[i])
		{
			if (line[i] == '2')
			{
				cub->spritex[n] = i;
				cub->spritey[n] = j;
				n++;
			}
			map[j][i] = line[i] - '0';
			i++;
		}
	}
	i = 0;
	j = 0;
	cub->map = map;
	free(line);
	line = NULL;
	fd = open(map_path, O_RDONLY);
	while(get_next_line(&line, fd) >0)
	{
		if(line[0] == 'R')
		{
			while(line[i])
			{
				if(cub->screenwidth == 0)
					while (line[i]>= '0' && line[i] <= '9')
					{
						cub->screenwidth = cub->screenwidth * 10 + (line[i] - '0');
						i++;
					}
				else if(cub->screenheight == 0)
					while (line[i]>= '0' && line[i] <= '9')
					{
						cub->screenheight = cub->screenheight * 10 + (line[i] - '0');
						i++;
					}
				if (line[i])
					i++;
			}
			i = 0;
		}
		if(line[0] == 'N' && line[1] == 'O')
		{
			i = 2;
			while(line[i])
			{
				if(line[i] == ' ')
					i++;
				else
				{
					cub->path_no[j] = line[i];
					i++;
					j++;
				}
			}
			cub->path_no[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'S' && line[1] == 'O')
		{
			i = 3;
			while(line[i])
			{
				if(line[i] == ' ')
					i++;
				else
				{
					cub->path_so[j] = line[i];
					i++;
					j++;
				}
			}
			cub->path_so[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'W' && line[1] == 'E')
		{
			i = 3;
			while(line[i])
			{
				if(line[i] == ' ')
					i++;
				else
				{
					cub->path_we[j] = line[i];
					i++;
					j++;
				}
			}
			cub->path_we[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'E' && line[1] == 'A')
		{
			i = 3;
			while(line[i])
			{
				if(line[i] == ' ')
					i++;
				else
				{
					cub->path_ea[j] = line[i];
					i++;
					j++;
				}
			}
			cub->path_ea[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'S' && line[1] == ' ')
		{
			i = 2;
			while(line[i])
			{
				if(line[i] == ' ')
					i++;
				else
				{
					cub->path_sprite[j] = line[i];
					i++;
					j++;
				}
			}
			cub->path_sprite[j] = '\0';
			i = 0;
			j = 0;
		}
		if (line [0] == 'F' && line[1] == ' ')
		{
			time = 0;
			i = 2;
			while (line[i])
			{
				if(line[i] == ' ' || line[i] == ',')
					i++;
				else
				{
					buff_color = malloc(sizeof(char) * 4);
					while (line[i]>= '0' && line[i] <= '9')
					{
					//	ft_rgb_to_hex(cub);
						buff_color[j] = line[i];
						j++;
						i++;
					}
					time++;
					buff_color[j] = '\0';
					ft_rgb_to_hex(buff_color, time, &cub->floor_color);
					free(buff_color);
					j = 0;
				}
			}
			i = 0;
		}
		if (line [0] == 'C' && line[1] == ' ')
		{
			time = 0;
			i = 2;
			while (line[i])
			{
				if(line[i] == ' ' || line[i] == ',')
					i++;
				else
				{
					buff_color = malloc(sizeof(char) * 4);
					while (line[i]>= '0' && line[i] <= '9')
					{
					//	ft_rgb_to_hex(cub);
						buff_color[j] = line[i];
						j++;
						i++;
					}
					time++;
					buff_color[j] = '\0';
					ft_rgb_to_hex(buff_color, time, &cub->ceiling_color);
					free(buff_color);
					j = 0;
				}
			}
			i = 0;
		}
	/*	if (line [0] == 'C' && line[1] == ' ')
		{
			i = 2;
			while (line[i])
			{
				if(line[i] == ' ' || line[i] == ',')
					i++;
				else
					while (line[i]>= '0' && line[i] <= '9')
					{
						cub->ceiling_color[j] = line[i];
						j++;
						i++;
					}
			}
			cub->ceiling_color[j] = '\0';
			j = 0;
			i = 0;
		}*/
	}
}