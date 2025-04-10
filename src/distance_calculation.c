/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:05 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/10 15:32:22 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Calculte the distance between the player and the camera plane.
 */
float	calculate_distance_between_player_and_plane(void)
{
	return ((SCREEN_WIDTH / 2) / tan(convert_degree_to_radian(FOV/2)));
}

/**
 * Calculate the distance between two points.
 */
float	calculate_distance_between_two_points(int xa, int ya, int xb, int yb)
{
	return (sqrtf(pow(xb - xa, 2) + pow(yb - ya, 2)));
}

float	fix_fish_eye_effect(t_ray ray, t_player player)
{
	// if (ray.direction_angle < player.direction_angle)
	// 	return (ray.smallest_distance * cos(convert_degree_to_radian(30)));
	// else if (ray.direction_angle > player.direction_angle)
	// 	return (ray.smallest_distance * cos(convert_degree_to_radian(-30)));
	// else
	// 	return (ray.smallest_distance);
	float	angle;
	
	angle = convert_degree_to_radian(player.direction_angle - ray.direction_angle);
	return (ray.smallest_distance * cos(angle));
}
