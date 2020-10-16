/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:46:05 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/16 12:46:06 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	draw_map(t_all *all)
{
	int x;
	int y;

	x = 0;
	y = 0;
	

    while (all->map[y])
    {
        x = 0;
        while (all->map[y][x] && x < all->win->map_x)
        {
            if (all->map[y][x] > '0' && all->map[y][x] < '3')
			   draw_square(all, x, y, all->map[y][x]);
            x++;
        }
        y++;
    }
}

void	draw_square(t_all *all, int x, int y, char c)
{
	int x1, y1, x_begin;

	y1 = 0;
	x *= SCALE;
	y *= SCALE;
	y1 = y + SCALE;
	x1 = x + SCALE;
	
	x_begin = x;
	while (y < y1)
	{
		x = x_begin;
		while (x < x1)
		{
			if (c == '1')
				my_mlx_pixel_put(all->win, x, y, 0x8A2BE2);
        	x++;
        }
        y++;
    }	
}

void	draw_player(t_all *all)
{
	int x1, y1, x_begin, x, y;

	x1 = all->player->x + SCALE / 2;
	y1 = all->player->y + SCALE / 2;
	x = all->player->x - SCALE / 2;
	y = all->player->y - SCALE / 2;
	x_begin = x;
	while (y < y1)
	{
		x = x_begin;
		while (x < x1)
		{
			my_mlx_pixel_put(all->win, x, y, 0x0000FF00);
			x++;
		}
		y++;
	}
}