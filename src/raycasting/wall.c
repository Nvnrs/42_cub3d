/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:43:02 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/21 09:34:00 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_wall_hitpoint(t_ray *ray, t_player player)
{
	if (ray->side == EAST | ray->side == WEST)
		ray->wall_x = player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = player.x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	find_texture_x(t_ray *ray, t_map map)
{
	t_texture	texture;

	if (ray->side == NORTH)
		texture = map.textures.north;
	else if (ray->side == SOUTH)
		texture = map.textures.south;
	else if (ray->side == EAST)
		texture = map.textures.east;
	else if (ray->side == WEST)
		texture = map.textures.west;
	ray->tex_x = ray->wall_x * texture.width;
}

void	calculate_perpendicular_wall_dist(t_ray *ray)
{
	if (ray->side == EAST || ray->side == WEST)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	draw_wall(t_ray *ray, t_images *images, int x, t_map map)
{
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height) / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == NORTH)
		draw_vertical_line_texture(images->wall, ray, x, map.textures.north);
	else if (ray->side == SOUTH)
		draw_vertical_line_texture(images->wall, ray, x, map.textures.south);
	else if (ray->side == EAST)
		draw_vertical_line_texture(images->wall, ray, x, map.textures.east);
	else if (ray->side == WEST)
		draw_vertical_line_texture(images->wall, ray, x, map.textures.west);
}
