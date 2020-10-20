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

int 	key_press(int key, t_all *all)
{
	if (key == 13)
	{
		if (all->map[(int)(all->player->y / SCALE)][(int)(all->player->x / SCALE)] != '1')
		{
			all->player->x += cos(all->player->dir) * 4;
			all->player->y -= sin(all->player->dir) * 4;
		}
		else
		{
			all->player->x -= cos(all->player->dir);
			all->player->y += sin(all->player->dir);
		}
	}
	else if (key == 1)
	{
		if (all->map[(int)(all->player->y / SCALE)][(int)(all->player->x / SCALE)] != '1')
		{
			all->player->x -= cos(all->player->dir) * 4;
			all->player->y += sin(all->player->dir) * 4;
		}
		else
		{
			all->player->x += cos(all->player->dir);
			all->player->y -= sin(all->player->dir);
		}
	}
	else if (key == 2)
		all->player->dir -= 0.1;
	else if (key == 0)
		all->player->dir += 0.1;
	else if (key == 53)
	{
		//printf ("%f\n", FOV);
		//printf("ppp is %d\n", all->player->projection_plan);
		mlx_destroy_window(all->win->mlx, all->win->window);
		exit (0);
	}
	draw_screen(all);
	//printf("the key is : %d\n", key);
	return (0);
}