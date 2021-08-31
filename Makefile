
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

MLXDIR_MACOS = ./minilibx/
MLX_MACOS = $(MLXDIR_MACOS)libmlx.a

MLXDIR_LINUX = ./minilibx-linux/
MLX_LINUX = $(MLXDIR_LINUX)libmlx_Linux.a

CFLAGS = -Wall -Werror -Wextra -I./includes -I./libft -I$(MLXDIR)
CFLAGS_LINUX = -I. -I/usr/include -O3 -D LINUX=1

MACOS_FLAGS = -L./minilibx -lmlx -framework OpenGL -framework AppKit
LINUX_FLAGS = -L./minilibx-linux ./minilibx-linux/libmlx_Linux.a -L/usr/lib -lXext -lX11 -lm -lz

OBJ = $(SRC:.c=.o)

all: $(NAME)

ifdef LINUX
CFLAGS += $(CFLAGS_LINUX)
MLX = $(MLX_LINUX)
MLXDIR = $(MLXDIR_LINUX)
MLX_FLAGS = $(LINUX_FLAGS)
else
MLX = $(MLX_MACOS)
MLXDIR = $(MLXDIR_MACOS)
MLX_FLAGS = $(MACOS_FLAGS)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME) -Llibft -lft $(MLX_FLAGS) 

$(LIBFT):
	make bonus -C $(LIBFTDIR)

$(MLX):
	make -C $(MLXDIR)

linux:
	$(MAKE) LINUX=1 all
clean: 
	make clean -C $(LIBFTDIR)
	make clean -C $(MLXDIR_MACOS)
	make clean -C $(MLXDIR_LINUX)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -f $(NAME)
	rm -f screenshot.bmp

re: fclean all

.PHONY: all clean fclean re
