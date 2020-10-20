/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:06:07 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/16 12:36:09 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**to_rectangle_map(char **map, t_all *all)
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

char	**get_map(t_all *all, int fd)
{
	//int		fd;	
	char	*line = NULL;
	int 	i, j;
	char	**map1;
	t_list	*map;
	t_list	*tmp;

	i = j = 0;
	map = NULL;
	//fd = open(config, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&map, ft_lstnew(line));
	free(line);
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
	return (to_rectangle_map(map1, all));
}