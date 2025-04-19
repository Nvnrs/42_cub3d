/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:43:02 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/19 13:29:12 by pchateau         ###   ########.fr       */
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
	// printf("wall_x: %f\n", ray->wall_x);
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
	// if (ray->side == EAST || ray->side == SOUTH)//faire attention ici//utile ?
	// 	ray->tex_x = texture.width - ray->tex_x - 1;
	// printf("tex_x: %d\n", ray->tex_x);
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
	if (ray->side == NORTH)//NORTH -> BLUE
		draw_vertical_line_texture(images->wall, ray, x, map.textures.north);
	else if (ray->side == SOUTH)//SOUTH -> GREEN
		draw_vertical_line_texture(images->wall, ray, x, map.textures.south);
	else if (ray->side == EAST)//EAST -> RED
		draw_vertical_line_texture(images->wall, ray, x, map.textures.east);
	else if (ray->side == WEST)//WEST -> PURPLE
		draw_vertical_line_texture(images->wall, ray, x, map.textures.west);
		// draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x0000FFFF);
		// draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x00FF00FF);
		// draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0xFF0000FF);
		// draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x800080FF);
}
