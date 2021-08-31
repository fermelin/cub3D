
#include "cub3d.h"

static int	is_resolution_not_too_big(char *trimmed, int *shift)
{
	int len;

	len = 0;
	while (ft_isspace(trimmed[*shift]))
		(*shift)++;
	while (ft_isdigit(trimmed[(*shift) + len]))
		len++;
	if (len > 5)
		return (0);
	return (1);
}

static void	resolution_format_checking(char *trimmed, int shift, t_all *all)
{
	int number_amount;

	number_amount = 0;
	while (trimmed[shift])
	{
		if ((ft_strchr("\t\n\v\f\r ", trimmed[shift])))
			shift++;
		else if (ft_isdigit(trimmed[shift]))
		{
			number_amount++;
			while (ft_isdigit(trimmed[shift]))
				shift++;
		}
		else
			break ;
	}
	if (trimmed[shift] != 0 || number_amount != 2)
	{
		free(trimmed);
		return (error_processor(WRONG_RES_FORMAT_ERR, all));
	}
}

void		get_screen_resolution(t_all *all, char *trimmed, int shift)
{
	int	screen_x;
	int	screen_y;

	screen_x = -1;
	screen_y = -1;
	resolution_format_checking(trimmed, shift, all);
	if (is_resolution_not_too_big(trimmed, &shift))
		screen_x = ft_atoi(trimmed + shift);
	while (ft_isdigit(trimmed[shift]))
		shift++;
	if (is_resolution_not_too_big(trimmed, &shift))
		screen_y = ft_atoi(trimmed + shift);
	if (screen_x != -1)
		all->win->screen_x = (screen_x > all->win->screen_x) ?
	all->win->screen_x : screen_x;
	if (screen_y != -1)
		all->win->screen_y = (screen_y > all->win->screen_y) ?
	all->win->screen_y : screen_y;
	if (all->win->screen_x < 4 || all->win->screen_y < 4)
	{
		free(trimmed);
		return (error_processor(RES_TOO_SMALL_ERR, all));
	}
	all->parsing.resolution = 1;
	free(trimmed);
}
