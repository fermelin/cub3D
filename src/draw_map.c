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

void	draw_bun_of_rays(t_all *all)
{
	t_player 	ray;
	double		start;
	double		end;
	int 		scale;
	
	scale = (all->win->screen_x + all->win->screen_y) / 2 / 100;
	ray = *all->player;
	start = ray.dir - (FOV / 2);
	end = ray.dir + (FOV / 2);
	while(start <= end)
	{
		ray.x = all->player->x / SCALE * scale;
		ray.y = all->player->y / SCALE * scale;
		while (all->map[(int)(ray.y / scale)][(int)(ray.x / scale)] != '1')
		{
			ray.x += cos(start);
			ray.y -= sin(start);	
			my_mlx_pixel_put(all->win, ray.x, ray.y, 0x00FF0000);
		}
		start += (FOV) / all->win->screen_x;
	}
}

void	draw_map(t_all *all)
{
	int x;
	int y;

	x = 0;
	y = 0;
    while (all->map[y])
    {
        x = 0;
        while (all->map[y][x])
        {
            if (all->map[y][x] == '1')
			   draw_square(all, x, y);
            x++;
        }
        y++;
    }
    draw_bun_of_rays(all);
    draw_player(all);
}

void	draw_square(t_all *all, int x, int y)
{
	int x1, y1, x_begin, scale;
	printf("%d\n", x);

	scale = (all->win->screen_x + all->win->screen_y) / 2 / 100;
	x *= scale;
	y *= scale;
	y1 = y + scale;
	x1 = x + scale;
	
	x_begin = x;
	while (y < y1)
	{
		x = x_begin;
		while (x < x1)
		{
			my_mlx_pixel_put(all->win, x, y, 0x8A2BE2);
        	x++;
        }
        y++;
    }	
}

void	draw_player(t_all *all)
{
	int x1, y1, x_begin, x, y, scale;

	scale = (all->win->screen_x + all->win->screen_y) / 2 / 100;
	x1 = all->player->x / SCALE * scale + scale / 2;
	y1 = all->player->y / SCALE * scale + scale / 2;
	x = all->player->x / SCALE * scale - scale / 2;
	y = all->player->y / SCALE * scale - scale / 2;
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