/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:57:51 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/19 19:30:10 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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


int main()
{
	char *line;
	int fd;
	char **map;
	int i;
	int j;
	int height;
	int width;
	int screenwidth;
	int screenheight;
	char *path_no;
	char *path_so;
	char *path_we;
	char *path_ea;
	char *path_sprite;
	char *floor;
	char *ceiling;
	
	screenheight = 0;
	screenheight = 0;
	i = 0;
	j = 0;
	height = 0;
	width = 0;
	path_no = malloc(sizeof(char) * 100);
	path_so = malloc(sizeof(char) * 100);
	path_we = malloc(sizeof(char) * 100);
	path_ea = malloc(sizeof(char) * 100);
	path_sprite = malloc(sizeof(char) * 100);
	floor = malloc(sizeof(char) * 100);
	ceiling = malloc(sizeof(char) * 100);
	/*if(!(map = malloc(sizeof(char * ) *13)))
		return (0);
	while (i < 24)
	{
		if(!(map[i] = malloc(sizeof(char) *57)))
			return (0);
		i++;
	}*/
	i = 0;
	line = NULL;
	fd = open("map1.cub", O_RDONLY);
	while(get_next_line(&line, fd) >0)
	{	
		if(line[0] >= '0' && line[0] <= '9')
			height++;
	}
	if(line[0] >= '0' && line[0] <= '9')
		height++;
	width = ft_strlen(line);
	free(line);
	if(!(map = malloc(sizeof(char * ) *height)))
		return (0);
	while (i < height)
	{
		if(!(map[i] = malloc(sizeof(char) *width)))
			return (0);
		i++;
	}
	i = 0;
	fd = open("map1.cub", O_RDONLY);
	free(line);
	while(get_next_line(&line, fd) >0)
	{	
		if(line[0] >= '0' && line[0] <= '9')
		{
			map[i] = line;
			i++;
		}
	}
	if(line[0] >= '0' && line[0] <= '9')
	{
		map[i] = line;
	}
	i = 0;
	/*while(i < height)
	{
		printf("%s\n", map[i]);
		i++;
	}*/
	free(line);
	fd = open("map1.cub", O_RDONLY);
	while(get_next_line(&line, fd) >0)
	{
		if(line[0] == 'R')
		{
			while(line[i])
			{
				if(screenwidth == 0)
					while (line[i]>= '0' && line[i] <= '9')
					{
						screenwidth = screenwidth * 10 + (line[i] - '0');
						i++;
					}
				else if(screenheight == 0)
					while (line[i]>= '0' && line[i] <= '9')
					{
						screenheight = screenheight * 10 + (line[i] - '0');
						i++;
					}
				i++;
			}
			i = 0;
		}
		if(line[0] == 'N' && line[1] == 'O')
		{
			i = 3;
			while(line[i])
			{
				path_no[j] = line[i];
				i++;
				j++;
			}
			path_no[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'S' && line[1] == 'O')
		{
			i = 3;
			while(line[i])
			{
				path_so[j] = line[i];
				i++;
				j++;
			}
			path_so[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'W' && line[1] == 'E')
		{
			i = 3;
			while(line[i])
			{
				path_we[j] = line[i];
				i++;
				j++;
			}
			path_we[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'E' && line[1] == 'A')
		{
			i = 3;
			while(line[i])
			{
				path_ea[j] = line[i];
				i++;
				j++;
			}
			path_ea[j] = '\0';
			i = 0;
			j = 0;
		}
		if(line[0] == 'S' && line[1] == ' ')
		{
			i = 2;
			while(line[i])
			{
				path_sprite[j] = line[i];
				i++;
				j++;
			}
			path_sprite[j] = '\0';
			i = 0;
			j = 0;
		}
		if (line [0] == 'F' && line[1] == ' ')
		{
			i = 2;
			while (line[i])
			{
				floor[j] = line[i];
				j++;
				i++;
			}
			floor[j] = '\0';
			j = 0;
			i = 0;
		}
		if (line [0] == 'C' && line[1] == ' ')
		{
			i = 2;
			while (line[i])
			{
				ceiling[j] = line[i];
				j++;
				i++;
			}
			ceiling[j] = '\0';
			j = 0;
			i = 0;
		}
	}
	printf("Esto es pathno %s\n Esto es pathso %s\n Esto es pathwe %s\n Esto es pathea %s\n Esto es pathsp %s\n", path_no, path_so, path_we, path_ea, path_sprite);
	free(path_no);
	free(path_so);
	free(path_we);
	free(path_ea);
	free(path_sprite);
	free(map);
}