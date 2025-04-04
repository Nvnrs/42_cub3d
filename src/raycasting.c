/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:13 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/04 13:52:19 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Cast rays in the player's field of view (FOV).
 */
void	raycasting(t_player player, t_map map)
{
	t_ray	ray;
	int		i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray.direction_angle = player.direction_angle - FOV / 2 + (double)i / SCREEN_WIDTH * FOV;
		ray.slope = calculate_ray_slope(ray);
		ray.y_intercept = calculate_ray_y_intercept(ray, player);
		ray.distance_vertical_intersection = vertical_intersection(ray, player, map);
		ray.distance_horizontal_intersection = horizontal_intersection(ray, player, map);
		if (ray.distance_vertical_intersection < ray.distance_horizontal_intersection)
			ray.smallest_distance = ray.distance_vertical_intersection;
		else
			ray.smallest_distance = ray.distance_horizontal_intersection;
		ray.fixed_distance = fix_fish_eye_effect(ray, player);
		printf("ray number %d -> wall height: %d\n", i, calculate_wall_height(ray.fixed_distance));
		i++;
	}
}
