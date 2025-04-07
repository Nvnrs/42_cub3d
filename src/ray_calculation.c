/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:10 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/07 14:43:17 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Calculte the angle between each ray in degree.
 */
double	calculate_angle_between_each_ray(void)
{
	return (FOV / SCREEN_WIDTH);
}

/**
 * Calculte the slope of a ray with its angle in degree.
 */
double	calculate_ray_slope(t_ray ray)
{
	return (tan(convert_degree_to_radian(ray.direction_angle - 90)));
}
/**
 * Calculate the ray's y intercept from the ray slope and the player's position.
 */
double	calculate_ray_y_intercept(t_ray ray, t_player player)
{
	return (player.y - ray.slope * player.x);
}

// /**
//  * Calculate the ray's direction from the player's direction angle and the ray's angle.
//  */
// double	calculate_ray_direction(t_player player, t_ray ray)
// {
// 	return (player.direction_angle - FOV / 2 + ray.angle);//attention quand l'angle passe par 0/360 degree, a ajouter.
// }
