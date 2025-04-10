/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:13 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/10 15:41:43 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "cub3d.h"

void	print_ray_info(t_ray ray)
{
	// printf("---------------------------\n");
	// printf("Ray number: %d\n\n", ray.x_on_screen);
	printf("Direction angle: %f\n", ray.direction_angle);
	printf("Slope: %f\n", ray.slope);
	printf("Y-intercept: %f\n", ray.y_intercept);
	printf("Vertical intersection distance: %f\n", ray.distance_vertical_intersection);
	printf("Horizontal intersection distance: %f\n", ray.distance_horizontal_intersection);
	printf("Smallest intersection distance: %f\n", ray.smallest_distance);
	printf("Fixed distance: %f\n", ray.fixed_distance);
	printf("Wall height: %f\n", ray.wall_height);
	if (ray.is_facing_right)
		printf("Facing right\n");
	if (ray.is_facing_left)
		printf("Facing left\n");
	if (ray.is_facing_down)
		printf("Facing down\n");
	if (ray.is_facing_up)
		printf("Facing up\n");
}

void	where_is_the_ray_facing(t_ray *ray)
{
	if (ray->direction_angle > 0 && ray->direction_angle < 180)
	{
		ray->is_facing_up = TRUE;
		ray->is_facing_down = FALSE;
	}
	else
	{
		ray->is_facing_up = FALSE;
		ray->is_facing_down = TRUE;
	}
	if (ray->direction_angle > 90 && ray->direction_angle < 270)
	{
		ray->is_facing_left = TRUE;
		ray->is_facing_right = FALSE;
	}
	else
	{
		ray->is_facing_left = FALSE;
		ray->is_facing_right = TRUE;
	}
}

void	ray_direction_angle_correction(t_ray *ray)
{
	if (ray->direction_angle >= 360)
		ray->direction_angle -= 360;
	else if (ray->direction_angle < 0)
		ray->direction_angle += 360;
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
		printf("---------------------------\n");
		printf("Ray number: %d\n\n", ray.x_on_screen);
		ray.direction_angle = player.direction_angle - FOV / 2 + (double)i / SCREEN_WIDTH * FOV;
		ray_direction_angle_correction(&ray);
		where_is_the_ray_facing(&ray);
		ray.slope = calculate_ray_slope(ray);
		if (ray.direction_angle == 0 || ray.direction_angle == 180 || ray.direction_angle == 360)
			ray.slope = 0;
		if (ray.direction_angle == 90 || ray.direction_angle == 270)
			ray.slope = INFINITY;
		ray.y_intercept = calculate_ray_y_intercept(ray, player);
		// ray.distance_vertical_intersection = vertical_intersection(ray, player, map);
		vertical_intersection(&ray, player, map);
		// ray.distance_horizontal_intersection = horizontal_intersection(&ray, player, map);
		horizontal_intersection(&ray, player, map);
		if (ray.distance_vertical_intersection < ray.distance_horizontal_intersection)
		{
			ray.smallest_distance = ray.distance_vertical_intersection;
			ray.x_smallest = ray.x_ver;
			ray.y_smallest = ray.y_ver;
		}
		else
		{
			ray.smallest_distance = ray.distance_horizontal_intersection;
			ray.x_smallest = ray.x_hor;
			ray.y_smallest = ray.y_hor;
		}
		ray.fixed_distance = fix_fish_eye_effect(ray, player);
		ray.wall_height = calculate_wall_height(ray.fixed_distance);
		print_ray_info(ray);
		printf("Player x: %d\n", player.x);
		printf("Player y: %d\n", player.y);
		draw_wall(images, ray);
		draw_ray_on_minimap(player, ray, images);
		i++;
	}
}
