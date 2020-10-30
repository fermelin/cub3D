/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 13:31:57 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/21 13:32:02 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_delta_angle(double start, double sprite_angle)
{
	double delta_angle;

	delta_angle = start - sprite_angle;
	if (delta_angle <= -M_PI)
		delta_angle += 2 * M_PI;
	else if (delta_angle >= M_PI)
		delta_angle -= 2 * M_PI;
	return (delta_angle);
}

static void		sort_sprites(t_all *all)
{
	int			i;
	t_sprite	temp;

	i = 0;
	while (i < all->sprites_amount - 1)
	{
		if (all->sprite[i].dist < all->sprite[i + 1].dist)
		{
			temp = all->sprite[i + 1];
			all->sprite[i + 1] = all->sprite[i];
			all->sprite[i] = temp;
			i = 0;
		}
		i++;
	}
}

void			get_sprites_params(t_all *all)
{
	double	start;
	int		i;

	i = 0;
	start = all->player->dir + (FOV / 2);
	while (i < all->sprites_amount)
	{
		all->sprite[i].angle = atan2(all->player->y - all->sprite[i].y,
			all->sprite[i].x - all->player->x);
		all->sprite[i].dist = hypot(all->sprite[i].x - all->player->x,
			all->sprite[i].y - all->player->y);
		all->sprite[i].size = (SCALE / all->sprite[i].dist) *
		all->player->projection_plane;
		all->sprite[i].delta_angle = get_delta_angle(start,
			all->sprite[i].angle);
		all->sprite[i].hor_offset = (all->sprite[i].delta_angle /
			(FOV / all->win->screen_x) - all->sprite[i].size / 2);
		all->sprite[i].vert_offset = (all->win->screen_y / 2 -
			all->sprite[i].size / 2);
		i++;
	}
	sort_sprites(all);
}

static int		get_sprite_color(t_all *all, int y, int i)
{
	int color;
	int texture_x;
	int texture_y;

	if (all->sprite[i].size > 1)
	{
		texture_y = y * (all->tex[4].height - 1) / (all->sprite[i].size - 1);
		texture_x = (all->ray->x_line - all->sprite[i].hor_offset) *
		(all->tex[4].width - 1) / (all->sprite[i].size - 1);
		color = *(all->tex[4].addr + (int)((int)(texture_y) *
			all->tex[4].line_length / sizeof(int) +
			texture_x * (all->tex[4].bits_per_pixel / 8) / sizeof(int)));
		return (color);
	}
	return (0);
}

void			draw_sprites(t_all *all)
{
	int y;
	int color;
	int i;

	i = 0;
	while (i < all->sprites_amount)
	{
		if (all->sprite[i].size > all->win->screen_y)
			all->sprite[i].size = 0;
		if (all->ray->x_line >= all->sprite[i].hor_offset && all->ray->x_line
			<= all->sprite[i].hor_offset + all->sprite[i].size
			&& all->sprite[i].dist < all->ray->ray_len)
		{
			y = 0;
			while (y < all->sprite[i].size)
			{
				color = get_sprite_color(all, y, i);
				if (color != 0x0)
					my_mlx_pixel_put(all->win, all->ray->x_line,
						(int)(all->sprite[i].vert_offset + y), color);
				y++;
			}
		}
		i++;
	}
}
