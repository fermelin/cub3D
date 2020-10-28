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
		if (!(tmp = (char*)malloc(sizeof(char) * (all->win->map_x + 1))))
			return (NULL);
		ft_memset(tmp, ' ', all->win->map_x);
		tmp[all->win->map_x] = '\0';
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
	// printf("%d\n", all->win->map_x);
	return (map);
}

static	char	**map_list_to_char(t_all *all, int y, t_list **map)
{
	char	**map_char;
	int 	i;
	t_list	*tmp;

	i = 0;
	tmp = NULL;
	if (!(map_char = (char **)malloc(sizeof(char *) * (y + 1))))
		return (NULL);
	map_char[y] = NULL;
	while (*map)
	{
		map_char[i] = (*map)->content;
		tmp = (*map);
		(*map) = (*map)->next;
		free(tmp);
		i++;
	}
	return (to_rectangle_map(map_char, all));
}

char	**get_map(t_all *all, int fd)
{
	char	*line;
	int 	y;
	t_list	*map;
	int		line_len;

	y = 0;
	map = NULL;
	line = NULL;
	line_len = 0;
	while (get_next_line(fd, &line) > 0 && !(line_len = ft_strlen(line)))
		free(line);
	while (line_len > 0)
	{
		if (*line)
			ft_lstadd_back(&map, ft_lstnew(line));
		if (get_next_line(fd, &line) == 0)
			break;
		line_len = ft_strlen(line);
	}
	if (*line)
		ft_lstadd_back(&map, ft_lstnew(line));
	else
		free(line);
	y = ft_lstsize(map);
	return (map_list_to_char(all, y, &map));
}



// void	map_horizontal_validation(t_all *all)
// {
// 	int x;
// 	int y;

// 	x = 0;
// 	y = 0;
// 	while (all->map[y])
// 	{

// 	}
// }



















