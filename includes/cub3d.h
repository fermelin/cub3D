
#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minilibx/mlx.h"
# include <stdio.h>
# include "libft.h"
# include "errors.h"
# include <errno.h>
# include <string.h>

# define SCALE 64
# define FOV M_PI / 3

#ifdef LINUX
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ROT_LEFT 65361
# define ROT_RIGHT 65363
# define ESC 65307
# define SPEED 0.7
# define BLACK 0xff000000
#else
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ROT_LEFT 123
# define ROT_RIGHT 124
# define ESC 53
# define SPEED 1
# define BLACK 0x0
#endif

typedef	struct	s_win {
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			screen_x;
	int			screen_y;
	int			map_x;
	int			map_y;
}				t_win;

typedef struct	s_texture
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	char		*path;
	double		step_x;
}				t_texture;

typedef	struct	s_player
{
	double		x;
	double		y;
	double		dir;
	int			is_dir_left;
	int			is_dir_right;
	int			is_dir_up;
	int			is_dir_down;
	double		sin_dir;
	double		cos_dir;
	int			projection_plane;
}				t_player;

typedef struct	s_ray
{
	int			is_left;
	int			is_right;
	int			is_up;
	int			is_down;
	double		intersection_x;
	double		intersection_y;
	double		ray_len;
	double		ray_fixed;
	int			what_intersection;
	double		ray_intersection;
	int			x_line;
}				t_ray;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
	double		angle;
	double		delta_angle;
	double		hor_offset;
	double		vert_offset;
	int			size;
}				t_sprite;

typedef struct	s_movement
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			rot_left;
	int			rot_right;
}				t_movement;

typedef struct	s_wall
{
	int			is_left;
	int			is_right;
	int			is_up;
	int			is_down;
}				t_wall;

typedef struct	s_parsing
{
	int			tex[5];
	int			resolution;
	int			is_floor;
	int			is_ceiling;
	int			floor;
	int			ceiling;
	int			player;
}				t_parsing;

typedef	struct	s_all
{
	t_win		*win;
	t_player	*player;
	t_ray		*ray;
	t_texture	tex[5];
	t_sprite	*sprite;
	int			sprites_amount;
	t_movement	movements;
	t_wall		walls;
	t_parsing	parsing;
	char		**map;
	int			minimap_scale;
	int			screenshot;
	int			errnum;
	int			texture_x;
}				t_all;

void			my_mlx_pixel_put(t_win *data, int x, int y, int color);
void			my_mlx_pixel_put_texture(t_all *all, int x, int y, int color);
char			**get_map(t_all *all, int fd, char *line);
void			draw_vertical_line(t_all *all, double start);
void			set_background(t_all *all);
void			find_player(t_all *all);
void			draw_minimap(t_all *all);
void			draw_scene(t_all *all);
int				key_press(int key, t_all *all);
int				draw_screen(t_all *all);
void			parser(char *argv, t_all *all);
int				player_movement(t_all *all);
int				key_release(int key, t_all *all);
void			get_sprites_xy(t_all *all);
void			sprites_counter(t_all *all);
void			get_sprites_params(t_all *all);
void			draw_sprites(t_all *all);
void			error_processor(int errnum, t_all *all);
void			make_screenshot(t_all *all, char *argv);
void			check_map_symbols(t_all *all);
void			get_textures(t_all *all);
int				destroy_all(t_all *all);
void			win_and_image_init(t_all *all);
void			get_initial_params(t_all *all);
void			struct_init(t_all *all);
void			get_screen_resolution(t_all *all, char *trimmed, int shift);
void			get_backgrougd_color(t_all *all, char *trimmed, int shift);
int				mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

#endif
