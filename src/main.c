
#include "cub3d.h"

int			draw_screen(t_all *all)
{
	set_background(all);
	draw_scene(all);
	if (all->minimap_scale != 0)
		draw_minimap(all);
	if (!all->screenshot)
		mlx_put_image_to_window(all->win->mlx, all->win->window, all->win->img,
			0, 0);
	return (0);
}

int			destroy_all(t_all *all)
{
	int i;

	i = all->win->map_y;
	while (i != 0)
	{
		free(all->map[--i]);
		all->map[i] = NULL;
	}
	free(all->map);
	while (i < 5)
	{
		if (all->tex[i].img)
			mlx_destroy_image(all->win->mlx, all->tex[i].img);
		free(all->tex[i].path);
		all->tex[i++].path = NULL;
	}
	free(all->sprite);
	if (all->win->img)
		mlx_destroy_image(all->win->mlx, all->win->img);
	if (all->win->window)
		mlx_destroy_window(all->win->mlx, all->win->window);
	exit(all->errnum);
}

static void	check_args(int argc, char **argv, t_all *all)
{
	if (argc < 2 || argc > 3)
		error_processor(WRONG_NUMBER_OF_ARGS_ERR, all);
	else if (ft_strncmp(".cub", (argv[1] + (ft_strlen(argv[1]) - 4)), 4) != 0)
		error_processor(WRONG_CON_EX_ERR, all);
}

int			main(int argc, char **argv)
{
	t_all		all;
	t_win		win;
	t_ray		ray;
	t_player	player;

	all.win = &win;
	all.player = &player;
	all.ray = &ray;
	struct_init(&all);
	check_args(argc, argv, &all);
	win_and_image_init(&all);
	parser(argv[1], &all);
	get_initial_params(&all);
	if (argc == 3)
		make_screenshot(&all, argv[2]);
	win.window = mlx_new_window(win.mlx, win.screen_x, win.screen_y, "cub3D");
	mlx_hook(win.window, 2, (1L << 0), &key_press, &all);
	mlx_hook(win.window, 3, (1L << 1), &key_release, &all);
	mlx_hook(win.window, 17, (1L << 17), &destroy_all, &all);
	mlx_loop_hook(win.mlx, &player_movement, &all);
	mlx_loop(win.mlx);
	return (0);
}
