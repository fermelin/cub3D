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

static int		find_all_texture_paths(t_all *all)
{
	int	i;

	i = 0; 
	printf("0 is %s\n", all->tex[0].path);
	printf("1 is %s\n", all->tex[1].path);
	printf("2 is %s\n", all->tex[2].path);
	printf("3 is %s\n", all->tex[3].path);
	while (all->tex[i].path && (*(all->tex[i].path) == '.' || *(all->tex[i].path) == '/'))
		i++;
	if (i == 4)
		return (1);
	return (0);
}

void	parser(char *argv, t_all *all)
{
	char	*line;
	char	**words = NULL;
	int 	fd;

	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line) > 0)//EA NO WE SO
	{
		words = NULL;
		if (ft_strncmp(line, "EA", 2) == 0)
		{
			words = ft_split(line, ' ');
			while (*(words + 1))
			{
				//free();
				words++;
			}
			all->tex[0].path = *words;
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
		}
		else
			free(line);
		line = NULL;
		if (find_all_texture_paths(all))
			break ;
	}
	all->map = get_map(all, fd);
}