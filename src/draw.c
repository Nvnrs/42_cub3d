/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:20:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/21 09:29:04 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_zone(t_coord start, t_coord end, mlx_image_t *image,
			uint32_t color)
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

void	draw_and_put_bg(mlx_t *mlx, mlx_image_t *bg, t_map *map)
{
	t_coord	sky_start;
	t_coord	sky_end;
	t_coord	ground_start;
	t_coord	ground_end;

	sky_start.x = 0;
	sky_start.y = 0;
	sky_end.x = SCREEN_WIDTH;
	sky_end.y = SCREEN_HEIGHT / 2;
	fill_zone(sky_start, sky_end, bg, map->colors.ceiling);
	ground_start.x = 0;
	ground_start.y = SCREEN_HEIGHT / 2;
	ground_end.x = SCREEN_WIDTH;
	ground_end.y = SCREEN_HEIGHT;
	fill_zone(ground_start, ground_end, bg, map->colors.floor);
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

void	draw_vertical_line_texture(mlx_image_t *image, t_ray *ray, int x,
			t_texture texture)
{
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	uint32_t	color;

	step = 1.0 * texture.height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		if (tex_pos < 0)
			tex_y = 0;
		else if (tex_pos > texture.height - 1)
			tex_y = texture.height - 1;
		else
			tex_y = tex_pos;
		tex_pos += step;
		color = texture.pixels[tex_y][ray->tex_x];
		mlx_put_pixel(image, x, y, color);
		y++;
	}
}
