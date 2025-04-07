/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:15:45 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/07 13:48:34 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Calculate the wall height perceived with one ray.
 */
int	calculate_wall_height(int distance_between_player_and_wall)
{
	int	distance_between_player_and_plane;
	
	distance_between_player_and_plane = calculate_distance_between_player_and_plane();
	printf("distance joueur/plan: %d\n", distance_between_player_and_plane);
	return (distance_between_player_and_plane * CUBE_SIZE / distance_between_player_and_wall);
}
