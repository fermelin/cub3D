/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:06:07 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/09 20:23:29 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

t_list	*get_config(char *config)
{
	int		fd;	
	char	*line;
	int 	i;
	t_list	**map;
	t_list	*mapline;

	i = 0;
	fd = open(config, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{	
		mapline = ft_lstnew(line);
		ft_lstadd_back(map, mapline);
	}
	return (*map);
}

int main(int argc, char **argv)
{
	int		i;
	t_list	*map;

	i = 0;
	if (argc == 2)
	{
		map = get_config(argv[1]);
		while (map)
		{
			printf("%s\n", map->content);
			map = map->next;
		}
	}
	return (0);
}
