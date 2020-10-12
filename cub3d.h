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

typedef	struct	s_win {
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			size_x;
	int			size_y;
}				t_win;

typedef	struct s_player
{
	float			x;
	float			y;
	float			dir;
	int				projection_plan;

}				t_player;

typedef	struct s_all
{
	t_win		*win;
	t_player	*player;
	char		**map;
}				t_all;

int mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

void    draw_square(t_all *all, int x, int y, char c);
void	my_mlx_pixel_put(t_win *data, int x, int y, int color);
char	**get_map(char *config);
void	draw_vertical_line(t_all *all, double ray_len, double x_line);

#endif
