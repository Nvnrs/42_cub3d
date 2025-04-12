/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:13 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/12 16:35:07 by pchateau         ###   ########.fr       */
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
	ray->real_angle = ray->direction_angle;
	if (ray->direction_angle >= 360)	
		ray->direction_angle -= 360;
	else if (ray->direction_angle < 0)
		ray->direction_angle += 360;
}

void	where_was_the_wall_hit(t_ray *ray)
{
	ray->is_north_hit = FALSE;
	ray->is_east_hit = FALSE;
	ray->is_south_hit = FALSE;
	ray->is_west_hit = FALSE;
	if (ray->is_facing_right && ray->is_vertical_smallest)
	{
		ray->is_west_hit = TRUE;
		printf("WEST was hit\n");
	}
	else if (ray->is_facing_left && ray->is_vertical_smallest)
	{
		ray->is_east_hit = TRUE;
		printf("EAST was hit\n");
	}
	else if (ray->is_facing_down && ray->is_horizontal_smallest)
	{
		ray->is_north_hit = TRUE;
		printf("NORTH was hit\n");	
	}
	else if (ray->is_facing_up && ray->is_horizontal_smallest)
	{
		ray->is_south_hit = TRUE;
		printf("SOUTH was hit\n");	
	}
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
		ray.x_on_screen = SCREEN_WIDTH - 1 - i;
		printf("---------------------------\n");
		printf("Ray number: %d\n\n", ray.x_on_screen);
		ray.direction_angle = player.direction_angle - FOV / 2 + (double)i / SCREEN_WIDTH * FOV;
		ray.angle_related_to_player = ray.direction_angle - player.direction_angle;
		printf("Angle related to player: %f\n", ray.angle_related_to_player);
		ray_direction_angle_correction(&ray);
		where_is_the_ray_facing(&ray);
		ray.slope = calculate_ray_slope(ray, player);
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
			ray.is_vertical_smallest = TRUE;
			ray.is_horizontal_smallest = FALSE;
		}
		else
		{
			ray.smallest_distance = ray.distance_horizontal_intersection;
			ray.x_smallest = ray.x_hor;
			ray.y_smallest = ray.y_hor;
			ray.is_vertical_smallest = FALSE;
			ray.is_horizontal_smallest = TRUE;
		}
		where_was_the_wall_hit(&ray);
		ray.fixed_distance = fix_fish_eye_effect(ray, player);
		ray.wall_height = calculate_wall_height(ray.smallest_distance);
		if (ray.x_on_screen == 319)
			print_ray_info(ray);
		printf("Player x: %d\n", player.x);
		printf("Player y: %d\n", player.y);
		printf("Player direction: %f\n", player.direction_angle);
		draw_wall(images, ray);
		draw_ray_on_minimap(player, ray, images, map);
		i++;
	}
}
