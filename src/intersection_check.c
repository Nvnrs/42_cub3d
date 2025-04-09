/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:08 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/09 10:52:03 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Check if the given point in the map's grid is in a wall or not.
 * Return TRUE or FALSE.
 */
t_bool	is_wall(float x, float y, t_map map, t_ray ray, int is_vertical_check)
{
	int	x_in_grid;
	int	y_in_grid;

	if (is_vertical_check == 0) // intersection verticale
	{
		if (ray.is_facing_left)
			x_in_grid = (x - 1) / CUBE_SIZE;
		else
			x_in_grid = x / CUBE_SIZE;
		y_in_grid = y / CUBE_SIZE;
	}
	else // intersection horizontale
	{
		if (ray.is_facing_up)
			y_in_grid = (y - 1) / CUBE_SIZE;
		else
			y_in_grid = y / CUBE_SIZE;
		x_in_grid = x / CUBE_SIZE;
	}
	// if (ray.is_facing_left)
	// 	x_in_grid = (x - 1) / CUBE_SIZE;
	// else
	// 	x_in_grid = x / CUBE_SIZE;
	// if (ray.is_facing_up)
	// 	y_in_grid = (y - 1) / CUBE_SIZE;
	// else
	// 	y_in_grid = y / CUBE_SIZE;
	// x_in_grid = x / CUBE_SIZE;
	// y_in_grid = y / CUBE_SIZE;
	if (x_in_grid >= map.x_max
		|| x_in_grid < 0
		|| y_in_grid >= map.y_max
		|| y_in_grid < 0
		|| map.grid[y_in_grid][x_in_grid] == '1')
	{
		printf("[WALL CHECK] Testing (%f, %f) -> map.grid[%d][%d] = 1\n",
       x, y, y_in_grid, x_in_grid);	
		return (TRUE);
	}
	printf("[WALL CHECK] Testing (%f, %f) -> map.grid[%d][%d] = %c\n",
       x, y,  y_in_grid, x_in_grid, map.grid[y_in_grid][x_in_grid]);
	return (FALSE);
}

/**
 * Calculate the distance between the player and the first wall encountered.
 * Check at each vertical intersection if the new cube is a wall.
 */
void	vertical_intersection(t_ray *ray, t_player player, t_map map)
{
	float	pixel_to_first_intersection;
	float	x;
	float	y;
	// float	distance_between_player_and_wall;
	float	x_step;
	float	y_step;

	pixel_to_first_intersection = player.x % CUBE_SIZE;
	if (ray->is_facing_right)
		x = player.x + pixel_to_first_intersection;
	else
		x = player.x - pixel_to_first_intersection;
		// x = (player.x / CUBE_SIZE) * CUBE_SIZE;
		// x = (player.x / CUBE_SIZE) * CUBE_SIZE - 1;
	y = ray->slope * x + ray->y_intercept;
	printf("VERTICAL_INTERSECTION FIRST x: %f\n", x);
	printf("VERTICAL_INTERSECTION FIRST y: %f\n", y);
	if (ray->is_facing_right)
		x_step = CUBE_SIZE;
	else
		x_step = -CUBE_SIZE;
	y_step = x_step * ray->slope;
	while (!is_wall(x, y, map, *ray, 1))
	{
		x += x_step;
		y += y_step;
	}
	// printf("VERTICAL_INTERSECTION LAST x: %f\n", x);
	// printf("VERTICAL_INTERSECTION LAST y: %f\n", y);
	// printf("x_in_grid = %f\n", x / CUBE_SIZE);
	// printf("y_in_grid = %f\n", y / CUBE_SIZE);
	ray->x_ver = x;
	ray->y_ver = y;
	ray->distance_vertical_intersection = calculate_distance_between_two_points(player.x, player.y, x, y);
	// distance_between_player_and_wall = calculate_distance_between_two_points(player.x, player.y, x, y);
	// return (distance_between_player_and_wall);
}

/**
 * Calculate the distance between the player and the first wall encountered.
 * Check at each horizontal intersection if the new cube is a wall.
 */
void	horizontal_intersection(t_ray *ray, t_player player, t_map map)
{
	float	pixel_to_first_intersection;
	float	x;
	float	y;
	// float	distance_between_player_and_wall;
	float	y_step;
	float	x_step;

	pixel_to_first_intersection = player.y % CUBE_SIZE;//attention a la limite
	if (ray->is_facing_down)
		y = player.y + pixel_to_first_intersection;
	else
		y = player.y - pixel_to_first_intersection;
		// y = (player.y / CUBE_SIZE) * CUBE_SIZE;
		// y = (player.y / CUBE_SIZE) * CUBE_SIZE - 1;
	x = (y - ray->y_intercept) / ray->slope;
	// printf("HORIZONTAL_INTERSECTION FIRST y: %f\n", y);
	// printf("HORIZONTAL_INTERSECTION FIRST x: %f\n", x);
	if (ray->is_facing_down)
		y_step = CUBE_SIZE;
	else
		y_step = -CUBE_SIZE;
	x_step = y_step / ray->slope;
	while (!is_wall(x, y, map, *ray, 0))
	{
		y += y_step;
		x += x_step;
	}
	// printf("HORIZONTAL_INTERSECTION LAST y: %f\n", y);
	// printf("HORIZONTAL_INTERSECTION LAST x: %f\n", x);
	// printf("x_in_grid = %f\n", x / CUBE_SIZE);
	// printf("y_in_grid = %f\n", y / CUBE_SIZE);
	ray->x_hor = x;
	ray->y_hor = y;
	ray->distance_horizontal_intersection = calculate_distance_between_two_points(player.x, player.y, x, y);
	// distance_between_player_and_wall = calculate_distance_between_two_points(player.x, player.y, x, y);
	// return (distance_between_player_and_wall);
}
