
#include "cub3d.h"

void	sprites_counter(t_all *all)
{
	int	x;
	int	y;

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
		if (!(all->sprite = (t_sprite*)malloc(sizeof(t_sprite) *
			all->sprites_amount)))
			error_processor(MALLOC_ERR, all);
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
					i++;
				}
				x++;
			}
			y++;
		}
	}
}
