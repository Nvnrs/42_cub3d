/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:38:29 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/12 11:13:32 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"

void	draw_ray_on_minimap(t_player player, t_ray ray, t_images *images)
{
	t_coord	ray_end_point_relative_to_player;
	t_coord	player_on_minimap;

	ray_end_point_relative_to_player.x = ray.x_smallest - player.x;
	ray_end_point_relative_to_player.y = ray.y_smallest - player.y;
	player_on_minimap.x	= images->minimap->width / 2;
	player_on_minimap.y	= images->minimap->height / 2;
	// draw_line(images->minimap, player_on_minimap, ray_end_point_relative_to_player, 0xFFFF00FF);
	if (ray.is_north_hit)//BLUE
		draw_line(images->minimap, player_on_minimap, ray_end_point_relative_to_player, 0x0000FFFF);
	else if (ray.is_east_hit)//GREEN
		draw_line(images->minimap, player_on_minimap, ray_end_point_relative_to_player, 0x00FF00FF);
	else if (ray.is_south_hit)//RED
		draw_line(images->minimap, player_on_minimap, ray_end_point_relative_to_player, 0xFF0000FF);
	else if (ray.is_west_hit)//PURPLE
		draw_line(images->minimap, player_on_minimap, ray_end_point_relative_to_player, 0x800080FF);
}

void	draw_player_on_minimap(t_player player, t_images *images)
{
	//center point
	mlx_put_pixel(images->minimap, images->minimap->width / 2, images->minimap->height / 2, 0x000000FF);
}

void	draw_bg_minimap(t_images *images)
{
	t_coord	start;
	t_coord	end;

	start.x = 0;
	start.y = 0;
	end.x = images->minimap->width;
	end.y = images->minimap->height;
	fill_zone(start, end, images->minimap, 0x80808088);
}

void	draw_border_minimap(t_images *images)
{
	int	x;
	int	y;

	y = 0;
	while (y < images->minimap->height)
	{
		x = 0;
		if (y == 0 || y == images->minimap->height - 1)
		{
			while (x < images->minimap->width)
			{
				mlx_put_pixel(images->minimap, x, y, 0x00000099);
				x++;
			}
		}
		while (x < images->minimap->width && y != 0 && y != images->minimap->height - 1)
		{
			if (x == 0 || x == images->minimap->width - 1)
				mlx_put_pixel(images->minimap, x, y, 0x00000099);
			x++;
		}
		y++;
	}
}
