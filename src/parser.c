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

/*
** EA = 0 NO = 1 WE = 2 SO = 3 S = 4
*/
#include "cub3d.h"

static int	is_all_parsed(t_all *all)
{
	if (all->parsing.tex[0] && all->parsing.tex[1] && all->parsing.tex[2] &&
		all->parsing.tex[3] && all->parsing.tex[4] && all->parsing.resolution
		&& all->parsing.is_floor && all->parsing.is_ceiling)
		return (1);
	return (0);
}

static int	is_line_belongs_to_map(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_strchr(" 102NSEW", line[i]))
		i++;
	if (!line[i] && i)
		return (1);
	return (0);
}

static void	get_texture_path(t_all *all, char *trimmed, int what_texture,
	int shift)
{
	char *newstr;

	while (ft_isspace(trimmed[shift]))
		shift++;
	newstr = ft_strdup(trimmed + shift);
	free(trimmed);
	trimmed = NULL;
	all->tex[what_texture].path = newstr;
	if (all->parsing.tex[what_texture] == 0)
		all->parsing.tex[what_texture] = 1;
	else
		error_processor(MULT_TEXTURES_ERR, all);
}

static void	parse_all_without_map(t_all *all, char *line)
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
	else if (ft_strncmp(trimmed, "F", 1) == 0 ||
		ft_strncmp(trimmed, "C", 1) == 0)
		get_backgrougd_color(all, trimmed, shift + 1);
	else
		free(trimmed);
	trimmed = NULL;
}

void		parser(char *argv, t_all *all)
{
	char	*line;
	int		fd;
	int		ret;

	if ((fd = open(argv, O_RDONLY)) == -1)
		error_processor(WRONG_CONFIG_NAME_ERR, all);
	while ((ret = get_next_line(fd, &line)) > 0)
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
	if (ret == -1)
		error_processor(GNL_ERR, all);
	if (!is_all_parsed(all))
		error_processor(INCOMPLETE_PARAM_SET_ERR, all);
	check_map_symbols(all);
	sprites_counter(all);
	get_sprites_xy(all);
	close(fd);
}
