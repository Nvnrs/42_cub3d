/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:15:45 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/14 16:57:35 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Calculate the wall height perceived with one ray.
 */
float	calculate_wall_height(float distance_between_player_and_wall)
{
	float	distance_between_player_and_plane;
	
	distance_between_player_and_plane = calculate_distance_between_player_and_plane();
	printf("distance joueur/plan: %f\n", distance_between_player_and_plane);
	return (distance_between_player_and_plane * CUBE_SIZE / distance_between_player_and_wall);
}
