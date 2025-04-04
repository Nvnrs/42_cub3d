/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:08 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/04 10:52:47 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Check if the given point in the map's grid is in a wall or not.
 * Return TRUE or FALSE.
 */
t_bool	is_wall(int x, int y, t_map map)
{
	int	x_in_grid;
	int	y_in_grid;

	x_in_grid = x / CUBE_SIZE;
	y_in_grid = y / CUBE_SIZE;
	if (x_in_grid >= map.x_max || y_in_grid >= map.y_max || map.grid[y_in_grid][x_in_grid] == '1')
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

	ray.direction = calculate_ray_direction(player, ray);
	pixel_to_first_intersection = player.x % CUBE_SIZE;//attention a la limite
	if (ray.direction >= 0 && ray.direction <= 180)//attention a la limite
		x = player.x + pixel_to_first_intersection;
	else
		x = player.x - pixel_to_first_intersection;
	y = ray.slope * x + ray.y_intercept;
	while (!is_wall(x, y, map))
	{
		if (ray.direction >= 0 && ray.direction <= 180)//attention a la limite
			x += CUBE_SIZE;
		else
			x -= CUBE_SIZE;
		y = ray.slope * x + ray.y_intercept;
	}
	if (is_wall(x, y, map))
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

	ray.direction = calculate_ray_direction(player, ray);
	pixel_to_first_intersection = player.y % CUBE_SIZE;//attention a la limite
	if (ray.direction >= 90 && ray.direction <= 270)//attention a la limite
		y = player.y + pixel_to_first_intersection;
	else
		y = player.y - pixel_to_first_intersection;
	x = (y - ray.y_intercept) / ray.slope;
	while (!is_wall(x, y, map))
	{
		if (ray.direction >= 90 && ray.direction <= 270)//attention a la limite
			y += CUBE_SIZE;
		else
			y -= CUBE_SIZE;
		x = (y - ray.y_intercept) / ray.slope;
	}
	if (is_wall(x, y, map))
		distance_between_player_and_wall = calculate_distance_between_two_points(player.x, player.y, x, y);
	return (distance_between_player_and_wall);
}
