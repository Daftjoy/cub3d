# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 16:19:18 by agianico          #+#    #+#              #
#    Updated: 2020/03/03 19:41:12 by antmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	cub3d.c get_next_line.c get_next_line_utils.c ft_floor_ceiling.c ft_set_direction.c ft_textures.c ft_move_player.c \
ft_key_detect.c ft_move_player2.c ft_sprites.c ft_raycasting.c ft_view.c ft_read_map.c ft_read_map2.c bmp.c\

OBJS =	$(SRCS:.c=.o)

FLAGS =	-Werror -Wextra -Wall

LIB_FLAGS =	-lmlx -framework OpenGL -framework AppKit

PATH1 =	/usr/local/include

PATH2 = /usr/local/lib/

NAME =	cub3d

RM = rm -f

$(NAME):
		gcc $(FLAGS) -I $(PATH1) $(SRCS) -L $(PATH2) $(LIB_FLAGS) -o $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
