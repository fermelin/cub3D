/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:47:36 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/20 12:47:49 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int		find_all_texture_paths(t_all *all)
// {
// 	int	i;

// 	i = 0; 
// 	printf("0 is %s\n", all->tex[0].path);
// 	printf("1 is %s\n", all->tex[1].path);
// 	printf("2 is %s\n", all->tex[2].path);
// 	printf("3 is %s\n", all->tex[3].path);
// 	printf("3 is %s\n", all->tex[4].path);
// 	while (all->tex[i].path && (*(all->tex[i].path) == '.' || *(all->tex[i].path) == '/'))
// 		i++;

// 	if (i == 5)
// 		return (1);
// 	return (0);
// }

int 	is_all_parsed(t_all *all)
{
	if (all->parsing.tex[0] && all->parsing.tex[1] && all->parsing.tex[2] 
		&& all->parsing.tex[3] && all->parsing.tex[4] && all->parsing.resolution
		&& all->parsing.is_floor && all->parsing.is_ceiling)
		return (1);
	return (0);
}

void	get_texture_path(t_all *all, char *trimmed, int what_texture, int shift)
{
	char *newstr;

	while (ft_isspace(trimmed[shift]))
		shift++;
	newstr = ft_strdup(trimmed + shift);
	free(trimmed);
	trimmed = NULL;
	all->tex[what_texture].path = newstr;
	all->parsing.tex[what_texture] = 1;
}

void	get_screen_resolution(t_all *all, char *trimmed, int shift)
{
	int		screen_x;
	int 	screen_y;

	screen_x = ft_atoi(trimmed + shift);
	while (ft_isspace(trimmed[shift]))
		shift++;
	while (ft_isdigit(trimmed[shift]))
		shift++;
	screen_y = ft_atoi(trimmed + shift);
	all->win->screen_x = (screen_x > all->win->screen_x) ? all->win->screen_x : screen_x;
	all->win->screen_y = (screen_y > all->win->screen_y) ? all->win->screen_y : screen_y;
	all->parsing.resolution = 1;
	free(trimmed);
}

int		color_mixer(int r, int g, int b)
{
	return (r << 16 | g << 8 | b << 0);
}

void	get_backgrougd_color(t_all *all, char *trimmed, int shift)
{
	int r;
	int g;
	int b;
	int	color;
	// int i;

	r = ft_atoi(trimmed + shift);
	while (trimmed[shift - 1] != ',')
		shift++;
	g = ft_atoi(trimmed + shift);
	shift++;
	while (trimmed[shift - 1] != ',')
		shift++;
	b = ft_atoi(trimmed + shift);
	color = color_mixer(r, g, b);
	if (*trimmed == 'F')
	{
		// if (all->parsing->is_floor == 1)
		// 	return ()
		all->parsing.floor = color;
		all->parsing.is_floor = 1;
	}
	else if (*trimmed == 'C')
	{
		all->parsing.ceiling = color;
		all->parsing.is_ceiling = 1;
	}
	free(trimmed);
}

void	parser(char *argv, t_all *all)
{
	char	*line;
	char 	*trimmed;
	int 	fd;
	int		shift;

	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line) > 0)//EA = 0 NO = 1 WE = 2 SO = 3 S = 4
	{
		shift = 0;
		trimmed = ft_strtrim(line, "\t\n\v\f\r ");
		free(line);
		line = NULL;
		if (ft_strncmp(trimmed, "EA", 2) == 0)
			get_texture_path(all, trimmed, 0, shift + 2);
		else if (ft_strncmp(trimmed, "NO", 2) == 0)
			get_texture_path(all, trimmed, 1, shift + 2);
		else if (ft_strncmp(trimmed, "WE", 2) == 0)
			get_texture_path(all, trimmed, 2, shift + 2);
		else if (ft_strncmp(trimmed, "SO", 2) == 0)
			get_texture_path(all, trimmed, 3, shift + 2);
		else if (ft_strncmp(trimmed, "S", 1) == 0)
			get_texture_path(all, trimmed, 4, shift + 1);
		else if (ft_strncmp(trimmed, "R", 1) == 0)
			get_screen_resolution(all, trimmed, shift + 1);
		else if (ft_strncmp(trimmed, "F", 1) == 0 || ft_strncmp(trimmed, "C", 1) == 0)
			get_backgrougd_color(all, trimmed, shift + 1);
		else
			free(trimmed);
		trimmed = NULL;
		if (is_all_parsed(all))
			break ;
	}
	free(line);
	all->map = get_map(all, fd);
	check_map_symbols(all);
	sprites_counter(all);
	get_sprites_xy(all);
	// printf("ceiling is %x\nfloor is %x\n", all->parsing.ceiling, all->parsing.floor);
	close(fd);
}