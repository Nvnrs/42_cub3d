/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:47:09 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/16 14:37:51 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_raycasting(t_player player, t_map map, t_images *images)
{
	int		x;
	t_ray	ray;
	int		map_x;
	int		map_y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray.dir_x = player.dir_x + player.plane_x * ray.camera_x;
		ray.dir_y = player.dir_y + player.plane_y * ray.camera_x;

		map_x = (int)player.x;
		map_y = (int)player.y;
		
		ray.delta_dist_x = fabs(1 / ray.dir_x);
		if (ray.dir_x == 0)
			ray.delta_dist_x = INFINITY;
		ray.delta_dist_y = fabs(1 / ray.dir_y);
		if (ray.dir_y == 0)
			ray.delta_dist_y = INFINITY;
		
		ray.hit = FALSE;

		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (player.x - map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (map_x + 1.0 - player.x) * ray.delta_dist_x;
		}
		if (ray.dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (player.y - map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (map_y + 1.0 - player.y) * ray.delta_dist_y;
		}

		while (ray.hit == FALSE)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				map_x += ray.step_x;
				ray.side = 0;//EAST WEST
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				map_y += ray.step_y;
				ray.side = 1;//NORTH SOUTH
			}
			if (map.grid[map_y][map_x] != '0')
				ray.hit = TRUE;
		}

		if (ray.side == 0)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		
		ray.line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		
		ray.draw_start = (-ray.line_height) / 2 + SCREEN_HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.draw_end >= SCREEN_HEIGHT)
			ray.draw_end = SCREEN_HEIGHT - 1;

		if (ray.side == 0)//EAST WEST
			draw_vertical_line(images->wall, ray.draw_start, ray.draw_end, x, 0x0000FFFF);
		else//NORTH SOUTH
			draw_vertical_line(images->wall, ray.draw_start, ray.draw_end, x, 0x00FF00FF);
			
		x++;
	}
}
