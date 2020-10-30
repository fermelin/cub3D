/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:55:07 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/16 12:55:29 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_wall_close(t_all *all)
{
	if (all->map[(int)((all->player->y - SCALE / 2) / SCALE)]
	[(int)((all->player->x) / SCALE)] != '1')
		all->walls.is_up = 0;
	else
		all->walls.is_up = 1;
	if (all->map[(int)((all->player->y) / SCALE)]
	[(int)((all->player->x - SCALE / 2) / SCALE)] != '1')
		all->walls.is_left = 0;
	else
		all->walls.is_left = 1;
	if (all->map[(int)((all->player->y + SCALE / 2) / SCALE)]
	[(int)((all->player->x) / SCALE)] != '1')
		all->walls.is_down = 0;
	else
		all->walls.is_down = 1;
	if (all->map[(int)((all->player->y) / SCALE)]
	[(int)((all->player->x + SCALE / 2) / SCALE)] != '1')
		all->walls.is_right = 0;
	else
		all->walls.is_right = 1;
}

static void	move_up_or_down(t_all *all)
{
	int sign;

	sign = (all->movements.up == 1) ? 1 : -1;
	if ((all->walls.is_up && (all->walls.is_left || all->walls.is_right))
		|| (all->walls.is_down && (all->walls.is_left || all->walls.is_right)))
	{
		if ((!(all->walls.is_right) && sign * all->player->cos_dir > 0)
			|| (!(all->walls.is_left) && sign * all->player->cos_dir < 0))
			all->player->x += sign * all->player->cos_dir * SCALE / 8;
		else if ((!(all->walls.is_up) && sign * all->player->sin_dir > 0)
			|| (!(all->walls.is_down) && sign * all->player->sin_dir < 0))
			all->player->y -= sign * all->player->sin_dir * SCALE / 8;
	}
	else if ((all->walls.is_up && sign * all->player->sin_dir > 0)
		|| (all->walls.is_down && sign * all->player->sin_dir < 0))
		all->player->x += sign * all->player->cos_dir * SCALE / 8;
	else if ((all->walls.is_right && sign * all->player->cos_dir > 0)
		|| (all->walls.is_left && sign * all->player->cos_dir < 0))
		all->player->y -= sign * all->player->sin_dir * SCALE / 8;
	else
	{
		all->player->x += sign * all->player->cos_dir * SCALE / 8;
		all->player->y -= sign * all->player->sin_dir * SCALE / 8;
	}
}

static void	move_left_or_right(t_all *all)
{
	int sign;

	sign = (all->movements.left == 1) ? 1 : -1;
	if ((all->walls.is_up && (all->walls.is_left || all->walls.is_right))
		|| (all->walls.is_down && (all->walls.is_left || all->walls.is_right)))
	{
		if ((!(all->walls.is_right) && sign * all->player->sin_dir < 0)
			|| (!(all->walls.is_left) && sign * all->player->sin_dir > 0))
			all->player->x -= sign * all->player->sin_dir * SCALE / 8;
		else if ((!(all->walls.is_up) && sign * all->player->cos_dir > 0)
			|| (!(all->walls.is_down) && sign * all->player->cos_dir < 0))
			all->player->y -= sign * all->player->cos_dir * SCALE / 8;
	}
	else if ((all->walls.is_up && sign * all->player->cos_dir > 0)
		|| (all->walls.is_down && sign * all->player->cos_dir < 0))
		all->player->x -= sign * all->player->sin_dir * SCALE / 8;
	else if ((all->walls.is_right && sign * all->player->sin_dir < 0)
		|| (all->walls.is_left && sign * all->player->sin_dir > 0))
		all->player->y -= sign * all->player->cos_dir * SCALE / 8;
	else
	{
		all->player->x -= sign * all->player->sin_dir * SCALE / 8;
		all->player->y -= sign * all->player->cos_dir * SCALE / 8;
	}
}

static void	get_player_direction(t_all *all)
{
	all->player->is_dir_right = 0;
	all->player->is_dir_left = 0;
	all->player->is_dir_up = 0;
	all->player->is_dir_down = 0;
	all->player->cos_dir = cos(all->player->dir);
	all->player->sin_dir = sin(all->player->dir);
	if (all->player->cos_dir > 0)
		all->player->is_dir_right = 1;
	else if (all->player->cos_dir < 0)
		all->player->is_dir_left = 1;
	if (all->player->sin_dir > 0)
		all->player->is_dir_up = 1;
	else if (all->player->sin_dir < 0)
		all->player->is_dir_down = 1;
}

int			player_movement(t_all *all)
{
	if (all->movements.rot_right)
		all->player->dir -= 0.06;
	if (all->movements.rot_left)
		all->player->dir += 0.06;
	is_wall_close(all);
	if (all->movements.up || all->movements.down)
	{
		get_player_direction(all);
		move_up_or_down(all);
	}
	if (all->movements.left || all->movements.right)
	{
		get_player_direction(all);
		move_left_or_right(all);
	}
	draw_screen(all);
	return (0);
}
