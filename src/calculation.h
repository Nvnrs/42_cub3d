#ifndef CALCULATION_H
# define CALCULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "../lib/MYLIB42/mylib42.h"

#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	200
#define CUBE_SIZE		64
#define FOV 			60.0
#define M_PI			3.14159265358979323846

typedef	struct s_map
{
	char **grid;
	int	x_max;
	int	y_max;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
	double	direction_angle;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	slope;
	double	y_intercept;
	double	direction;
	int		distance_vertical_intersection;
	int		distance_horizontal_intersection;
	int		smallest_distance;
}	t_ray;

void	raycasting(t_player player, t_map map);

double convert_degree_to_radian(double degree);

int	calculate_distance_between_two_points(int xa, int ya, int xb, int yb);
int	calculate_distance_between_player_and_plane(void);

t_bool	is_wall(int x, int y, t_map map);
int	vertical_intersection(t_ray ray, t_player player, t_map map);
int	horizontal_intersection(t_ray ray, t_player player, t_map map);

double	calculate_angle_between_each_ray(void)
double	calculate_ray_slope(t_ray ray);
double	calculate_ray_y_intercept(t_ray ray, t_player player);
double	calculate_ray_direction(t_player player, t_ray ray);

#endif