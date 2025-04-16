/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:20:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/16 14:46:36 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_zone(t_coord start, t_coord end, mlx_image_t *image, uint32_t color)
{
	int	y;
	int	x;

	x = start.x;
	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}	
}

void	draw_and_put_bg(mlx_t *mlx, mlx_image_t *bg)
{
	t_coord	sky_start;
	t_coord	sky_end;
	t_coord	ground_start;
	t_coord	ground_end;

	// draw sky
	sky_start.x = 0;
	sky_start.y = 0;
	sky_end.x = SCREEN_WIDTH;
	sky_end.y = SCREEN_HEIGHT / 2;
	fill_zone(sky_start, sky_end, bg, 0xFFFFFFFF);
	ground_start.x = 0;
	ground_start.y = SCREEN_HEIGHT / 2;
	ground_end.x = SCREEN_WIDTH;
	ground_end.y = SCREEN_HEIGHT;
	fill_zone(sky_start, sky_end, bg, 0xFFFFFFAA);
	mlx_image_to_window(mlx, bg, 0, 0);
}

void	reset_wall_image(t_images *images)
{
	t_coord	start;
	t_coord	end;

	start.x = 0;
	start.y = 0;
	end.x = images->wall->width;
	end.y = images->wall->height;
	fill_zone(start, end, images->wall, 0x00000000);
}

void	draw_vertical_line(mlx_image_t *image, int draw_start, int draw_end, int x, uint32_t color)
{
	int y;

	y = draw_start;
	while (y <= draw_end)
	{
		mlx_put_pixel(image, x, y, color);
		y++;
	}
}
