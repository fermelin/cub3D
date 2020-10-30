/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:24:49 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/25 14:24:53 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	int_to_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}

static int	bmp_header(int fd, int height, int width, int padsize)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (width * 3 * height) + (padsize * height);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_to_char(header + 18, width);
	int_to_char(header + 22, height);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

static int	bmp_data(int fd, t_all *all, int padsize)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				pixel;

	y = all->win->screen_y - 1;
	ft_bzero(zero, 3);
	while (y >= 0)
	{
		x = 0;
		while (x < all->win->screen_x)
		{
			pixel = *((int*)all->win->addr + x + y * all->win->line_length / 4);
			if (write(fd, &pixel, 3) < 0)
				return (0);
			x++;
		}
		if (padsize > 0 && write(fd, &zero, padsize) < 0)
			return (0);
		y--;
	}
	return (1);
}

static int	take_screenshot(t_all *all)
{
	int padsize;
	int fd;

	draw_screen(all);
	padsize = (4 - ((int)all->win->screen_x * 3) % 4) % 4;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC |
		O_APPEND)) < 0)
		return (0);
	bmp_header(fd, all->win->screen_y, all->win->screen_x, padsize);
	bmp_data(fd, all, padsize);
	close(fd);
	return (1);
}

void		make_screenshot(t_all *all, char *argv)
{
	if (ft_strncmp("--save", argv, 7) != 0)
		error_processor(WRONG_SEC_ARG_ERR, all);
	all->screenshot = 1;
	if (!take_screenshot(all))
		error_processor(SCREENSHOT_ERR, all);
	ft_putendl_fd("\033[1;32mFile \"screenshot.bmp\" was created!\033[0m", 1);
	destroy_all(all);
}
