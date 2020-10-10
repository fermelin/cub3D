# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fermelin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/07 13:42:02 by fermelin          #+#    #+#              #
#    Updated: 2020/10/10 16:45:15 by fermelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
SRC = main.c 
LIBFTDIR = ./libft
CFLAGS = -Wall -Werror -Wextra -g
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -L minilibx -lmlx -framework OpenGL -framework AppKit -L. -lft $? -o $(NAME)
