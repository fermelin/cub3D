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
    color = 0x000000FF;
    while (y < all->win->size_y / 2)
    {
        x = 0;
        while (x < all->win->size_x)
        {
            my_mlx_pixel_put(all->win, x, y, color);
            x++;
        }
        y++;
        if (y % 3 == 0)
            color--;
    }
    color = 0x00000000;
    while (y < all->win->size_y)
    {
        x = 0;
        while (x < all->win->size_x)
        {
            my_mlx_pixel_put(all->win, x, y, color);
            x++;
        }
        y++;
        if (y % 3 == 0) //исправить, чтобы зависело от разрешения экрана
            color+= 256;
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

void	cast_rays(t_all *all)
{
	t_player ray;
	double	start;
	double	end;
	double 	ray_len;
	double 	x_line;

	ray = *all->player;
	start = ray.dir - (M_PI / 6);
	end = ray.dir + (M_PI / 6);
	x_line = 0;

	while (start <= end)
	{
		ray.x = all->player->x;
		ray.y = all->player->y;
		while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);	
			my_mlx_pixel_put(all->win, ray.x, ray.y, 0x00FF0000);
		}
		ray_len = hypot((all->player->x - ray.x), (all->player->y - ray.y)) * cos(start - ray.dir);
		printf("%f\n", ray_len);
		x_line++;
		draw_vertical_line(all, ray_len, x_line);
		start += (M_PI / 3) / all->win->size_x;
	}
}

void	draw_vertical_line(t_all *all, double ray_len, double x_line)
{
	int y, y1;
	double slice_height;

	slice_height = 0;
	if (ray_len != 0)
		slice_height = (int)((SCALE / ray_len * all->win->size_x * 0.83));
	printf("%f\n", slice_height);
	if (slice_height > all->win->size_y)
		slice_height = all->win->size_y;
	y = ((all->win->size_y - slice_height) / 2);
	y1 = all->win->size_y - y;
	while (y < y1)
	{
		my_mlx_pixel_put(all->win, x_line, y, 0x00FFFFFF);
		y++;
	}
}

void	draw_player(t_all *all)
{
	int x1, y1, x_begin, x, y;

	x1 = all->player->x + SCALE / 2;
	y1 = all->player->y + SCALE / 2;
	x = all->player->x - SCALE / 2;
	y = all->player->y - SCALE / 2;
	x_begin = x;
	while (y < y1)
	{
		x = x_begin;
		while (x < x1)
		{
			my_mlx_pixel_put(all->win, x, y, 0x0000FF00);
			x++;
		}
		y++;
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

int	draw_screen(t_all *all)
{
	set_background(all);
	draw_map(all);
	cast_rays(all);
	draw_player(all);
	mlx_put_image_to_window(all->win->mlx, all->win->window, all->win->img, 0, 0);
	return (0);
}

int 	key_press(int key, t_all *all)
{
	if (key == 13)
	{
		if (all->map[(int)(all->player->y / SCALE)][(int)(all->player->x / SCALE)] != '1')
		{
			all->player->x += cos(all->player->dir) * 4;
			all->player->y += sin(all->player->dir) * 4;
		}
	}
	else if (key == 1)
	{
		if (all->map[(int)(all->player->y / SCALE)][(int)(all->player->x / SCALE)] != '1')
		{
			all->player->x -= cos(all->player->dir) * 4;
			all->player->y -= sin(all->player->dir) * 4;
		}
	}
	else if (key == 2)
		all->player->dir += 0.1;
	else if (key == 0)
		all->player->dir -= 0.1;
	else if (key == 53)
	{
		mlx_destroy_window(all->win->mlx, all->win->window);
		exit (0);
	}
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
				all->player->x = x * SCALE + SCALE / 2;
				all->player->y = y * SCALE + SCALE / 2;
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
		mlx_get_screen_size(win.mlx, &win.size_x, &win.size_y);
		win.window = mlx_new_window(win.mlx, win.size_x, win.size_y, "hello world!");
		win.img = mlx_new_image(win.mlx, win.size_x, win.size_y);
		win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length, &win.endian);
		all.map = get_map(argv[1]);
		player.dir = 0;
		player.projection_plan = win.size_x / (tan(M_PI / 6) * 2);
		printf("%d\n", player.projection_plan);
		find_player(&all);
		draw_screen(&all);
		mlx_hook(win.window, 2, (1L << 0), &key_press, &all);
		mlx_loop(win.mlx);
	}
	return (0);
}
