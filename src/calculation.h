/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:03 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/08 18:01:46 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATION_H
# define CALCULATION_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <math.h>
// #include "../lib/MLX42/include/MLX42/MLX42.h"//modifier dans le Makefile
// #include "../lib/MYLIB42/mylib42.h"
#include "cub3d.h"

// #define SCREEN_WIDTH	320
// #define SCREEN_HEIGHT	200
// #define CUBE_SIZE		64
// #define FOV 			60.0
// #define M_PI			3.14159265358979323846

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
	float	direction_angle;
}	t_player;

typedef struct s_ray
{
	float	direction_angle;
	float	slope;
	float	y_intercept;
	float		distance_vertical_intersection;
	float		distance_horizontal_intersection;
	float		smallest_distance;
	float		fixed_distance;
	float		wall_height;
	int		x_on_screen;
	t_bool	is_facing_right;
	t_bool	is_facing_left;
	t_bool	is_facing_up;
	t_bool	is_facing_down;
}	t_ray;

void	raycasting(t_player player, t_map map, t_images *images);

float convert_degree_to_radian(float degree);

float	calculate_distance_between_two_points(int xa, int ya, int xb, int yb);
float	calculate_distance_between_player_and_plane(void);
float	fix_fish_eye_effect(t_ray ray, t_player player);

t_bool	is_wall(float x, float y, t_map map, t_ray ray, int is_vertical_check);
float	vertical_intersection(t_ray ray, t_player player, t_map map);
float	horizontal_intersection(t_ray ray, t_player player, t_map map);

float	calculate_angle_between_each_ray(void);
float	calculate_ray_slope(t_ray ray);
float	calculate_ray_y_intercept(t_ray ray, t_player player);
//float	calculate_ray_direction(t_player player, t_ray ray);

float	calculate_wall_height(float distance_between_player_and_wall);

void	draw_wall(t_images *images, t_ray ray);

#endif
