
#include "cub3d.h"

static void	get_map_size(char **map, t_all *all)
{
	int	x;
	int	y;
	int	x_max;

	y = 0;
	x_max = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (x > x_max)
				x_max = x;
			x++;
		}
		y++;
	}
	all->win->map_x = x_max + 1;
	all->win->map_y = y;
}

static char	**to_rectangle_map(char **map, t_all *all)
{
	int		x;
	int		y;
	char	*tmp;

	get_map_size(map, all);
	y = 0;
	while (y < all->win->map_y)
	{
		x = 0;
		if (!(tmp = (char*)malloc(sizeof(char) * (all->win->map_x + 1))))
			error_processor(MALLOC_ERR, all);
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
	return (map);
}

static char	**map_list_to_char(t_all *all, t_list **map)
{
	char	**map_char;
	int		i;
	t_list	*tmp;
	int		y;

	i = 0;
	tmp = NULL;
	y = 0;
	y = ft_lstsize(*map);
	if (!(map_char = (char **)malloc(sizeof(char *) * (y + 1))))
		error_processor(MALLOC_ERR, all);
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

char		**get_map(t_all *all, int fd, char *line)
{
	t_list	*map;
	int		line_len;
	int		ret;

	map = NULL;
	line_len = 0;
	ret = 0;
	line_len = ft_strlen(line);
	while (line_len > 0)
	{
		if (*line)
			ft_lstadd_back(&map, ft_lstnew(line));
		if ((ret = get_next_line(fd, &line)) <= 0)
			break ;
		line_len = ft_strlen(line);
	}
	if (*line)
		ft_lstadd_back(&map, ft_lstnew(line));
	else
		free(line);
	if (ret == -1)
		error_processor(GNL_ERR, all);
	return (map_list_to_char(all, &map));
}
