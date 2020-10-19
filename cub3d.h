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
#include "libft.h"

#define SCALE 30
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
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef	struct s_player
{
	double			x;
	double			y;
	double			dir;
	int				projection_plan;

}				t_player;

typedef struct s_ray
{
	int			is_left;
	int			is_right;
	int			is_up;
	int			is_down;
	double		intersection_x;
	double		intersection_y;
	int 		what_intersection;
}				t_ray;

typedef	struct s_all
{
	t_win		*win;
	t_player	*player;
	t_ray		*ray;
	t_texture	*texture;
	char		**map;
}				t_all;

int mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

void    draw_square(t_all *all, int x, int y, char c);
void	my_mlx_pixel_put(t_win *data, int x, int y, int color);
void	my_mlx_pixel_put_texture(t_all *all, int x, int y, int color);
char	**get_map(char *config, t_all *all);
void	draw_vertical_line(t_all *all, double ray_len, int x_line);
void	set_background(t_all *all);
void	get_ray_direction(t_all *all, double start);
void	get_map_size(char **map, t_all *all);
void	find_player(t_all *all);
void	draw_map(t_all *all);
void	draw_player(t_all *all);
void	cast_rays(t_all *all);
int 	key_press(int key, t_all *all);
int		draw_screen(t_all *all);

#endif
