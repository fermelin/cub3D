/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_and_textures.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:52:57 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/29 12:53:12 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	get_texture_path(t_all *all, char *trimmed, int what_texture, int shift)
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
		error_processor(MULT_TEXTURES_ERR);
}

void	get_textures(t_all *all)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if ((ft_strncmp(".xpm", (all->tex[i].path + (ft_strlen(all->tex[i].path) - 4)), 4)))
			return (error_processor(TPATH_EXT_ERR));
		if (!(all->tex[i].img = mlx_xpm_file_to_image(all->win->mlx, all->tex[i].path, &all->tex[i].width, &all->tex[i].height)))
			return (error_processor(TPATH_ERR));
		free(all->tex[i].path);
		all->tex[i].addr = (int*)mlx_get_data_addr(all->tex[i].img, &all->tex[i].bits_per_pixel, &all->tex[i].line_length, &all->tex[i].endian);
		all->tex[i].step_x = (all->tex[i].width >= SCALE) ? ((double)all->tex[i].width / SCALE) : 1 / ((double)SCALE / all->tex[i].width);
		i++;
	}
			int j = 0;
		while (all->map[j])
		{
			printf("j is %5d %s\n", j, all->map[j]);
			j++;
		}
}