/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:36 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/03 21:38:35 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	free(cub->dst);
	free(cub->texture);
	free(cub->map);
	free(cub->path_no);
	free(cub->path_so);
	free(cub->path_we);
	free(cub->path_ea);
	free(cub->path_sprite);
	free(cub->zbuffer);
	free(cub->spritex);
	free(cub->spritey);
	//free(cub->spriteorder);
	//free(cub->spritedistance);
	free(cub->n_text);
	free(cub->n_text_info);
	free(cub->n_text2);
	free(cub->n_text_info2);
	free(cub->n_text3);
	free(cub->n_text_info3);
	free(cub->n_text4);
	free(cub->n_text_info4);
	free(cub->n_text5);
	free(cub->n_text_info5);
	free(cub->n_text6);
	free(cub->n_text_info6);
	free(cub);
	cub = 0;
	//system("killall afplay");
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

	cub = NULL;
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
		ft_textures(cub);
		if (!(cub->zbuffer = malloc(sizeof(double) * cub->screenwidth + 1)))
			return (0);
		if (argc == 3 && strcmp(argv[2], "--save") == 0)
		{
			save_bmp(cub);
			ft_exit_hook(cub);
		}
		//system("afplay rec.mp3 &");
		ft_view(cub);
		//ft_free(cub);
		ft_mlx(cub);
	}
	else
		write(1, "Error\n", 6);
	getchar();
	return (0);
}
