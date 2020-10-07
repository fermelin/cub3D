/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:43:37 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/07 19:05:00 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef	struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	set_background(t_data img)
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
            my_mlx_pixel_put(&img, x, y, color);
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
            my_mlx_pixel_put(&img, x, y, color);
            x++;
        }
        y++;
        if (y % 3 == 0)
            color-= 256;
    }
}

int		main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1920, 1080, "hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	set_background(img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
