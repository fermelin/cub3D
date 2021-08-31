
#include "cub3d.h"

static int	choose_texture(t_all *all)
{
	if (all->ray->what_intersection == 1 && all->ray->is_right)
		return (0);
	else if (all->ray->what_intersection == 0 && all->ray->is_up)
		return (1);
	else if (all->ray->what_intersection == 1 && all->ray->is_left)
		return (2);
	else
		return (3);
}

static void	line_drawing(t_all *all, double slice_height, int txt_nbr,
	double height_diff)
{
	int		y;
	int		y1;
	int		color;
	double	step_y;
	int		i;

	i = 0;
	if (slice_height > all->win->screen_y)
	{
		i = (slice_height - all->win->screen_y) / 2;
		height_diff = all->win->screen_y - slice_height;
		slice_height = all->win->screen_y;
	}
	step_y = all->tex[txt_nbr].height / (slice_height - height_diff);
	y = ((all->win->screen_y - slice_height) / 2);
	y1 = all->win->screen_y - y - 1;
	while (y < y1)
	{
		color = *(all->tex[txt_nbr].addr + (int)((int)(step_y * i) * all->tex
			[txt_nbr].line_length / sizeof(int) + all->texture_x * (all->tex
				[txt_nbr].bits_per_pixel / 8) / sizeof(int)));
		my_mlx_pixel_put(all->win, all->ray->x_line, y, color);
		y++;
		i++;
	}
}

void		draw_vertical_line(t_all *all, double start)
{
	double	slice_height;
	double	height_diff;
	int		txt_nbr;

	slice_height = 0;
	height_diff = 0;
	all->ray->ray_intersection = (all->ray->what_intersection == 0) ?
	all->ray->intersection_x : all->ray->intersection_y;
	txt_nbr = choose_texture(all);
	all->ray->ray_fixed = all->ray->ray_len * cos(start - all->player->dir);
	all->texture_x = (int)((int)all->ray->ray_intersection % SCALE *
		all->tex[txt_nbr].step_x) % all->tex[txt_nbr].width;
	if (all->ray->ray_fixed != 0)
		slice_height = (int)(SCALE * all->player->projection_plane /
			all->ray->ray_fixed);
	line_drawing(all, slice_height, txt_nbr, height_diff);
}
