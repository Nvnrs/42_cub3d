/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:08 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/07 14:32:21 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Check if the given point in the map's grid is in a wall or not.
 * Return TRUE or FALSE.
 */
t_bool	is_wall(int x, int y, t_map map, t_ray ray)
{
	int	x_in_grid;
	int	y_in_grid;

	if (ray.is_facing_left)
		x_in_grid = x / CUBE_SIZE;
	else
		x_in_grid = x / CUBE_SIZE;
	if (ray.is_facing_up)
		y_in_grid = y / CUBE_SIZE;
	else
		y_in_grid = y / CUBE_SIZE;
	if (x_in_grid >= map.x_max
		|| x_in_grid < 0
		|| y_in_grid >= map.y_max
		|| y_in_grid < 0
		|| map.grid[y_in_grid][x_in_grid] == '1')
		return (TRUE);
	return (FALSE);
}

/**
 * Calculate the distance between the player and the first wall encountered.
 * Check at each vertical intersection if the new cube is a wall.
 */
int	vertical_intersection(t_ray ray, t_player player, t_map map)
{
	int	pixel_to_first_intersection;
	int	x;
	int	y;
	int	distance_between_player_and_wall;
	int	x_step;
	// int	y_step;

	pixel_to_first_intersection = player.x % CUBE_SIZE;//attention a la limite
	if (ray.direction_angle >= 0 && ray.direction_angle <= 180)//attention a la limite
		x = player.x + pixel_to_first_intersection;
	else
		x = player.x - pixel_to_first_intersection;
	// if (ray.is_facing_right)
	// 	x = (player.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	// else
	// 	x = (player.x / CUBE_SIZE) * CUBE_SIZE;
	y = ray.slope * x + ray.y_intercept;
	printf("VERTICAL_INTERSECTION FIRST x: %d\n", x);
	printf("VERTICAL_INTERSECTION FIRST y: %d\n", y);
	if (ray.is_facing_right)
		x_step = CUBE_SIZE;
	else
		x_step = -CUBE_SIZE;
	// y_step = x_step * ray.slope;
	while (!is_wall(x, y, map, ray))
	{
		// if (ray.direction_angle >= 0 && ray.direction_angle <= 180)//attention a la limite
		// 	x += CUBE_SIZE;
		// else
		// 	x -= CUBE_SIZE;//+1
		x += x_step;
		y = ray.slope * x + ray.y_intercept;
		// y += y_step;
	}
	//if (is_wall(x, y, map))
	printf("VERTICAL_INTERSECTION LAST x: %d\n", x);
	printf("VERTICAL_INTERSECTION LAST y: %d\n", y);
	printf("x_in_grid = %d\n", x / CUBE_SIZE);
	printf("y_in_grid = %d\n", y / CUBE_SIZE);
	distance_between_player_and_wall = calculate_distance_between_two_points(player.x, player.y, x, y);
	return (distance_between_player_and_wall);
}

/**
 * Calculate the distance between the player and the first wall encountered.
 * Check at each horizontal intersection if the new cube is a wall.
 */
int	horizontal_intersection(t_ray ray, t_player player, t_map map)
{
	int	pixel_to_first_intersection;
	int	x;
	int	y;
	int	distance_between_player_and_wall;
	// int	x_step;
	int	y_step;

	pixel_to_first_intersection = player.y % CUBE_SIZE;//attention a la limite
	// if (ray.direction_angle >= 90 && ray.direction_angle <= 270)//attention a la limite
	// 	y = player.y + pixel_to_first_intersection;
	// else
	// 	y = player.y - pixel_to_first_intersection;
	if (ray.is_facing_down)
		y = player.y + pixel_to_first_intersection;
	else
		y = player.y - pixel_to_first_intersection;
		// y = (player.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		// y = (player.y / CUBE_SIZE) * CUBE_SIZE;
	x = (y - ray.y_intercept) / ray.slope;
	printf("HORIZONTAL_INTERSECTION FIRST y: %d\n", y);
	printf("HORIZONTAL_INTERSECTION FIRST x: %d\n", x);
	if (ray.is_facing_down)
		y_step = CUBE_SIZE;
	else
		y_step = -CUBE_SIZE;
	// x_step = y_step / ray.slope;
	while (!is_wall(x, y, map, ray))
	{
		// if (ray.direction_angle >= 90 && ray.direction_angle <= 270)//attention a la limite
		// 	y += CUBE_SIZE;
		// else
		// 	y -= CUBE_SIZE;
		y += y_step;
		x = (y - ray.y_intercept) / ray.slope;
		// x += x_step;
	}
	//if (is_wall(x, y, map))
	printf("HORIZONTAL_INTERSECTION LAST y: %d\n", y);
	printf("HORIZONTAL_INTERSECTION LAST x: %d\n", x);
	printf("x_in_grid = %d\n", x / CUBE_SIZE);
	printf("y_in_grid = %d\n", y / CUBE_SIZE);
	distance_between_player_and_wall = calculate_distance_between_two_points(player.x, player.y, x, y);
	return (distance_between_player_and_wall);
}
