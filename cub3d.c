/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:36 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/01 18:01:46 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	free(cub);
	system("killall afplay");
	exit(0);
	return (0);
}

void	ft_mlx(t_cub *cub)
{
	mlx_hook(cub->win_ptr, 2, 0, key_pressed, (void *)cub);
	mlx_hook(cub->win_ptr, 3, 0, key_released, (void *)cub);
	mlx_loop_hook(cub->mlx_ptr, move_player, (void *)cub);
	mlx_hook(cub->win_ptr, 17, 0, ft_exit_hook, (void *)cub);
	mlx_loop(cub->mlx_ptr);
}

int		main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc == 2 || argc == 3)
	{
		if (!(cub = malloc(sizeof(t_cub))))
			return (0);
		ft_read_map(cub, argv[1]);
		ft_set_direction(cub);
		cub->textheight = 64;
		cub->textwidth = 64;
		cub->mlx_ptr = mlx_init();
		cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->screenwidth,
		cub->screenheight, "Marisco");
		cub->rotspeed = 0.05;
		cub->movespeed = 0.1;
		system("afplay rec.mp3 &");
		ft_textures(cub);
		ft_view(cub);
		ft_mlx(cub);
	}
	else
		write(1, "Error\n", 6);
	return (0);
}
