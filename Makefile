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
		src/parser_map.c \
		src/draw_minimap.c \
		src/ray_casting.c \
		src/player.c \
		src/parser.c \
		src/sprites.c \
		src/screenshot.c \
		src/errors.c \
		src/map_validation.c \
		src/walls_drawing.c \
		src/movement_events.c \
		src/initialization.c \
		src/parser_resolution.c \
		src/parser_background.c \
		src/parser_sprites.c
HDR = cub3d.h

LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a

MLXDIR = ./minilibx/
MLX = $(MLXDIR)libmlx.a

CFLAGS = -Wall -Werror -Wextra -Iincludes -Iminilibx -Ilibft
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS)  -Llibft -lft -Lminilibx -lmlx -framework OpenGL -framework AppKit $^ -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTDIR)

$(MLX):
	make -C $(MLXDIR)

clean: 
	make clean -C $(LIBFTDIR)
	make clean -C $(MLXDIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -f $(NAME)
	rm -f screenshot.bmp

re: fclean all

.PHONY: all clean fclean re
