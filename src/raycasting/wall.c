/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:43:02 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/18 14:46:39 by nveneros         ###   ########.fr       */
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

void	find_texture_x(t_ray *ray, mlx_texture_t *texture)
{
	ray->tex_x = ray->wall_x * texture->width;
	if (ray->side == EAST || ray->side == SOUTH)//faire attention ici
		ray->tex_x = texture->width - ray->tex_x - 1;
}

// void	draw_vertical_line_texture(mlx_image_t *image, t_ray *ray, int x, mlx_texture_t *texture)
// {
// 	double	step;
// 	double	tex_pos;
// 	int		y;
// 	int		tex_y;
// 	uint32_t	color;

// 	step = 1.0 * texture->height / ray->line_height;
// 	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
// 	y = ray->draw_start;
// 	while (y < ray->draw_end)
// 	{
// 		tex_y = tex_pos & (texture->height - 1);
// 		tex_pos += step;
// 		color = texture->pixels[texture->height * tex_y + ray->tex_x];//il faut transformer le contenu de pixels
// 		mlx_put_pixel(image, x, y, color);
// 		y++;
// 	}
// }

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
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x0000FFFF);
	else if (ray->side == SOUTH)//SOUTH -> GREEN
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x00FF00FF);
	else if (ray->side == EAST)//EAST -> RED
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0xFF0000FF);
	else if (ray->side == WEST)//WEST -> PURPLE
		draw_vertical_line(images->wall, ray->draw_start, ray->draw_end, x, 0x800080FF);
		// draw_vertical_line_texture(images->wall, ray, x, map.textures.north);
		// draw_vertical_line_texture(images->wall, ray, x, map.textures.south);
		// draw_vertical_line_texture(images->wall, ray, x, map.textures.east);
		// draw_vertical_line_texture(images->wall, ray, x, map.textures.west);
}
