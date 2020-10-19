/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:43:37 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/16 11:10:48 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //deletedeletedeletedeletedeletedeeltedeletedeletedeleteedleteeldeetledeeltedelet


void	draw_vertical_line(t_all *all, double ray_len, int x_line)
{
	int 	y;
	int 	y1;
	double 	slice_height;
	int 	color;
	double	ray_intersection;
	double	step_y;
	int 	i;
	int 	texture_x;

	slice_height = 0;
	i = 0;
	ray_intersection = (all->ray->what_intersection == 0) ? all->ray->intersection_x : all->ray->intersection_y;
	texture_x = (int)ray_intersection % all->texture->width;
	if (ray_len != 0)
		slice_height = (int)(SCALE / ray_len * all->player->projection_plan);
	//printf("slice_height is %24f\n", slice_height);
	if (slice_height > all->win->screen_y)
		slice_height = all->win->screen_y;
	//color = 0xFFFFFF - 0x10101 * (int)(ray_len / SCALE * 8);
	step_y = all->texture->height / (slice_height); 
	y = ((all->win->screen_y - slice_height) / 2);
	y1 = all->win->screen_y - y;
	while (y < y1)
	{
		color = *(all->texture->addr + ((int)(step_y * i) * all->texture->line_length + texture_x * (all->texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(all->win, x_line, y, color);
		y++;
		i++;
	}
}

int		draw_screen(t_all *all)
{
	set_background(all);
	cast_rays(all);
	draw_map(all);
	mlx_put_image_to_window(all->win->mlx, all->win->window, all->win->img, 0, 0);
	return (0);
}

void	get_textures(t_all *all)
{
	all->texture->img = mlx_xpm_file_to_image(all->win->mlx, "./textures/redbrick.xpm", &all->texture->width, &all->texture->height);
	all->texture->addr = mlx_get_data_addr(all->texture->img, &all->texture->bits_per_pixel, &all->texture->line_length, &all->texture->endian);
}

// t_all	struct_init(void)
// {
// 	t_all		all;
// 	t_ray		ray;
// 	t_texture	texture;
// 	t_player	player;

// 	player.x = 0;
// 	player.y = 0;
// 	all.map = NULL;
// 	all.player = &player;
// 	all.ray = &ray;
// 	all.texture = &texture;

// 	return (all);
// }

int		main(int argc, char **argv)
{

	t_all		all;
	t_win 		win;
	t_ray		ray;
	t_texture	texture;
	t_player	player;

	if (argc != 2)
		printf("invalid argument\n");
	else
	{
		// all = struct_init();
		all.win = &win;
		all.player = &player;
		all.ray = &ray;
		all.texture = &texture;

		win.mlx = mlx_init();
		mlx_get_screen_size(win.mlx, &win.screen_x, &win.screen_y);
		win.window = mlx_new_window(win.mlx, win.screen_x, win.screen_y, "cub3D");
		win.img = mlx_new_image(win.mlx, win.screen_x, win.screen_y);
		win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length, &win.endian);

		all.map = get_map(argv[1], &all);
		all.player->projection_plan = (win.screen_x / 2) / (tan(FOV / 2));
		find_player(&all);
		get_textures(&all);
		draw_screen(&all);
		mlx_hook(win.window, 2, (1L << 0), &key_press, &all);
		mlx_loop(win.mlx);
	}
	return (0);
}
