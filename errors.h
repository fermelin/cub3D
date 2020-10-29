/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:49:03 by fermelin          #+#    #+#             */
/*   Updated: 2020/10/20 12:50:01 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define TPATH_ERR 1
# define TPATH_TXT "\033[1;31mERROR\033[0m\n--Invalid texture path--\n"

# define TPATH_EXT_ERR 2
# define TPATH_EXT_TXT "\033[1;31mERROR\033[0m\n--Wrong texture file extension. Expected \".xpm\"--"

# define MULT_TEXTURES_ERR 3
# define MULT_TEXTURES_TXT "\033[1;31mERROR\033[0m\n--Multiple texture parameter is giving--"

# define MULT_FLOOR_ERR 4
# define MULT_FLOOR_TXT "\033[1;31mERROR\033[0m\n--Multiple floor color parameter is giving--"

# define MULT_CEILING_ERR 5
# define MULT_CEILING_TXT "\033[1;31mERROR\033[0m\n--Multiple ceiling color parameter is giving--"

# define WRONG_COLOR_FORMAT_ERR 6
# define WRONG_COLOR_FORMAT_TXT "\033[1;31mERROR\033[0m\n--Wrong format of ceiling/floor color parameter--"

# define WRONG_RESOLUTION_FORMAT_ERR 7
# define WRONG_RESOLUTION_FORMAT_TXT "\033[1;31mERROR\033[0m\n--Wrong format of resolution parameter--"

# define INCOMPLETE_PARAM_SET_ERR 8
# define INCOMPLETE_PARAM_SET_TXT "\033[1;31mERROR\033[0m\n--Incomplete set of parameters--"

# define WRONG_COLOR_VALUE_ERR 9
# define WRONG_COLOR_VALUE_TXT "\033[1;31mERROR\033[0m\n--Wrong color value. Correct is in range [0;255]--"

# define MULTIPLE_PLAYERS_ERR 10
# define MULTIPLE_PLAYERS_TXT "\033[1;31mERROR\033[0m\n--There are multiple players on the map--"

# define NO_PLAYER_ERR 11
# define NO_PLAYER_TXT "\033[1;31mERROR\033[0m\n--There is no player on the map--"

# define WRONG_CONFIG_EXTENSION_ERR 12
# define WRONG_CONFIG_EXTENSION_TXT "\033[1;31mERROR\033[0m\n--Wrong config file extension. Expected \".cub\"--"

# define WRONG_NUMBER_OF_ARGS_ERR 13
# define WRONG_NUMBER_OF_ARGS_TXT "\033[1;31mERROR\033[0m\n--Wrong number of arguments--"

# define WRONG_SECOND_ARG_ERR 14
# define WRONG_SECOND_ARG_TXT "\033[1;31mERROR\033[0m\n--Wrong second argument. Expected \"--save\"--"

# define WRONG_CONFIG_NAME_ERR 15
# define WRONG_CONFIG_NAME_TXT "\033[1;31mERROR\033[0m\n--Wrong name of config file--\n"

# define NOT_VALID_MAP_ERR 16
# define NOT_VALID_MAP_TXT "\033[1;31mERROR\033[0m\n--The map is not valid--"

#endif






