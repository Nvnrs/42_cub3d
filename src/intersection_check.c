/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:08 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/12 10:56:22 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Check if the given point in the map's grid is in a wall or not.
 * Return TRUE or FALSE.
 */
t_bool	is_wall(int x, int y, t_map map, t_ray ray, int is_vertical_check)
{
	int	x_in_grid;
	int	y_in_grid;

	(void)is_vertical_check;
	x_in_grid = x / CUBE_SIZE;
	y_in_grid = y / CUBE_SIZE;
	if (x_in_grid >= map.x_max
		|| x_in_grid < 0
		|| y_in_grid >= map.y_max
		|| y_in_grid < 0
		|| map.grid[y_in_grid][x_in_grid] == '1')
	{
		printf("[WALL CHECK] Testing (%d, %d) -> map.grid[%d][%d] = 1\n",
       x, y, y_in_grid, x_in_grid);	
		return (TRUE);
	}
	printf("[WALL CHECK] Testing (%d, %d) -> map.grid[%d][%d] = %c\n",
       x, y,  y_in_grid, x_in_grid, map.grid[y_in_grid][x_in_grid]);
	return (FALSE);
}

/**
 * Calculate the distance between the player and the first wall encountered.
 * Check at each vertical intersection if the new cube is a wall.
 */
void	vertical_intersection(t_ray *ray, t_player player, t_map map)
{
	int	x;
	int	y;
	float	x_step;
	float	y_step;
	float	alpha;
	
	alpha = convert_degree_to_radian(fabs(player.direction_angle - ray->real_angle));//si probleme modifier ici
	printf("alpha = %f = %f\n", alpha, fabs(player.direction_angle - ray->real_angle));
	if (ray->is_facing_left)
		x = (player.x / CUBE_SIZE) * CUBE_SIZE - 1;
	else
		x = (player.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	y = player.x + (player.x - x) * tan (alpha);
	if (ray->is_facing_left)
		x_step = -CUBE_SIZE;
	else
		x_step = CUBE_SIZE;
	y_step = CUBE_SIZE * tan(alpha);
	while (!is_wall(x, y, map, *ray, 1))
	{
		x += x_step;
		y += y_step;
	}
	ray->x_ver = x;
	ray->y_ver = y;
	// ray->distance_vertical_intersection = calculate_distance_between_two_points(player.x, player.y, x, y);
	ray->distance_vertical_intersection = abs(player.x - x) / cos(alpha);
}

/**
 * Calculate the distance between the player and the first wall encountered.
 * Check at each horizontal intersection if the new cube is a wall.
 */
void	horizontal_intersection(t_ray *ray, t_player player, t_map map)
{
	int	x;
	int	y;
	float	y_step;
	float	x_step;
	float	alpha;

	alpha = convert_degree_to_radian(fabs(player.direction_angle - ray->real_angle));//si probleme modifier ici
	printf("alpha = %f = %f\n", alpha, fabs(player.direction_angle - ray->real_angle));
	if (ray->is_facing_up)
		y = (player.y / CUBE_SIZE) * CUBE_SIZE - 1;
	else
		y = (player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	x = player.x + (player.y - y) / tan(alpha);
	if (ray->is_facing_up)
		y_step = -CUBE_SIZE;
	else
		y_step = CUBE_SIZE;
	x_step = CUBE_SIZE / tan(alpha);
	while (!is_wall(x, y, map, *ray, 0))
	{
		x += x_step;
		y += y_step;
	}
	ray->x_hor = x;
	ray->y_hor = y;
	// ray->distance_horizontal_intersection = calculate_distance_between_two_points(player.x, player.y, x, y);
	ray->distance_horizontal_intersection = abs(player.x - x) / cos(alpha);
}
