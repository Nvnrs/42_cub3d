/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:13 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/07 14:44:23 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "cub3d.h"

void	print_ray_info(t_ray ray)
{
	printf("---------------------------\n");
	printf("Ray number: %d\n\n", ray.x_on_screen);
	printf("Direction angle: %f\n", ray.direction_angle);
	printf("Slope: %f\n", ray.slope);
	printf("Y-intercept: %f\n", ray.y_intercept);
	printf("Vertical intersection distance: %d\n", ray.distance_vertical_intersection);
	printf("Horizontal intersection distance: %d\n", ray.distance_horizontal_intersection);
	printf("Smallest intersection distance: %d\n", ray.smallest_distance);
	printf("Fixed distance: %d\n", ray.fixed_distance);
	printf("Wall height: %d\n", ray.wall_height);
	if (ray.is_facing_right)
		printf("Facing right\n");
	if (ray.is_facing_left)
		printf("Facing left\n");
	if (ray.is_facing_down)
		printf("Facing down\n");
	if (ray.is_facing_up)
		printf("Facing up\n");
}

/**
 * Cast rays in the player's field of view (FOV).
 */
void	raycasting(t_player player, t_map map, t_images *images)
{
	t_ray	ray;
	int		i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray.x_on_screen = i;
		ray.direction_angle = player.direction_angle - FOV / 2 + (double)i / SCREEN_WIDTH * FOV;
		if (ray.direction_angle > 0 && ray.direction_angle < 180)
		{
			ray.is_facing_right = TRUE;
			ray.is_facing_left = FALSE;
		}
		else
		{
			ray.is_facing_right = FALSE;
			ray.is_facing_left = TRUE;
		}
		if (ray.direction_angle > 90 && ray.direction_angle < 270)
		{
			ray.is_facing_down = TRUE;
			ray.is_facing_up = FALSE;
		}
		else
		{
			ray.is_facing_down = FALSE;
			ray.is_facing_up = TRUE;
		}
		ray.slope = calculate_ray_slope(ray);
		ray.y_intercept = calculate_ray_y_intercept(ray, player);
		ray.distance_vertical_intersection = vertical_intersection(ray, player, map);
		ray.distance_horizontal_intersection = horizontal_intersection(ray, player, map);
		if (ray.distance_vertical_intersection < ray.distance_horizontal_intersection)
			ray.smallest_distance = ray.distance_vertical_intersection;
		else
			ray.smallest_distance = ray.distance_horizontal_intersection;
		ray.fixed_distance = fix_fish_eye_effect(ray, player);
		ray.wall_height = calculate_wall_height(ray.fixed_distance);
		draw_wall(images, ray);
		// printf("ray number %d -> wall height: %d\n", i, ray.wall_height);
		print_ray_info(ray);
		i++;
	}
}
