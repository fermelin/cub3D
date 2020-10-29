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
void	error_processor_2(int errnum)
{
	if (errnum == WRONG_CONFIG_EXTENSION_ERR)
		ft_putendl_fd(WRONG_CONFIG_EXTENSION_TXT, 2);
	else if (errnum == WRONG_NUMBER_OF_ARGS_ERR)
		ft_putendl_fd(WRONG_NUMBER_OF_ARGS_TXT, 2);
	else if (errnum == WRONG_SECOND_ARG_ERR)
		ft_putendl_fd(WRONG_SECOND_ARG_TXT, 2);
	else if (errnum == WRONG_CONFIG_NAME_ERR)
		perror(WRONG_CONFIG_NAME_TXT);
	else if (errnum == NOT_VALID_MAP_ERR)
		ft_putendl_fd(NOT_VALID_MAP_TXT, 2);
}
void	error_processor(int errnum)
{
	if (errnum == TPATH_ERR) //fix it
		perror(TPATH_TXT);
	else if (errnum == TPATH_EXT_ERR) //fix it 1
		ft_putendl_fd(TPATH_EXT_TXT, 2);
	else if (errnum == MULT_TEXTURES_ERR)
		ft_putendl_fd(MULT_TEXTURES_TXT, 2);
	else if (errnum == MULT_FLOOR_ERR)
		ft_putendl_fd(MULT_FLOOR_TXT, 2);
	else if (errnum == MULT_CEILING_ERR)
		ft_putendl_fd(MULT_CEILING_TXT, 2);
	else if (errnum == WRONG_COLOR_FORMAT_ERR)
		ft_putendl_fd(WRONG_COLOR_FORMAT_TXT, 2);
	else if (errnum == WRONG_RESOLUTION_FORMAT_ERR)
		ft_putendl_fd(WRONG_RESOLUTION_FORMAT_TXT, 2);
	else if (errnum == INCOMPLETE_PARAM_SET_ERR)
		ft_putendl_fd(INCOMPLETE_PARAM_SET_TXT, 2);
	else if (errnum == WRONG_COLOR_VALUE_ERR)
		ft_putendl_fd(WRONG_COLOR_VALUE_TXT, 2);
	else if (errnum == MULTIPLE_PLAYERS_ERR)
		ft_putendl_fd(MULTIPLE_PLAYERS_TXT, 2);
	else if (errnum == NO_PLAYER_ERR)
		ft_putendl_fd(NO_PLAYER_TXT, 2);
	else
		error_processor_2(errnum);
	exit(errnum);
}