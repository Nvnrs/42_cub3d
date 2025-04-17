/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:43:02 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/17 10:16:52 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_perpendicular_wall_dist(t_ray *ray)
{
	if (ray->side == EAST || ray->side == WEST)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	draw_wall(t_ray *ray, t_images *images, int x)
{
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height) / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == NORTH)//NORTH -> BLUE
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x0000FFFF);
	else if (ray->side == SOUTH)//SOUTH -> GREEN
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x00FF00FF);
	else if (ray->side == EAST)//EAST -> RED
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0xFF0000FF);
	else if (ray->side == WEST)//WEST -> PURPLE
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x800080FF);
}
