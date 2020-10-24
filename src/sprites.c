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

void	sprites_counter(t_all *all) //with malloc
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
			if (all->map[y][x] == '2')
				all->sprites_amount++;
			x++;
		}
		y++;
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
				if (all->map[y][x] == '2')
				{
					all->sprite[i].x = x * SCALE + SCALE / 2;
					all->sprite[i].y = y * SCALE + SCALE / 2;
					// printf("%d sprite.x is %f\nsprite.y is %f\n", i, all->sprite[i].x, all->sprite[i].y);
					i++;
				}
				x++;
			}
			y++;
		}
	}
}

double	get_delta_angle(double start, double sprite_angle)
{
	double delta_angle;

	delta_angle = start - sprite_angle;
	if (delta_angle <= -M_PI)
		delta_angle += 2 * M_PI;
	else if (delta_angle >= M_PI)
		delta_angle -= 2 * M_PI;
	return (delta_angle);
}

void	get_sprites_params(t_all *all, int i)
{
	double	start;

	all->sprite[i].dist = hypot(all->sprite[i].x - all->player->x, all->sprite[i].y - all->player->y);
	sort_sprites(all);
	start = all->player->dir + (FOV / 2);
	all->sprite[i].angle = atan2(all->player->y - all->sprite[i].y, all->sprite[i].x - all->player->x);
	all->sprite[i].size = (SCALE / all->sprite[i].dist) * all->player->projection_plane;
	all->sprite[i].delta_angle = get_delta_angle(start, all->sprite[i].angle);
	all->sprite[i].hor_offset = (all->sprite[i].delta_angle / (FOV / all->win->screen_x) - all->sprite[i].size / 2);
	all->sprite[i].vert_offset = (all->win->screen_y / 2 - all->sprite[i].size / 2);
	// printf("s%d angle is %f\n", i, all->sprite[i].angle);
	 // printf("%d dist is %f\n", i, all->sprite[i].dist);
	
}

void	sort_sprites(t_all *all)
{
	int i;
	t_sprite temp;

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


int 	get_sprite_color(t_all *all, int x_line, int y, int i)
{
	int color;
	int texture_x;
	int texture_y;

	texture_y = y * (all->tex[4].height - 1) / (all->sprite[i].size - 1);
	texture_x = (x_line - all->sprite[i].hor_offset) * (all->tex[4].width - 1) / (all->sprite[i].size - 1);
	color = *(all->tex[4].addr +(int)((int)(texture_y) * all->tex[4].line_length / sizeof(int) +
		texture_x * (all->tex[4].bits_per_pixel / 8) / sizeof(int)));
	return (color);
}
void	draw_sprites(t_all *all)
{
	int 	y;
	int 	x_line;
	double 	slice_height;
	int 	color;
	int i;
	// double	ray_intersection;
	// double	step_y;
	// int 	texture_x;
	// int 	texture_y;
	double	height_diff;

	x_line  = 0;
	slice_height = 0;
	i = 0;
	height_diff = 0;
	//ray_intersection = (all->ray->what_intersection == 0) ? all->ray->intersection_x : all->ray->intersection_y;
	//texture_x = (int)ray_intersection % SCALE % (all->tex[4].width);
	//printf("all->sprite[i].size is %24f\n", all->sprite[i].size);

	// color = 0xFFFFFF;
	//color = 0xFFFFFF - 0x10101 * (int)(all->sprite[i] / SCALE * 8);
	//step_y = all->tex[4].height / (all->sprite[i].size - height_diff); 
	while (i < all->sprites_amount)
	{
		// printf("i = %d\n", i);
		get_sprites_params(all, i);
		x_line  = 0;
		if (all->sprite[i].size > all->win->screen_y)
		{
			all->sprite[i].size = 0;
			// i = (all->sprite[i].size - all->win->screen_y) / 2;
			// height_diff = all->win->screen_y - all->sprite[i].size;
			// all->sprite[i].size = all->win->screen_y;
		}
		while (x_line < all->win->screen_x)
		{
			if (x_line >= all->sprite[i].hor_offset && x_line <= all->sprite[i].hor_offset + all->sprite[i].size && all->sprite[i].dist < all->ray->array_lens[x_line])
			{
				y = 0;
				while (y < all->sprite[i].size)
				{
					color = get_sprite_color(all, x_line, y, i);
					if (color != 0x0)
						my_mlx_pixel_put(all->win, x_line, (int)(all->sprite[i].vert_offset + y), color);
					y++;
				}
			}
			x_line++;
		}
		i++;
	}
	//color = *(all->tex[4].addr + (int)((int)(step_y * j) * all->tex[4].line_length / sizeof(int) + texture_x * (all->tex[4].bits_per_pixel / 8) / sizeof(int)));
	// j++;
}














