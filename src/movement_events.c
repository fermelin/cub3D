
/*
**	keys: A = 0 S = 1 D = 2 W = 13
**	left = 123 down = 125 right = 124 up = 126
*/
#include "cub3d.h"

int	key_press(int key, t_all *all)
{
	if (key == ROT_RIGHT)
		all->movements.rot_right = 1;
	else if (key == ROT_LEFT)
		all->movements.rot_left = 1;
	else if (key == UP)
		all->movements.up = 1;
	else if (key == DOWN)
		all->movements.down = 1;
	else if (key == LEFT)
		all->movements.left = 1;
	else if (key == RIGHT)
		all->movements.right = 1;
	else if (key == ESC)
		destroy_all(all);
	return (0);
}

int	key_release(int key, t_all *all)
{
	if (key == ROT_RIGHT)
		all->movements.rot_right = 0;
	else if (key == ROT_LEFT)
		all->movements.rot_left = 0;
	else if (key == UP)
		all->movements.up = 0;
	else if (key == DOWN)
		all->movements.down = 0;
	else if (key == LEFT)
		all->movements.left = 0;
	else if (key == RIGHT)
		all->movements.right = 0;
	return (0);
}
