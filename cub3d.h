/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:05:59 by antmarti          #+#    #+#             */
/*   Updated: 2020/02/21 16:29:21 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef textwidth 
# define textwidth 64
#ifndef textheight 
# define textheight 64


#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_ESC 53

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

typedef struct 	s_cub
{
	double	posx; // posiciones de inicio del personaje
	double	posy;
	double	dirx; // dirección a la que mira el jugador
	double	olddirx;
	double	diry;
	double	planex; // plano de cámara del jugador -> es perpendicular al de dirección
	double	oldplanex;
	double	planey;
	double	camerax; // lado de la pantalla en el que te encuentras, siendo  0 = centro, 1 = derecha y -1 = izquierda
	double	raydirx; // dirección rayo de ray casting
	double	raydiry;
	int		mapx; // posición actual del mapa en la que se encuentra el rayo
	int		mapy;
	double	sidedistx; // distancia que el rayo tiene que hacer para avanzar la primera posición en el mapa 
	double	sidedisty;
	double	deltadistx; // distancia que el rayo tiene que hacer para avanzar una posición en el mapa 
	double	deltadisty;
	int		stepx; // dependen de la dirección del rayo y funciona igual 1 o -1
	int		stepy;
	int		hit; // determina si se choca -> 1
	int		side; // es 0 si se ha chocado con un x-side y 1 si ha sido con un y-side
	double	perpwalldist; // largo del rayo
	int		lineheight;
	int		drawstart;
	int		drawend;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int	*img_info;
	int		bpp;
	int		ls;
	int		endian;
	unsigned int *dst;
	double	rotspeed;
	double	movespeed;
	int		a;
	int		s;
	int		w;
	int		d;
	int		right;
	int		left;
	int		**texture;
	int		*n_text;
	int 	*n_text_info;
	int		*n_text2;
	int 	*n_text_info2;
	int		**map;
	int 	screenheight;
	int 	screenwidth;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	*path_sprite;
	char	*floor_color;
	char 	*ceiling_color;
} 				t_cub;

void ft_read_map(t_cub *cub, char *map_path);

#endif
#endif
