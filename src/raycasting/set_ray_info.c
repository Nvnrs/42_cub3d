/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:48:12 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/21 09:32:52 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_camera_x(t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
}

void	set_dir(t_ray *ray, t_player player)
{
	ray->dir_x = player.dir_x + player.plane_x * ray->camera_x;
	ray->dir_y = player.dir_y + player.plane_y * ray->camera_x;
}

void	set_delta_dist(t_ray *ray)
{
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_x == 0)
		ray->delta_dist_x = INFINITY;
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_y == 0)
		ray->delta_dist_y = INFINITY;
}

void	set_side_dist(t_ray *ray, t_player player, int map_x, int map_y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player.x - map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (map_x + 1.0 - player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player.y - map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (map_y + 1.0 - player.y) * ray->delta_dist_y;
	}
}
