#include <math.h>
#include <stdio.h>

#define FOV 5 * M_PI 

int	main(void)
{
	double	dir = 0;
	double	start;
	double	end;
	start = dir - (FOV / 2);
	end = dir + (FOV / 2);
	while (start <= end)
	{
	printf("%f\n", cos(start));

	
	start += (FOV) / 2560;
	}
}
