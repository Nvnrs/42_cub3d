/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:10 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/12 15:53:32 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Calculte the angle between each ray in degree.
 */
float	calculate_angle_between_each_ray(void)
{
	return (FOV / SCREEN_WIDTH);
}

/**
 * Calculte the slope of a ray with its angle in degree.
 */
float	calculate_ray_slope(t_ray ray, t_player player)
{
	return (tanf(convert_degree_to_radian(ray.angle_related_to_player)));
}
/**
 * Calculate the ray's y intercept from the ray slope and the player's position.
 */
float	calculate_ray_y_intercept(t_ray ray, t_player player)
{
	return (player.y - ray.slope * player.x);
}

// /**
//  * Calculate the ray's direction from the player's direction angle and the ray's angle.
//  */
// float	calculate_ray_direction(t_player player, t_ray ray)
// {
// 	return (player.direction_angle - FOV / 2 + ray.angle);//attention quand l'angle passe par 0/360 degree, a ajouter.
// }
