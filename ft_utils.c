/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:37:19 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/09 20:25:38 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_cub *cub, int i)
{
	if (i == 0)
	{
		write(1, "Resolution Error\n", 17);
		ft_exit_hook(cub);
	}
	if (i == 1)
	{
		write(1, "Wrong path\n", 11);
		ft_exit_hook(cub);
	}
	if (i == 2)
	{
		write(1, "Color error\n", 12);
		ft_exit_hook(cub);
	}
	if (i == 3)
	{
		write(1, "Wrong extension\n", 16);
		ft_exit_hook(cub);
	}
	if (i == 4)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
}

void	ft_error_2(t_cub *cub, int i)
{
	if (i == 0)
	{
		write(1, "Map error\n", 10);
		ft_exit_hook(cub);
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

int		ft_loop3(t_cub *cub, char *line, int n, int *j)
{
	int i;
	int j_pointer;

	i = 0;
	j_pointer = *j;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] >= '0' && line[i] <= '9')
		{
			n = ft_loop2(cub, line, j_pointer, n);
			j_pointer++;
			break ;
		}
		else
			break ;
	}
	*j = j_pointer;
	return (n);
}
