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

int 	is_all_parsed(t_all *all)
{
	if (all->parsing.tex[0] && all->parsing.tex[1] && all->parsing.tex[2] 
		&& all->parsing.tex[3] && all->parsing.tex[4] && all->parsing.resolution
		&& all->parsing.is_floor && all->parsing.is_ceiling)
		return (1);
	return (0);
}


int 	is_resolution_not_too_big(char *trimmed, int shift)
{
	int len;

	len = 0;
	while (ft_isspace(trimmed[shift]))
		shift++;
	while (ft_isdigit(trimmed[shift]))
	{
		shift++;
		len++;
	}
	if (len > 5)
		return (0);
	return (1);
}

void	resolution_format_checking(char *trimmed, int shift)
{
	int number_amount;

	number_amount = 0;
	while (trimmed[shift])
	{
		if ((ft_strchr("\t\n\v\f\r ", trimmed[shift])))
			shift++;
		else if (ft_isdigit(trimmed[shift]))
		{
			number_amount++;
			while (ft_isdigit(trimmed[shift]))
				shift++;
		}
		else
			break ;
		
	}
	if (trimmed[shift] != 0 || number_amount != 2)
		return (error_processor(WRONG_RESOLUTION_FORMAT_ERR));
}

void	get_screen_resolution(t_all *all, char *trimmed, int shift)
{
	int		screen_x;
	int 	screen_y;

	screen_x = 0;
	screen_y = 0;
	resolution_format_checking(trimmed, shift);
	if (is_resolution_not_too_big(trimmed, shift))
		screen_x = ft_atoi(trimmed + shift);
	while (ft_isspace(trimmed[shift]))
		shift++;
	while (ft_isdigit(trimmed[shift]))
		shift++;
	if (is_resolution_not_too_big(trimmed, shift))
		screen_y = ft_atoi(trimmed + shift);
	if (screen_x != 0)
		all->win->screen_x = (screen_x > all->win->screen_x) ? all->win->screen_x : screen_x;
	if (screen_y != 0)
		all->win->screen_y = (screen_y > all->win->screen_y) ? all->win->screen_y : screen_y;
	all->parsing.resolution = 1;
	free(trimmed);
}

// int		color_mixer(int r, int g, int b)
// {
// 	if (r > 255 || g > 255 || b > 255)
// 		return (error_processor(WRONG_COLOR_VALUE_ERR))
// 	return (r << 16 | g << 8 | b << 0);
// }

int 	get_color_nbr_len(char *trimmed, int shift, int *nbr_amount)
{
	int nbr_len;

	nbr_len = 0;
	(*nbr_amount)++;
	while (ft_isdigit(trimmed[shift + nbr_len]))
		nbr_len++;
	if (nbr_len > 3)
		error_processor(WRONG_COLOR_VALUE_ERR);
	return (nbr_len);
}

void 	color_format_checking(char *trimmed, int shift)
{
	int commas;
	int nbr_amount;

	commas = 0;
	nbr_amount = 0;
	while (trimmed[shift])
	{
		if (ft_isspace(trimmed[shift]))
			shift++;
		else if (ft_isdigit(trimmed[shift]))
			shift += get_color_nbr_len(trimmed, shift, &nbr_amount);
		else if (trimmed[shift] == ',')
		{
			shift++;
			commas++;
		}
		else
			return (error_processor(WRONG_COLOR_FORMAT_ERR));
	}
	if (commas != 2 || nbr_amount != 3)
		return (error_processor(WRONG_COLOR_FORMAT_ERR));
}

int 	get_color_value(char *trimmed, int shift)
{
	int r;
	int g;
	int b;

	r = ft_atoi(trimmed + shift);
	while (trimmed[shift - 1] != ',')
		shift++;
	g = ft_atoi(trimmed + shift);
	shift++;
	while (trimmed[shift - 1] != ',')
		shift++;
	b = ft_atoi(trimmed + shift);
	if (r > 255 || g > 255 || b > 255)
		error_processor(WRONG_COLOR_VALUE_ERR);
	return (r << 16 | g << 8 | b << 0);
}

void	get_backgrougd_color(t_all *all, char *trimmed, int shift)
{
	int	color;
	// int i;

	color_format_checking(trimmed, shift);
	color = get_color_value(trimmed, shift);
	if (*trimmed == 'F')
	{
		if (all->parsing.is_floor == 1)
			return (error_processor(MULT_FLOOR_ERR));
		all->parsing.floor = color;
		all->parsing.is_floor = 1;
	}
	else if (*trimmed == 'C')
	{
		if (all->parsing.is_ceiling == 1)
			return (error_processor(MULT_CEILING_ERR));
		all->parsing.ceiling = color;
		all->parsing.is_ceiling = 1;
	}
	free(trimmed);
}

int 	is_line_belongs_to_map(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_strchr(" 102NSEW", line[i]))
		i++;
	if (!line[i] && i)
		return (1);
	return (0);
}

void	parse_all_without_map(t_all *all, char *line)
{
	char	*trimmed;
	int		shift;

	shift = 0;
	trimmed = ft_strtrim(line, "\t\n\v\f\r ");
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
}

void	parser(char *argv, t_all *all)
{
	char	*line;
	int 	fd;
	
	if ((fd = open(argv, O_RDONLY)) == -1)
		error_processor(WRONG_CONFIG_NAME_ERR);
	while (get_next_line(fd, &line) > 0)//EA = 0 NO = 1 WE = 2 SO = 3 S = 4
	{
		parse_all_without_map(all, line);
		if (is_all_parsed(all) && is_line_belongs_to_map(line))
		{
			all->map = get_map(all, fd, line);
			break ; 
		}
		free(line);
		line = NULL;
	}
	// free(line);
	if (!is_all_parsed(all))
		error_processor(INCOMPLETE_PARAM_SET_ERR);
	check_map_symbols(all);
	sprites_counter(all);
	get_sprites_xy(all);
	// printf("ceiling is %x\nfloor is %x\n", all->parsing.ceiling, all->parsing.floor);
	close(fd);
}