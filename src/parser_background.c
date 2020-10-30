/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:37:26 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/30 16:37:28 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color_nbr_len(char *trimmed, int shift, int *nbr_amount,
	t_all *all)
{
	int nbr_len;

	nbr_len = 0;
	(*nbr_amount)++;
	while (ft_isdigit(trimmed[shift + nbr_len]))
		nbr_len++;
	if (nbr_len > 3)
		error_processor(WRONG_COLOR_VALUE_ERR, all);
	return (nbr_len);
}

static int	get_color_value(char *trimmed, int shift, t_all *all)
{
	int r;
	int g;
	int b;

	r = ft_atoi(trimmed + shift);
	while (trimmed[shift - 1] != ',')
		shift++;
	g = ft_atoi(trimmed + shift);
	shift++;
	while (trimmed[shift - 1] != ',')
		shift++;
	b = ft_atoi(trimmed + shift);
	if (r > 255 || g > 255 || b > 255)
		error_processor(WRONG_COLOR_VALUE_ERR, all);
	return (r << 16 | g << 8 | b << 0);
}

static void	color_format_checking(char *trimmed, int shift, t_all *all)
{
	int commas;
	int nbr_amount;

	commas = 0;
	nbr_amount = 0;
	while (trimmed[shift])
	{
		if (ft_isspace(trimmed[shift]))
			shift++;
		else if (ft_isdigit(trimmed[shift]))
			shift += get_color_nbr_len(trimmed, shift, &nbr_amount, all);
		else if (trimmed[shift] == ',')
		{
			shift++;
			commas++;
		}
		else
			return (error_processor(WRONG_COLOR_FORMAT_ERR, all));
	}
	if (commas != 2 || nbr_amount != 3)
		return (error_processor(WRONG_COLOR_FORMAT_ERR, all));
}

void		get_backgrougd_color(t_all *all, char *trimmed, int shift)
{
	int	color;

	color_format_checking(trimmed, shift, all);
	color = get_color_value(trimmed, shift, all);
	if (*trimmed == 'F')
	{
		if (all->parsing.is_floor == 1)
			return (error_processor(MULT_FLOOR_ERR, all));
		all->parsing.floor = color;
		all->parsing.is_floor = 1;
	}
	else if (*trimmed == 'C')
	{
		if (all->parsing.is_ceiling == 1)
			return (error_processor(MULT_CEILING_ERR, all));
		all->parsing.ceiling = color;
		all->parsing.is_ceiling = 1;
	}
	free(trimmed);
}
