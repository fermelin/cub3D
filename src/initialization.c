
#include "cub3d.h"

void		get_textures(t_all *all)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if ((ft_strncmp(".xpm", (all->tex[i].path + (ft_strlen(
			all->tex[i].path) - 4)), 4)))
			return (error_processor(TPATH_EXT_ERR, all));
		if (!(all->tex[i].img = mlx_xpm_file_to_image(all->win->mlx,
			all->tex[i].path, &all->tex[i].width, &all->tex[i].height)))
			return (error_processor(TPATH_ERR, all));
		all->tex[i].addr = (int*)mlx_get_data_addr(all->tex[i].img, &all->tex
			[i].bits_per_pixel, &all->tex[i].line_length, &all->tex[i].endian);
		all->tex[i].step_x = (all->tex[i].width >= SCALE) ? ((double)all->tex
			[i].width / SCALE) : 1 / ((double)SCALE / all->tex[i].width);
		i++;
	}
}

void		get_initial_params(t_all *all)
{
	all->player->projection_plane = (all->win->screen_x / 2) / (tan(FOV / 2));
	all->minimap_scale = (all->win->screen_x + all->win->screen_y) / 2 / 100;
	if (all->minimap_scale * all->win->map_x > all->win->screen_x ||
		all->minimap_scale * all->win->map_y > all->win->screen_y)
		all->minimap_scale = 0;
	find_player(all);
	get_textures(all);
}

void		win_and_image_init(t_all *all)
{
	all->win->mlx = mlx_init();
	mlx_get_screen_size(all->win->mlx, &all->win->screen_x,
		&all->win->screen_y);
	all->win->img = mlx_new_image(all->win->mlx, all->win->screen_x,
		all->win->screen_y);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bits_per_pixel
		, &all->win->line_length, &all->win->endian);
}

static void	struct_init_2(t_all *all)
{
	all->movements.up = 0;
	all->movements.down = 0;
	all->movements.left = 0;
	all->movements.right = 0;
	all->movements.rot_left = 0;
	all->movements.rot_right = 0;
}

void		struct_init(t_all *all)
{
	int i;

	i = 0;
	while (i < 5)
	{
		all->tex[i].path = NULL;
		all->tex[i].img = NULL;
		all->tex[i].addr = NULL;
		all->parsing.tex[i] = 0;
		i++;
	}
	all->map = NULL;
	all->sprite = NULL;
	all->errnum = 0;
	all->win->map_x = 0;
	all->win->map_y = 0;
	all->win->img = NULL;
	all->win->window = NULL;
	all->parsing.is_floor = 0;
	all->parsing.is_ceiling = 0;
	all->parsing.resolution = 0;
	all->parsing.player = 0;
	all->sprites_amount = 0;
	all->screenshot = 0;
	struct_init_2(all);
}
