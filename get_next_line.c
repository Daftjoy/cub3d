/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:57:51 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/02 17:03:17 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_append(int ret, char **file, int fd, char *buffer)
{
	char *aux;

	while (ret == 32)
	{
		if (ft_strchr(*file, '\n'))
			break ;
		ret = read(fd, buffer, 32);
		if (ret == -1)
		{
			free(*file);
			return (ft_return_1(buffer));
		}
		buffer[ret] = '\0';
		aux = ft_strjoin(*file, buffer);
		free(*file);
		*file = aux;
	}
	free(buffer);
	return (1);
}

int		ft_saver(char **file, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*file)[i] && (*file)[i] != '\n')
		i++;
	if ((*file)[i] == '\n')
	{
		*line = ft_substr(*file, 0, i);
		temp = ft_strdup(&((*file)[i + 1]));
		free(*file);
		*file = temp;
	}
	else
	{
		*line = ft_strdup(*file);
		free(*file);
		*file = 0;
		return (0);
	}
	return (1);
}

int		ft_return_0(char *buffer, char **line)
{
	*line = ft_strdup("");
	free(buffer);
	return (0);
}

int		ft_return_1(char *buffer)
{
	free(buffer);
	return (-1);
}

int		get_next_line(char **line, int fd)
{
	static char	*file;
	char		*buffer;
	int			ret;

	ret = 32;
	if (!(buffer = malloc(33)) || !line)
		return (-1);
	if (!file)
	{
		ret = read(fd, buffer, 32);
		if (ret == 0)
			return (ft_return_0(buffer, line));
		if (ret == -1)
			return (ft_return_1(buffer));
		buffer[ret] = '\0';
		file = ft_strdup(buffer);
		free(buffer);
		if (!(buffer = malloc(33)))
			return (-1);
	}
	if (ft_append(ret, &file, fd, buffer) < 0)
		return (-1);
	return (ft_saver(&file, line));
}
