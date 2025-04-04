/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:05 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/04 10:52:44 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Calculte the distance between the player and the camera plane.
 */
int	calculate_distance_between_player_and_plane(void)
{
	return ((SCREEN_WIDTH / 2) / tan(convert_degree_to_radian(FOV/2)));
}

/**
 * Calculate the distance between two points.
 */
int	calculate_distance_between_two_points(int xa, int ya, int xb, int yb)
{
	return (sqrt(pow(xb - xa, 2) + pow(yb - ya, 2)));
}
