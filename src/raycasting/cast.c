/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:55:14 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/17 10:17:41 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast(t_ray *ray, t_map map, int map_x, int map_y)
{
	ray->hit = FALSE;

	while (ray->hit == FALSE)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			map_x += ray->step_x;
			if (ray->dir_x >= 0)
				ray->side = EAST;
			else
				ray->side = WEST;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			map_y += ray->step_y;
			if (ray->dir_y >= 0)
				ray->side = NORTH;
			else
				ray->side = SOUTH;
		}
		if (map.grid[map_y][map_x] != '0')
			ray->hit = TRUE;
	}
}
