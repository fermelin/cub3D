
#ifndef ERRORS_H
# define ERRORS_H

# define TPATH_ERR 1
# define TPATH_TXT "ERROR\n--Invalid texture path--\n"

# define TPATH_EXT_ERR 2
# define TPATH_EXT_TXT "ERROR\n--Expected \".xpm\" texture file extension.--"

# define MULT_TEXTURES_ERR 3
# define MULT_TEXTURES_TXT "ERROR\n--Multiple texture parameter is giving--"

# define MULT_FLOOR_ERR 4
# define MULT_FLOOR_TXT "ERROR\n--Multiple floor color parameter is giving--"

# define MULT_CEILING_ERR 5
# define MULT_CEILING_TXT "ERROR\n--Giving multiple ceiling color parameter--"

# define WRONG_COLOR_FORMAT_ERR 6
# define WRONG_COLOR_FORMAT_TXT "ERROR\n--Wrong format of color parameter--"

# define WRONG_RES_FORMAT_ERR 7
# define WRONG_RES_FORMAT_TXT "ERROR\n--Wrong format of resolution parameter--"

# define INCOMPLETE_PARAM_SET_ERR 8
# define INCOMPLETE_PARAM_SET_TXT "ERROR\n--Incomplete set of parameters--"

# define WRONG_COLOR_VALUE_ERR 9
# define WRONG_COLOR_VALUE_TXT "ERROR\n--Correct color value is [0;255]--"

# define MULTIPLE_PLAYER_ERR 10
# define MULTIPLE_PLAYER_TXT "ERROR\n--There are multiple players on the map--"

# define NO_PLAYER_ERR 11
# define NO_PLAYER_TXT "ERROR\n--There is no player on the map--"

# define WRONG_CON_EX_ERR 12
# define WRONG_CON_EX_TXT "ERROR\n--Expected \".cub\" config file extension.--"

# define WRONG_NUMBER_OF_ARGS_ERR 13
# define WRONG_NUMBER_OF_ARGS_TXT "ERROR\n--Wrong number of arguments--"

# define WRONG_SEC_ARG_ERR 14
# define WRONG_SEC_ARG_TXT "ERROR\n--Expected second argument is \"--save\"--"

# define WRONG_CONFIG_NAME_ERR 15
# define WRONG_CONFIG_NAME_TXT "ERROR\n--Wrong name of config file--\n"

# define NOT_VALID_MAP_ERR 16
# define NOT_VALID_MAP_TXT "ERROR\n--The map is not valid--"

# define RES_TOO_SMALL_ERR 17
# define RES_TOO_SMALL_TXT "ERROR\n--Resolution is too small. Min 4 pix--"

# define SCREENSHOT_ERR 18
# define SCREENSHOT_TXT "ERROR\n--Couldn't create screenshot.bmp--"

# define GNL_ERR 19
# define GNL_TXT "ERROR\n--GNL error occured--"

# define MALLOC_ERR 20
# define MALLOC_TXT "ERROR\n--Malloc error occured--\n"

#endif
