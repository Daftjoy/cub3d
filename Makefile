# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agianico <agianico@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 16:19:18 by agianico          #+#    #+#              #
#    Updated: 2020/02/28 17:27:14 by agianico         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	cub3d.c get_next_line.c ft_floor_ceiling.c ft_set_direction.c ft_textures.c ft_move_player.c

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
