/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:17:20 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/30 16:17:23 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	keys: A = 0 S = 1 D = 2 W = 13
**	left = 123 down = 125 right = 124 up = 126
*/
#include "cub3d.h"

int	key_press(int key, t_all *all)
{
	if (key == 124)
		all->movements.rot_right = 1;
	else if (key == 123)
		all->movements.rot_left = 1;
	else if (key == 13)
		all->movements.up = 1;
	else if (key == 1)
		all->movements.down = 1;
	else if (key == 0)
		all->movements.left = 1;
	else if (key == 2)
		all->movements.right = 1;
	else if (key == 53)
		destroy_all(all);
	return (0);
}

int	key_release(int key, t_all *all)
{
	if (key == 124)
		all->movements.rot_right = 0;
	else if (key == 123)
		all->movements.rot_left = 0;
	else if (key == 13)
		all->movements.up = 0;
	else if (key == 1)
		all->movements.down = 0;
	else if (key == 0)
		all->movements.left = 0;
	else if (key == 2)
		all->movements.right = 0;
	return (0);
}
