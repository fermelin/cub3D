/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:43:37 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/10 16:43:16 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void			my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	set_background(t_all *all)
{
	int x,y;
	y = 0;
    int color;
    color = 0x00000000;
    while (y < 1080 / 2)
    {
        x = 0;
        while (x < 1920)
        {
            my_mlx_pixel_put(all->win, x, y, color);
            x++;
        }
        y++;
        if (y % 3 == 0)
            color++;
    }
    color = 0x0000FF00;
    while (y < 1080)
    {
        x = 0;
        while (x < 1920)
        {
            my_mlx_pixel_put(all->win, x, y, color);
            x++;
        }
        y++;
        if (y % 3 == 0)
            color-= 256;
    }
}

void	draw_map(t_all *all)
{
	int x;
	int y;

	x = 0;
	y = 0;
	

    while (all->map[y])
    {
        x = 0;
        while (all->map[y][x])
        {
            if (all->map[y][x] > '0' && all->map[y][x] < '3')
			   draw_square(all, x, y, all->map[y][x]);
            x++;
        }
        y++;
    }
}

void	draw_square(t_all *all, int x, int y, char c)
{
	int x1, y1, x_begin;

	y1 = 0;
	x *= SCALE;
	y *= SCALE;
	y1 = y + SCALE;
	x1 = x + SCALE;
	
	x_begin = x;
	while (y < y1)
	{
		x = x_begin;
		while (x < x1)
		{
			if (c == '1')
				my_mlx_pixel_put(all->win, x, y, 0x00FFFFFF);
        	x++;
        }
        y++;
    }	
}

void	draw_player(t_all *all)
{
	int x1, y1, x_begin;

	x1 = all->player->x + SCALE;
	y1 = all->player->y + SCALE;

	x_begin = all->player->x;
	while (all->player->y < y1)
	{
		all->player->x = x_begin;
		while (all->player->x < x1)
		{
			my_mlx_pixel_put(all->win, all->player->x, all->player->y, 0x0000FF00);
			all->player->x++;
		}
		all->player->y++;
	}
}
char	**get_map(char *config)
{
	int		fd;	
	char	*line = NULL;
	int 	i, j;
	char	**map1;
	t_list	*map;
	t_list	*tmp;

	i = j = 0;
	map = NULL;
	fd = open(config, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&map, ft_lstnew(line));
	i = ft_lstsize(map);
	if (!(map1 = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	map1[i] = NULL;
	while (map)
	{
		map1[j] = map->content;
		tmp = map;
		map = map->next;
		free(tmp);
		j++;
	}
	return (map1);
}

void	draw_screen(t_all *all)
{
	set_background(all);
	draw_map(all);
	draw_player(all);
	mlx_put_image_to_window(all->win->mlx, all->win->window, all->win->img, 0, 0);
}
int 	key_press(int key, t_all *all)
{
	if (key == 1)
		all->player->y += 1;
	else if (key == 13)
		all->player->y -= 1;
	else if (key == 2)
		all->player->x += 1;
	else if (key == 0)
		all->player->x -= 1;
	draw_screen(all);
	printf("the key is : %d\n", key);
	return (0);
}

void	find_player(t_all *all)
{
	int x;
	int y;

	x = y = 0;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[y][x] == 'W' || all->map[y][x] == 'E' || all->map[y][x] == 'S' || all->map[y][x] == 'N')
			{
				all->player->x = x * SCALE;
				all->player->y = y * SCALE;
				return ;
			}
			x++;
		}
		y++;
	}
}
int		main(int argc, char **argv)
{
	t_win		win;
	t_player	player;
	t_all		all;

	if (argc == 2)
	{
		all.player = &player;
		all.win = &win;
		win.mlx = mlx_init();
		win.window = mlx_new_window(win.mlx, 1920, 1080, "hello world!");
		win.img = mlx_new_image(win.mlx, 1920, 1080);
		win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length, &win.endian);
		all.map = get_map(argv[1]);
		find_player(&all);
		draw_screen(&all);
		mlx_hook(win.window, 2, (1L << 0), &key_press, &all);
		mlx_loop(win.mlx);
	}
	return (0);
}
