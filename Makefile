# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/07 13:42:02 by fermelin          #+#    #+#              #
#    Updated: 2020/10/11 13:31:58 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
SRC = 	src/main.c \
		src/cub3d_utils.c \
		src/get_config.c \
		src/draw_map.c \
		src/ray_casting.c \
		src/player.c \
		src/parser.c \
		src/sprites.c \
		src/screenshot.c \
		src/errors.c \
		src/map_validation.c \
		src/parser_init_and_textures.c \
		src/walls_drawing.c

HDR = cub3d.h
LIBFTDIR = ./libft
CFLAGS = -Wall -Werror -Wextra -g -I.
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -L minilibx -lmlx -framework OpenGL -framework AppKit -L. -lft $? -o $(NAME)

clean: 
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
