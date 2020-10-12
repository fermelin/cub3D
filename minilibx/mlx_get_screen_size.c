#include "mlx_int.h"
#include "mlx.h"

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl3.h>

int	mlx_get_screen_size(mlx_ptr_t *mlx_ptr, int *sizex, int *sizey)
{
	*sizex = DisplayWidth (mlx_ptr->display, mlx_ptr->screen);
	*sizey = DisplayHeight (mlx_ptr->display, mlx_ptr->screen);
	return (0);
}
