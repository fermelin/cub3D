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
    while (y < all->win->screen_y / 2)
    {
        x = 0;
        while (x < all->win->screen_x)
        {
            my_mlx_pixel_put(all->win, x, y, color);
            x++;
        }
        y++;
        if (y % 3 == 0)
            color--;
    }
    color = 0x00000000;
    while (y < all->win->screen_y)
    {
        x = 0;
        while (x < all->win->screen_x)
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
	t_player ray_new;
	double	start;
	double	end;
	double 	ray_len;
	int 	x_line;
	double	ray_hor;
	double	ray_vert;
	ray = *all->player;
	ray_new = *all->player;
	start = ray.dir - (M_PI / 6);
	end = ray.dir + (M_PI / 6);
	printf("end is %24f\n", end);
	x_line = 0;

	while (start < end)
	{
		ray.x = all->player->x;
		ray.y = all->player->y;
		while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(start);
			ray.y -= sin(start);	
			my_mlx_pixel_put(all->win, ray.x, ray.y, 0x00FF0000);
		}
		if (sin(start) > 0 )	//checking horizontal intersections
		{
			ray.y_hor = round_down(all->player->y / SCALE) * SCALE - 1;
			ray.x_hor = all->player->x + (all->player->y - ray.y_hor) / tan(start);
			ray.x_diff = SCALE / tan(start);
			while (ray.y_hor / SCALE > 0 && ray.y_hor / SCALE < all->win->map_y && 
				ray.x_hor / SCALE > 0 && ray.x_hor / SCALE < all->win->map_x && 
				all->map[(int)(ray.y_hor / SCALE)][(int)(ray.x_hor / SCALE)] != '1')
			{
				ray.y_hor -= SCALE;
				ray.x_hor += ray.x_diff;
				printf("y_hor = %20f x_hor = %20f\n", ray.y_hor / SCALE, ray.x_hor / SCALE);
			}
		}
		else
		{
			ray.y_hor = round_down(all->player->y / SCALE) * SCALE + SCALE;
			ray.x_hor = all->player->x + (all->player->y - ray.y_hor) / tan(start);
			ray.x_diff = SCALE / tan(start);
			while (ray.y_hor / SCALE > 0 && ray.y_hor / SCALE < all->win->map_y && 
				ray.x_hor / SCALE > 0 && ray.x_hor / SCALE < all->win->map_x && 
				all->map[(int)(ray.y_hor / SCALE)][(int)(ray.x_hor / SCALE)] != '1')
			{
				ray.y_hor += SCALE;
				ray.x_hor += ray.x_diff;
				printf("y_hor = %20f x_hor = %20f\n", ray.y_hor / SCALE, ray.x_hor / SCALE);
			}
		}
		if (cos(start) > 0)	//checking vertical intersections
		{
			ray.x_vert = round_down(all->player->x / SCALE) * SCALE + SCALE;
			ray.y_vert = all->player->y + (all->player->x - ray.x_vert) * tan(start);
			ray.y_diff = SCALE * tan(start);
			while (ray.y_vert / SCALE > 0 && ray.y_vert / SCALE < all->win->map_y && 
				ray.x_vert / SCALE > 0 && ray.x_vert / SCALE < all->win->map_x &&
				all->map[(int)(ray.y_vert / SCALE)][(int)(ray.x_vert / SCALE)] != '1')
			{
				ray.x_vert += SCALE;
				ray.y_vert += ray.y_diff;
				printf("y_vert = %20f x_vert = %20f\n", ray.y_vert / SCALE, ray.x_vert / SCALE);
			}
		}
		else
		{
			ray.x_vert = round_down(all->player->x / SCALE) * SCALE - 1;
			ray.y_vert = all->player->y + (all->player->x - ray.x_vert) * tan(start);
			ray.y_diff = SCALE * tan(start);
			while (ray.y_vert / SCALE > 0 && ray.y_vert / SCALE < all->win->map_y && 
				ray.x_vert / SCALE > 0 && ray.x_vert / SCALE < all->win->map_x &&
				all->map[(int)(ray.y_vert / SCALE)][(int)(ray.x_vert / SCALE)] != '1')
			{
				ray.x_vert -= SCALE;
				ray.y_vert += ray.y_diff;
				printf("y_vert = %20f x_vert = %20f\n", ray.y_vert / SCALE, ray.x_vert / SCALE);
			}
		}
		if (start == M_PI_2 || start == 3 * M_PI_2)
		{
			ray.y_hor = INFINITY;
			ray.x_hor = INFINITY;
		}
		ray_hor = hypot((all->player->x - ray.x_hor), (all->player->y - ray.y_hor));
		ray_vert = hypot((all->player->x - ray.x_vert), (all->player->y - ray.y_vert));
		ray_len = (ray_hor > ray_vert) ? (ray_vert * cos(start - ray.dir)) : (ray_hor * cos(start - ray.dir));
		//printf("ray_len is %24f\n", ray_len);
		//printf("start is %24f in %d line\n", start, x_line);
		x_line++;
		draw_vertical_line(all, ray_len, x_line);
		start += (M_PI / 3) / all->win->screen_x;
	}
}

int 	round_down(double x)
{
	int x_rounded;

	x_rounded = round(x);
	if (x_rounded > x)
		x_rounded--;
	return (x_rounded);
}

void	draw_vertical_line(t_all *all, double ray_len, int x_line)
{
	int y, y1;
	double slice_height;

	slice_height = 0;
	if (ray_len != 0)
		slice_height = (int)((SCALE / ray_len * all->win->screen_x * 0.83));
	printf("slice_height is %24f\n", slice_height);
	if (slice_height > all->win->screen_y)
		slice_height = all->win->screen_y;
	y = ((all->win->screen_y - slice_height) / 2);
	y1 = all->win->screen_y - y;
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
void	get_map_size(char **map, t_all *all)
{
	int 	x;
	int 	y;
	int 	x_max;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (x > x_max)
				x_max = x;
			x++;
		}
		y++;
	}
	all->win->map_x = x_max + 1;
	all->win->map_y = y;
}

char	**to_rectangle_map(char **map, t_all *all)
{
	int 	x;
	int 	y;
	char	*tmp;

	get_map_size(map, all);
	y = 0;
	while (y < all->win->map_y)
	{
		x = 0;
		if (!(tmp = ft_calloc(1, all->win->map_x)))
			return (NULL);
		while (map[y][x])
		{
			tmp[x] = map[y][x];
			x++;
		}
		free(map[y]);
		map[y] = tmp;
		tmp = NULL;
		y++;
	}
	return (map);
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
			all->player->y -= sin(all->player->dir) * 4;
		}
	}
	else if (key == 1)
	{
		if (all->map[(int)(all->player->y / SCALE)][(int)(all->player->x / SCALE)] != '1')
		{
			all->player->x -= cos(all->player->dir) * 4;
			all->player->y += sin(all->player->dir) * 4;
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
		mlx_get_screen_size(win.mlx, &win.screen_x, &win.screen_y);
		win.window = mlx_new_window(win.mlx, win.screen_x, win.screen_y, "cub3D");
		win.img = mlx_new_image(win.mlx, win.screen_x, win.screen_y);
		win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length, &win.endian);
		all.map = to_rectangle_map(get_map(argv[1]), &all);
		player.dir = M_PI;
		player.projection_plan = win.screen_x / (tan(M_PI / 6) * 2);
		printf("%d\n", player.projection_plan);
		find_player(&all);
		draw_screen(&all);
		mlx_hook(win.window, 2, (1L << 0), &key_press, &all);
		mlx_loop(win.mlx);
	}
	return (0);
}
