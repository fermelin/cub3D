/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:48:09 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/27 19:48:14 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			check_map_sides(t_all *all, int y, int x)
{
	if (y == 0 || x == 0 || y == all->win->map_y - 1 || x == all->win->map_x - 1)
	    error_processor(NOT_VALID_MAP_ERR);
	if (0 == ft_strchr("102NSEW", all->map[y - 1][x]))
	    error_processor(NOT_VALID_MAP_ERR);
	if (0 == ft_strchr("102NSEW", all->map[y][x - 1]))
	    error_processor(NOT_VALID_MAP_ERR);
	if (0 == ft_strchr("102NSEW", all->map[y + 1][x]))
	    error_processor(NOT_VALID_MAP_ERR);
	if (0 == ft_strchr("102NSEW", all->map[y][x + 1]))
	    error_processor(NOT_VALID_MAP_ERR);
}

static void			check_map_corners(t_all *all, int y, int x)
{
	if (0 == ft_strchr("102NSEW", all->map[y - 1][x - 1]))
	   error_processor(NOT_VALID_MAP_ERR);
	if (0 == ft_strchr("102NSEW", all->map[y + 1][x - 1]))
	   error_processor(NOT_VALID_MAP_ERR);
	if (0 == ft_strchr("102NSEW", all->map[y + 1][x + 1]))
	   error_processor(NOT_VALID_MAP_ERR);
	if (0 == ft_strchr("102NSEW", all->map[y - 1][x + 1]))
	   error_processor(NOT_VALID_MAP_ERR);
}

void                check_map_symbols(t_all *all)
{
    int             y;
    int             x;
    y = 0;
    while (all->map[y])
    {
        x = 0;
        while (all->map[y][x])
        {
            if (ft_strchr("02NSEW", all->map[y][x]))
            {
            	check_map_sides(all, y, x);
            	check_map_corners(all, y, x);
            }
            x++;
        }
        y++;
    }
}