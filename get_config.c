/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:06:07 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/10 12:36:53 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	get_config(char *config)
{
	int		fd;	
	char	*line = NULL;
	int 	i, j;
	char	**map1;
	t_list	*map;
	t_list	*tmp;

	i = j = 0;
	map = NULL;
	fd = open(config, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&map, ft_lstnew(line));
	i = ft_lstsize(map);
	printf("%d\n", i);
	if (!(map1 = (char **)malloc(sizeof(char *) * (i + 1))))
		return ;
	map1[i] = NULL;
	while (map)
	{
		map1[j] = map->content;
		tmp = map;
		map = map->next;
		free(tmp);
		j++;
	}
	j = 0;
	while (j < i+1)
	{
		printf("%s\n", map1[j]);
		j++;
	}
}

int main(int argc, char **argv)
{

	if (argc == 2)
	{
		get_config(argv[1]);
	}
	return (0);
}
