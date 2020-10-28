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

// void	error_list(char c)
// {

// }

void	error_processor(int errnum)
{
	if (errnum == TPATH_ERR)
		perror(TPATH_TXT);
	else if (errnum == TPATH_EXT_ERR)
		perror(TPATH_EXT_TXT);
	exit(1);
}

int		put_error(char *str)//, t_all *all) осталось от жениной функции проверки карты
{
	ft_putendl_fd(str, 2);
	// return (0);
	exit(1);
}