/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:29:18 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/16 12:29:20 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	set_background(t_all *all)
{
	int x;
	int y;

	y = 0;
    while (y < all->win->screen_y / 2)
    {
        x = 0;
        while (x < all->win->screen_x)
        {
            my_mlx_pixel_put(all->win, x, y, all->parsing.ceiling);
            x++;
        }
        y++;
        // if (y % 3 == 0)
        //     color--;
    }
    // color = 0x00000000;
    while (y < all->win->screen_y)
    {
        x = 0;
        while (x < all->win->screen_x)
        {
            my_mlx_pixel_put(all->win, x, y, all->parsing.floor);
            x++;
        }
        y++;
        // if (y % 3 == 0) //исправить, чтобы зависело от разрешения экрана
        //     color+= 256;
    }
}

void	get_ray_direction(t_all *all, double start)
{
	all->ray->is_right = 0;
	all->ray->is_left = 0;
	all->ray->is_up = 0;
	all->ray->is_down = 0;
	if (cos(start) > 0)
		all->ray->is_right = 1;
	else if (cos(start) < 0)
		all->ray->is_left = 1;
	if (sin(start) > 0)
		all->ray->is_up = 1;
	else if (sin(start) < 0)
		all->ray->is_down = 1;
}

void	get_map_size(char **map, t_all *all)
{
	int 	x;
	int 	y;
	int 	x_max;

	y = 0;
	x_max = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (x > x_max)
				x_max = x;
			x++;
		}
		y++;
	}
	all->win->map_x = x_max + 1;
	all->win->map_y = y;
	printf("map_y is %d\n", all->win->map_y);
}

void	find_player(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[y][x] == 'W' || all->map[y][x] == 'E' || all->map[y][x] == 'S' || all->map[y][x] == 'N')
			{
				if (all->map[y][x] == 'W')
					all->player->dir = M_PI;
				if (all->map[y][x] == 'E')
					all->player->dir = 0;
				if (all->map[y][x] == 'S')
					all->player->dir = 3 * M_PI_2;
				if (all->map[y][x] == 'N')
					all->player->dir = M_PI_2;
				all->player->x = x * SCALE + SCALE / 2;
				all->player->y = y * SCALE + SCALE / 2;
				return ;
			}
			x++;
		}
		y++;
	}
}
