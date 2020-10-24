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

int	choose_texture(t_all *all)
{
	if (all->ray->what_intersection == 1 && all->ray->is_right)
		return(0);
	if (all->ray->what_intersection == 0 && all->ray->is_up)
		return(1);
	if (all->ray->what_intersection == 1 && all->ray->is_left)
		return(2);
	if (all->ray->what_intersection == 0 && all->ray->is_down)
		return(3);
	return (4);
}

void	draw_vertical_line(t_all *all, int x_line)
{
	int 	y;
	int 	y1;
	double 	slice_height;
	int 	color;
	double	ray_intersection;
	double	step_y;
	int 	i;
	int 	texture_x;
	double	height_diff;
	int 	txt_nbr;

	slice_height = 0;
	i = 0;
	height_diff = 0;
	ray_intersection = (all->ray->what_intersection == 0) ? all->ray->intersection_x : all->ray->intersection_y;
	txt_nbr = choose_texture(all);
	texture_x = (int)ray_intersection % SCALE % (all->tex[txt_nbr].width);
	if (all->ray->ray_len != 0)
		slice_height = (int)(SCALE * all->player->projection_plane / all->ray->ray_len);
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
		color = *(all->tex[txt_nbr].addr + (int)((int)(step_y * i) * all->tex[txt_nbr].line_length / sizeof(int) + texture_x * (all->tex[txt_nbr].bits_per_pixel / 8) / sizeof(int)));
		my_mlx_pixel_put(all->win, x_line, y, color);
		y++;
		i++;
	}
}

int		draw_screen(t_all *all)
{
	
	set_background(all);
	draw_scene(all);
	draw_sprites(all);
	draw_map(all);
	mlx_put_image_to_window(all->win->mlx, all->win->window, all->win->img, 0, 0);
	return (0);
}

void	get_textures(t_all *all)
{
	int i;

	i = 0;
	while (i < 5)
	{
		all->tex[i].img = mlx_xpm_file_to_image(all->win->mlx, all->tex[i].path, &all->tex[i].width, &all->tex[i].height);
		all->tex[i].addr = (int*)mlx_get_data_addr(all->tex[i].img, &all->tex[i].bits_per_pixel, &all->tex[i].line_length, &all->tex[i].endian);
		i++;
	}
}

void	struct_init(t_all *all)
{
	int i;

	i = 0;
	while (i < 5)
	{
		all->tex[i].path = NULL;
		all->tex[i].img = NULL;
		all->tex[i].addr = NULL;
		i++;
	}

	all->movements.up = 0;
	all->movements.down = 0;
	all->movements.left = 0;
	all->movements.right = 0;
	all->movements.rot_left = 0;
	all->movements.rot_right = 0;
	all->parsing.no_tex = 0;
	all->parsing.ea_tex = 0;
	all->parsing.we_tex = 0;
	all->parsing.so_tex = 0;
	all->parsing.s_tex = 0;
	all->parsing.resolution = 0;
}

int		main(int argc, char **argv)
{

	t_all		all;
	t_win 		win;
	t_ray		ray;
	t_player	player;

	if (argc != 2)
		printf("invalid argument\n");
	else
	{
		all.win = &win;
		all.player = &player;
		all.ray = &ray;
		struct_init(&all);

		win.mlx = mlx_init();
		mlx_get_screen_size(win.mlx, &win.screen_x, &win.screen_y);
		parser(argv[1], &all);
		win.window = mlx_new_window(win.mlx, win.screen_x, win.screen_y, "cub3D");
		win.img = mlx_new_image(win.mlx, win.screen_x, win.screen_y);
		win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length, &win.endian);
		mlx_do_key_autorepeaton(win.mlx); //надо ли?
		mlx_do_sync(win.mlx); //надо ли?
		if (!(ray.array_lens = (double*)malloc(sizeof(double) * (win.screen_x + 1))))
			return (0);
		all.player->projection_plane = (win.screen_x / 2) / (tan(FOV / 2));
		find_player(&all);
		get_textures(&all);
		printf("%d\n", all.win->map_y);
		// draw_screen(&all);
		mlx_hook(win.window, 2, (1L << 0), &key_press, &all);
		mlx_hook(win.window, 3, (1L << 1), &key_release, &all);
		mlx_loop_hook(win.mlx, &player_movement, &all);
		mlx_loop(win.mlx);
	}
	return (0);
}
