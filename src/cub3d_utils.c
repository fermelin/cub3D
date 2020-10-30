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

void		my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		set_background(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (y < (all->win->screen_y / 2))
	{
		x = 0;
		while (x < all->win->screen_x)
		{
			my_mlx_pixel_put(all->win, x, y, all->parsing.ceiling);
			x++;
		}
		y++;
	}
	while (y < all->win->screen_y)
	{
		x = 0;
		while (x < all->win->screen_x)
		{
			my_mlx_pixel_put(all->win, x, y, all->parsing.floor);
			x++;
		}
		y++;
	}
}

static void	player_dir_and_xy_init(t_all *all, char letter, int x, int y)
{
	if (letter == 'W')
		all->player->dir = M_PI;
	if (letter == 'E')
		all->player->dir = 0;
	if (letter == 'S')
		all->player->dir = 3 * M_PI_2;
	if (letter == 'N')
		all->player->dir = M_PI_2;
	all->player->x = x * SCALE + SCALE / 2;
	all->player->y = y * SCALE + SCALE / 2;
	all->parsing.player = 1;
}

void		find_player(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[y][x] == 'W' || all->map[y][x] == 'E' ||
				all->map[y][x] == 'S' || all->map[y][x] == 'N')
			{
				if (all->parsing.player == 0)
					player_dir_and_xy_init(all, all->map[y][x], x, y);
				else
					error_processor(MULTIPLE_PLAYER_ERR, all);
			}
			x++;
		}
		y++;
	}
	if (all->parsing.player == 0)
		error_processor(NO_PLAYER_ERR, all);
}
