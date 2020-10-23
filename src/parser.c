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
	if (all->parsing.no_tex && all->parsing.ea_tex && all->parsing.we_tex 
		&& all->parsing.so_tex && all->parsing.s_tex && all->parsing.resolution)
		//&& all->parsing.is_floor && all->parsing.is_ceiling)
		return (1);
	return (0);
}

void	parser(char *argv, t_all *all)
{
	char	*line;
	//char 	*trimmed;
	char	**words = NULL;
	int 	fd;
	int		i;
	int		screen_x;
	int 	screen_y;

	i = 0;
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line) > 0)//EA = 0 NO = 1 WE = 2 SO = 3 S = 4
	{
		//trimmed = ft_strtrim(line, "\n\t\v ");
		//free(line);
		//words = NULL;
		if (ft_strncmp(line, "EA", 2) == 0)
		{
			words = ft_split(line, ' ');
			while (*(words + 1))
			{
				//free();
				words++;
			}
			all->tex[0].path = *words;
			all->parsing.ea_tex = 1;
		}
		else if (ft_strncmp(line, "NO", 2) == 0)
		{
			words = ft_split(line, ' ');
			while (*(words + 1))
			{
				//free();
				words++;
			}
			all->tex[1].path = *words;
			all->parsing.no_tex = 1;
		}
		else if (ft_strncmp(line, "WE", 2) == 0)
		{
			words = ft_split(line, ' ');
			while (*(words + 1))
			{
				//free();
				words++;
			}
			all->tex[2].path = *words;
			all->parsing.we_tex = 1;
		}
		else if (ft_strncmp(line, "SO", 2) == 0)
		{
			words = ft_split(line, ' ');
			while (*(words + 1))
			{
				//free();
				words++;
			}
			all->tex[3].path = *words;
			all->parsing.so_tex = 1;
		}
		else if (ft_strncmp(line, "S", 1) == 0)
		{
			words = ft_split(line, ' ');
			while (*(words + 1))
			{
				//free();
				words++;
			}
			all->tex[4].path = *words;
			all->parsing.s_tex = 1;
		}
		else if (ft_strncmp(line, "R", 1) == 0)
		{
			screen_x = ft_atoi(++line);
			while (*line == ' ' || *line == '\t')
				line++;
			while (ft_isdigit(*line))
				line++;
			screen_y = ft_atoi(line);
			all->win->screen_x = (screen_x > all->win->screen_x) ? all->win->screen_x : screen_x;
			all->win->screen_y = (screen_y > all->win->screen_y) ? all->win->screen_y : screen_y;
			all->parsing.resolution = 1;
		}
		else
			free(line);
		line = NULL;
		if (is_all_parsed(all))
			break ;
	}
	all->map = get_map(all, fd);
	sprites_counter(all);
	get_sprites_xy(all);
}