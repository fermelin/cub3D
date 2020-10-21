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

void	sprites_counter(all) //with malloc
{
	int 		x;
	int 		y;

	x = 0;
	y = 0;
	all->sprites_amount = 0;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[x][y] == '2')
				all->sprites_amount++;
			x++;
		}
	}
	if (all->sprites_amount > 0)
	{
		if (!(all->sprite = (t_sprite*)malloc(sizeof(t_sprite) * all->sprites_amount)))
			return ;
	}
}

void	get_sprites_xy(t_all *all)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;
	if (all->sprites_amount > 0)
	{
		while (all->map[y])
		{
			x = 0;
			while (all->map[y][x])
			{
				if (all->map[x][y] == '2')
				{
					all->sprite.x[i] = x * SCALE + SCALE / 2;
					all->sprite.y[i] = y * SCALE + SCALE / 2;
					i++;
				}
				x++;
			}
		}
	}
}

void	draw_sprite(t_all *all, int x_line)
{
	int 	y;
	int 	y1;
	double 	slice_height;
	int 	color;
	double	ray_intersection;
	double	step_y;
	int 	i;
	int 	texture_x;
	double	height_diff;

	slice_height = 0;
	i = 0;
	height_diff = 0;
	ray_intersection = (all->ray->what_intersection == 0) ? all->ray->intersection_x : all->ray->intersection_y;
	texture_x = (int)ray_intersection % SCALE % (all->tex[4].width);
	if (all->ray->ray_len != 0)
		slice_height = (int)(SCALE * all->player->projection_plan / all->ray->ray_len);
	//printf("slice_height is %24f\n", slice_height);
	if (slice_height > all->win->screen_y)
	{
		i = (slice_height - all->win->screen_y) / 2;
		height_diff = all->win->screen_y - slice_height;
		slice_height = all->win->screen_y;
	}
	//color = 0xFFFFFF - 0x10101 * (int)(all->ray->ray_len / SCALE * 8);
	step_y = all->tex[4].height / (slice_height - height_diff); 
	y = ((all->win->screen_y - slice_height) / 2);
	y1 = all->win->screen_y - y - 1;
	while (y < y1)
	{
		color = *(all->tex[4].addr + (int)((int)(step_y * i) * all->tex[4].line_length / sizeof(int) + texture_x * (all->tex[4].bits_per_pixel / 8) / sizeof(int)));
		if (color != 0x00)
			my_mlx_pixel_put(all->win, x_line, y, color);
		y++;
		i++;
	}
}