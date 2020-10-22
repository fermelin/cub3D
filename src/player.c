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
/*	keys: A = 0 S = 1 D = 2 W = 13 
**   	  left = 123 down = 125 right = 124 up = 126
*/

void		is_wall_close(t_all *all)
{
	if (all->map[(int)((all->player->y - SCALE / 2) / SCALE)]
	[(int)((all->player->x) / SCALE)] != '1')				//up
		all->walls.is_up = 0;
	else 
		all->walls.is_up = 1;
	if (all->map[(int)((all->player->y) / SCALE)]
	[(int)((all->player->x - SCALE / 2) / SCALE)] != '1')	//left
		all->walls.is_left = 0;
	else
		all->walls.is_left = 1;
	if (all->map[(int)((all->player->y + SCALE / 2) / SCALE)]
	[(int)((all->player->x) / SCALE)] != '1')				//down
		all->walls.is_down = 0;
	else
		all->walls.is_down = 1;
	if (all->map[(int)((all->player->y) / SCALE)]
	[(int)((all->player->x + SCALE / 2) / SCALE)] != '1')	//right
		all->walls.is_right = 0;
	else
		all->walls.is_right = 1;
}

int		player_movement(t_all *all)
{
	if (all->movements.rot_right)
		all->player->dir -= 0.06;
	if (all->movements.rot_left)
		all->player->dir += 0.06;
	is_wall_close(all);
	if (all->movements.up)
	{
		if ((all->walls.is_up && (all->walls.is_left || all->walls.is_right)) || (all->walls.is_down && (all->walls.is_left || all->walls.is_right)))
		{
			if ((!(all->walls.is_right) && cos(all->player->dir) > 0) || (!(all->walls.is_left) && cos(all->player->dir) < 0))
				all->player->y -= cos(all->player->dir) * SCALE / 8;
			else if ((!(all->walls.is_up) && sin(all->player->dir) > 0) || (!(all->walls.is_down) && sin(all->player->dir) < 0))
				all->player->y -= sin(all->player->dir) * SCALE / 8;
		}
		else if ((all->walls.is_up && sin(all->player->dir) > 0) || (all->walls.is_down && sin(all->player->dir) < 0))
			all->player->x += cos(all->player->dir) * SCALE / 8;
		else if ((all->walls.is_right && cos(all->player->dir) > 0) || (all->walls.is_left && cos(all->player->dir) < 0))
			all->player->y -= sin(all->player->dir) * SCALE / 8;
		else
		{
			all->player->x += cos(all->player->dir) * SCALE / 8;
			all->player->y -= sin(all->player->dir) * SCALE / 8;
		}
	}	
	if (all->movements.down)
	{
		if (all->map[(int)((all->player->y + 1) / SCALE)][(int)((all->player->x + 1) / SCALE)] != '1')
		{
			all->player->x -= cos(all->player->dir) * SCALE / 8;
			all->player->y += sin(all->player->dir) * SCALE / 8;
		}
		else if (all->map[(int)((all->player->y + SCALE) / SCALE)][(int)((all->player->x + SCALE) / SCALE)] != '1')
			all->player->x += cos(all->player->dir) * SCALE / 8;
		else if (all->map[(int)((all->player->y + 1) / SCALE)][(int)((all->player->x + 1) / SCALE)] != '1')
			all->player->y -= sin(all->player->dir) * SCALE / 8;
	}
	draw_screen(all);
	return (0);
}
int 	key_press(int key, t_all *all)
{
	if (key == 13)
		all->movements.up = 1;
	else if (key == 1)
		all->movements.down = 1;
	else if (key == 2)
		all->movements.rot_right = 1;
	else if (key == 0)
		all->movements.rot_left = 1;
	else if (key == 53)
	{
		//printf ("%f\n", FOV);
		//printf("ppp is %d\n", all->player->projection_plan);
		mlx_destroy_window(all->win->mlx, all->win->window);
		exit (0);
	}
	//draw_screen(all);
	printf("pressed key is : %d\n", key);
	return (0);
}

int		key_release(int key, t_all *all)
{
	if (key == 13)
		all->movements.up = 0;
	else if (key == 1)
		all->movements.down = 0;
	else if (key == 2)
		all->movements.rot_right = 0;
	else if (key == 0)
		all->movements.rot_left = 0;
	printf("released key is : %d\n", key);
	return (0);

}

