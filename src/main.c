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







int		draw_screen(t_all *all)
{
	
	set_background(all);
	draw_scene(all);
	draw_map(all);
	if (!all->screenshot)
		mlx_put_image_to_window(all->win->mlx, all->win->window, all->win->img, 0, 0);
	return (0);
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
		all->parsing.tex[i] = 0;
		i++;
	}
	all->parsing.is_floor = 0;
	all->parsing.is_ceiling = 0;
	all->parsing.resolution = 0;
	all->parsing.player = 0;
	
	all->movements.up = 0;
	all->movements.down = 0;
	all->movements.left = 0;
	all->movements.right = 0;
	all->movements.rot_left = 0;
	all->movements.rot_right = 0;

	all->screenshot = 0;
}
void	win_and_image_init(t_all *all)
{
	all->win->mlx = mlx_init();
	mlx_get_screen_size(all->win->mlx, &all->win->screen_x, &all->win->screen_y);
	all->win->img = mlx_new_image(all->win->mlx, all->win->screen_x, all->win->screen_y);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bits_per_pixel, &all->win->line_length, &all->win->endian);
}

void	check_args(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		error_processor(WRONG_NUMBER_OF_ARGS_ERR);
	else if (ft_strncmp(".cub", (argv[1] + (ft_strlen(argv[1]) - 4)), 4) != 0)
		error_processor(WRONG_CONFIG_EXTENSION_ERR);
}

int		main(int argc, char **argv)
{

	t_all		all;
	t_win 		win;
	t_ray		ray;
	t_player	player;

	all.win = &win;
	all.player = &player;
	all.ray = &ray;

	check_args(argc, argv);
	
	struct_init(&all);
	win_and_image_init(&all);
	parser(argv[1], &all);
	all.player->projection_plane = (win.screen_x / 2) / (tan(FOV / 2));
	find_player(&all);
	get_textures(&all);
	all.minimap_scale = (win.screen_x + win.screen_y) / 2 / 100;
	
	if (argc == 3)
		make_screenshot(&all, argv[2]);
		
	win.window = mlx_new_window(win.mlx, win.screen_x, win.screen_y, "cub3D");
		




		mlx_do_key_autorepeaton(win.mlx); //надо ли?
		mlx_do_sync(win.mlx); //надо ли?


		// printf("%d\n", all.win->map_y);
		mlx_hook(win.window, 2, (1L << 0), &key_press, &all);
		mlx_hook(win.window, 3, (1L << 1), &key_release, &all);
		mlx_loop_hook(win.mlx, &player_movement, &all);
		mlx_loop(win.mlx);
	
	return (0);
}
