/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:50:26 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/16 12:50:29 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	horizontal_intersection(t_all *all, double start)
{
	double	x_hor;
	double	y_hor;
	double	x_diff;
	double	y_diff;

	x_hor = 0;
	y_hor = 0;
	y_hor = (int)(all->player->y / SCALE) * SCALE;
	y_hor += (all->ray->is_up) ? -0.001 : SCALE;
	x_hor = all->player->x + (all->player->y - y_hor) / tan(start);
	x_diff = SCALE / tan(start);
	x_diff *= (all->ray->is_left && x_diff > 0) ? -1 : 1;
	x_diff *= (all->ray->is_right && x_diff < 0) ? -1 : 1;
	y_diff = (all->ray->is_up) ? -SCALE : SCALE;
	while (y_hor / SCALE >= 0 && y_hor / SCALE < all->win->map_y && 
		x_hor / SCALE >= 0 && x_hor / SCALE < all->win->map_x && 
		all->map[(int)(y_hor / SCALE)][(int)(x_hor / SCALE)] != '1')
	{
		y_hor += y_diff;
		x_hor += x_diff;
	}
	all->ray->intersection_x = x_hor;
	return(fabs((all->player->y - y_hor) / sin(start)));
}

static double	vertical_intersection(t_all *all, double start)
{
	double	x_vert;
	double	y_vert;
	double	y_diff;
	double	x_diff;

	x_vert = 0;
	y_vert = 0;
	x_vert = (int)(all->player->x / SCALE) * SCALE;
	x_vert += (all->ray->is_right) ? SCALE : -0.001;
	y_vert = all->player->y + (all->player->x - x_vert) * tan(start);
	y_diff = SCALE * tan(start);
	y_diff *= (all->ray->is_up && y_diff > 0) ? -1 : 1;
	y_diff *= (all->ray->is_down && y_diff < 0) ? -1 : 1;
	x_diff = (all->ray->is_left) ? -SCALE : SCALE;
	while (y_vert / SCALE >= 0 && y_vert / SCALE < all->win->map_y && 
		x_vert / SCALE >= 0 && x_vert / SCALE < all->win->map_x &&
		all->map[(int)(y_vert / SCALE)][(int)(x_vert / SCALE)] != '1')
	{
		x_vert += x_diff;
		y_vert += y_diff;
	}
	all->ray->intersection_y = y_vert;
	return (fabs((all->player->x - x_vert) / cos(start)));
}

void	cast_rays(t_all *all)
{
	double	start;
	double	end;
	double 	ray_len;
	int 	x_line;
	double	ray_hor;
	double	ray_vert;
	
	start = all->player->dir - (FOV / 2);
	end = all->player->dir + (FOV / 2);
	x_line = all->win->screen_x;
	while (start <= end && x_line != 0)
	{
		get_ray_direction(all, start);
		all->ray->what_intersection = 0;
		ray_hor = 0;
		ray_vert = 0;

		if (sin(start) != 0)
			ray_hor = horizontal_intersection(all, start);
		if (cos(start) != 0)
			ray_vert = vertical_intersection(all, start);
		if (ray_vert == 0)
			ray_len = ray_hor;
		else if (ray_hor == 0)
		{
			ray_len = ray_vert;
			all->ray->what_intersection = 1;
		}
		else
		{
			ray_len = (ray_hor > ray_vert) ? (ray_vert * cos(start - all->player->dir)) : (ray_hor * cos(start - all->player->dir));
			all->ray->what_intersection = (ray_hor > ray_vert) ? 1 : 0;
		}
		x_line--;
		draw_vertical_line(all, ray_len, x_line);
		start += (FOV) / all->win->screen_x;
	}
}