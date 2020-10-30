/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:41:48 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/28 13:41:55 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error_processor_2(int errnum)
{
	if (errnum == NO_PLAYER_ERR)
		ft_putendl_fd(NO_PLAYER_TXT, 2);
	else if (errnum == WRONG_CON_EX_ERR)
		ft_putendl_fd(WRONG_CON_EX_TXT, 2);
	else if (errnum == WRONG_NUMBER_OF_ARGS_ERR)
		ft_putendl_fd(WRONG_NUMBER_OF_ARGS_TXT, 2);
	else if (errnum == WRONG_SEC_ARG_ERR)
		ft_putendl_fd(WRONG_SEC_ARG_TXT, 2);
	else if (errnum == WRONG_CONFIG_NAME_ERR)
		perror(WRONG_CONFIG_NAME_TXT);
	else if (errnum == NOT_VALID_MAP_ERR)
		ft_putendl_fd(NOT_VALID_MAP_TXT, 2);
	else if (errnum == RES_TOO_SMALL_ERR)
		ft_putendl_fd(RES_TOO_SMALL_TXT, 2);
	else if (errnum == SCREENSHOT_ERR)
		ft_putendl_fd(SCREENSHOT_TXT, 2);
	else if (errnum == GNL_ERR)
		ft_putendl_fd(GNL_TXT, 2);
	else if (errnum == MALLOC_ERR)
		perror(MALLOC_TXT);
}

void		error_processor(int errnum, t_all *all)
{
	all->errnum = errnum;
	if (errnum == TPATH_ERR)
		perror(TPATH_TXT);
	else if (errnum == TPATH_EXT_ERR)
		ft_putendl_fd(TPATH_EXT_TXT, 2);
	else if (errnum == MULT_TEXTURES_ERR)
		ft_putendl_fd(MULT_TEXTURES_TXT, 2);
	else if (errnum == MULT_FLOOR_ERR)
		ft_putendl_fd(MULT_FLOOR_TXT, 2);
	else if (errnum == MULT_CEILING_ERR)
		ft_putendl_fd(MULT_CEILING_TXT, 2);
	else if (errnum == WRONG_COLOR_FORMAT_ERR)
		ft_putendl_fd(WRONG_COLOR_FORMAT_TXT, 2);
	else if (errnum == WRONG_RES_FORMAT_ERR)
		ft_putendl_fd(WRONG_RES_FORMAT_TXT, 2);
	else if (errnum == INCOMPLETE_PARAM_SET_ERR)
		ft_putendl_fd(INCOMPLETE_PARAM_SET_TXT, 2);
	else if (errnum == WRONG_COLOR_VALUE_ERR)
		ft_putendl_fd(WRONG_COLOR_VALUE_TXT, 2);
	else if (errnum == MULTIPLE_PLAYER_ERR)
		ft_putendl_fd(MULTIPLE_PLAYER_TXT, 2);
	else
		error_processor_2(errnum);
	destroy_all(all);
}
