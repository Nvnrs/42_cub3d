/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:47:09 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/21 09:32:21 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_loop(t_player player, t_map map, t_images *images)
{
	int		x;
	t_ray	ray;
	int		map_x;
	int		map_y;

	map_x = (int)player.x;
	map_y = (int)player.y;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		set_camera_x(&ray, x);
		set_dir(&ray, player);
		set_delta_dist(&ray);
		set_side_dist(&ray, player, map_x, map_y);
		cast(&ray, map, map_x, map_y);
		calculate_perpendicular_wall_dist(&ray);
		find_wall_hitpoint(&ray, player);
		find_texture_x(&ray, map);
		draw_wall(&ray, images, x, map);
		x++;
	}
}
