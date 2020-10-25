/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 12:48:28 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/09 20:23:32 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#include "errors.h"

#define SCALE 64
#define FOV M_PI / 3

typedef	struct	s_win {
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			screen_x;
	int			screen_y;
	int			map_x;
	int			map_y;
}				t_win;

typedef struct s_texture
{
	void		*img;
	int 		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	char		*path;

}				t_texture;

typedef	struct s_player
{
	double			x;
	double			y;
	double			dir;
	int 			is_dir_left;
	int 			is_dir_right;
	int 			is_dir_up;
	int 			is_dir_down;
	double			sin_dir;
	double			cos_dir;
	int				projection_plane;
}				t_player;

typedef struct s_ray
{
	int			is_left;
	int			is_right;
	int			is_up;
	int			is_down;
	double		intersection_x;
	double		intersection_y;
	double		ray_len;
	double		ray_fixed;
	int 		what_intersection;
}				t_ray;

typedef struct s_sprite
{
	double 		x;
	double 		y;
	double		dist;
	double		angle;
	double		delta_angle;
	double		hor_offset;
	double		vert_offset;
	int			size;
}				t_sprite;

typedef struct s_movement
{
	int 		up;
	int 		down;
	int 		left;
	int 		right;
	int 		rot_left;
	int 		rot_right;
}				t_movement;

typedef struct s_wall
{
	int 		is_left;
	int 		is_right;
	int 		is_up;
	int 		is_down;
}				t_wall;

typedef struct s_parsing
{
	int 		no_tex;
	int 		ea_tex;
	int 		we_tex;
	int 		so_tex;
	int 		s_tex;
	int 		resolution;
	int 		is_floor;
	int 		is_ceiling;
	int 		floor;
	int 		ceiling;
}				t_parsing;

typedef	struct s_all
{
	t_win		*win;
	t_player	*player;
	t_ray		*ray;
	t_texture	tex[5];
	t_sprite	*sprite;
	int 		sprites_amount;
	t_movement	movements;
	t_wall 		walls;
	t_parsing	parsing;
	char		**map;
	int 		minimap_scale;
}				t_all;

int mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

void    draw_square(t_all *all, int x, int y);
void	my_mlx_pixel_put(t_win *data, int x, int y, int color);
void	my_mlx_pixel_put_texture(t_all *all, int x, int y, int color);
char	**get_map(t_all *all, int fd);
void	draw_vertical_line(t_all *all, int x_line, double start);
void	set_background(t_all *all);
void	get_ray_direction(t_all *all, double start);
void	get_map_size(char **map, t_all *all);
void	find_player(t_all *all);
void	draw_map(t_all *all);
void	draw_player(t_all *all);
void	draw_scene(t_all *all);
int 	key_press(int key, t_all *all);
int		draw_screen(t_all *all);
void	parser(char *argv, t_all *all);
int		player_movement(t_all *all);
int		key_release(int key, t_all *all);
void	get_sprites_xy(t_all *all);
void	sprites_counter(t_all *all);
void	get_sprites_params(t_all *all);
void	draw_sprites(t_all *all, int x_line);
void	sort_sprites(t_all *all);

#endif
