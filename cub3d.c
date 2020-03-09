/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:36 by antmarti          #+#    #+#             */
/*   Updated: 2020/03/09 20:00:49 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit_hook(void *param)
{
	t_cub	*cub;
	int		i;

	i = -1;
	cub = (t_cub *)param;
	if (cub->music == 0)
		system("killall afplay");
	free(cub->texture);
	while (++i < cub->map_h)
		free(cub->map[i]);
	free(cub->map);
	free(cub->path_no);
	free(cub->path_so);
	free(cub->path_we);
	free(cub->path_ea);
	free(cub->path_sprite);
	free(cub->zbuffer);
	free(cub->spritex);
	free(cub->spritey);
	free(cub->n_text);
	free(cub->n_text_info);
	ft_exit_hook2(cub);
	exit(0);
	return (0);
}

void	ft_exit_hook2(t_cub *cub)
{
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
}

void	ft_mlx(t_cub *cub)
{
	mlx_hook(cub->win_ptr, 2, 0, key_pressed, (void *)cub);
	mlx_hook(cub->win_ptr, 3, 0, key_released, (void *)cub);
	mlx_loop_hook(cub->mlx_ptr, move_player, (void *)cub);
	mlx_hook(cub->win_ptr, 17, 0, ft_exit_hook, (void *)cub);
	mlx_loop(cub->mlx_ptr);
}

void	ft_crabs(t_cub *cub, char **argv)
{
	system("afplay rec.mp3 &");
	if (!ft_strcmp(&(argv[1][ft_strlen(argv[1]) - 4]), ".cub"))
		ft_error(cub, 3);
	cub->counter = 0;
	ft_read_map(cub, argv[1]);
	if (cub->counter != 1)
		ft_error_2(cub, 0);
	cub->music = 0;
	ft_path_check(cub);
	if (!ft_map_error(cub))
		ft_error_2(cub, 0);
	ft_set_direction(cub);
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->screenwidth,
	cub->screenheight, "Marisco");
	ft_textures(cub);
	if (!(cub->zbuffer = malloc(sizeof(double) * cub->screenwidth + 1)))
		return ;
}

int		main(int argc, char **argv)
{
	t_cub *cub;

	cub = NULL;
	if (argc == 2 || argc == 3)
	{
		if (!(cub = malloc(sizeof(t_cub))))
			return (0);
		ft_crabs(cub, argv);
		if (argc == 3)
		{
			system("killall afplay");
			cub->music = 1;
			if (ft_strcmp(argv[2], "--save"))
				save_bmp(cub);
			else
				write(1, "Argument Error", 14);
			ft_exit_hook(cub);
		}
		ft_view(cub);
		ft_mlx(cub);
	}
	else
		ft_error(cub, 4);
	return (0);
}
