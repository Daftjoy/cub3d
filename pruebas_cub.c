/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:21:12 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/20 12:34:28 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define KEY_A 0

#define KEY_S 1
#define KEY_D 2
#define KEY_W 13

typedef struct 	s_point
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	void *img_info;
	int x;
	int y;
}				t_point;

void 	ft_putchar (char c)
{
	write (1, &c, 1);
}

int deal_key(int key, void *param)
{

	t_point	*point;
	point  = (t_point *)param;
	if (key == 0)
	{
		point->x -= 1;
		mlx_pixel_put (point->mlx_ptr, point->win_ptr, point->x, point->y, 0xFFFFFF );
	}
	if (key == 1)
	{
		point->y += 1;
		mlx_pixel_put (point->mlx_ptr, point->win_ptr, point->x, point->y, 0xFFFFFF );
	}	
	if (key == 2)
	{	
		point->x +=1;
		mlx_pixel_put (point->mlx_ptr, point->win_ptr, point->x, point->y, 0xFFFFFF );
	}
	if	(key == 13)
	{
		point->y -= 1;
		mlx_pixel_put (point->mlx_ptr, point->win_ptr, point->x, point->y, 0xFFFFFF );
	}
	return (0);
}

int main()
{
	t_point	*point;
	int		width;
	int		height;
	int 	bpp;
	int		sl;
	int endian;
	int j;
	int i;

	bpp = 4;
	sl = 800;
	endian = 1;
	i = 0;
	j = 0;
	
	width = 50;
	height = 69;
	if (!(point = malloc( (sizeof (t_point)))))
		return (0);
	point->mlx_ptr = mlx_init(); /*necesario para iniciar la conexión con el paqute */
	point->x = 50;
	point->win_ptr = mlx_new_window(point->mlx_ptr, 1000, 720, "PAJuo" ); /*win_ptr  hace que las funciones del loop se asocien especificamente con esta ventana*/
	point->y = 50;
	mlx_key_hook(point->win_ptr, deal_key, (void *)point);
	//point->img_ptr = mlx_new_image(point->mlx_ptr, 200, 200);
	//point->img_info = mlx_get_data_addr(point->img_ptr, &bpp, &sl, &endian);
	point->img_ptr = mlx_xpm_file_to_image(point->mlx_ptr, "palacios_nazaries.xpm", &width, &height);
	mlx_put_image_to_window(point->mlx_ptr, point->win_ptr, point->img_ptr, 0, 0);
	//mlx_destroy_image(point->mlx_ptr, point->img_ptr);
	mlx_loop(point->mlx_ptr); /* hace que se quede esperando a que hagas algo*/
	return (0);
}
