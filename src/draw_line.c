/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:20:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/12 11:10:16 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"

t_bool	is_inside_screen_float(t_coord_float point, mlx_image_t *image)
{
	if (point.x >= image->width || point.x < 0)
		return (FALSE);
	if (point.y >= image->height || point.y < 0)
		return (FALSE);
	return (TRUE);
}

void	draw_line(mlx_image_t *image, t_coord c1, t_coord c2, uint32_t color)
{
	float			length;
	t_coord_float	d;
	t_coord_float	coord;
	int				i;

	if (c2.x - c1.x >= c2.y - c1.y)
		length = c2.x - c1.x;
	else
		length = c2.y - c1.y;

	d.x = (c2.x - c1.x) / length;
	d.y = (c2.y - c1.y) / length;
	coord.x = c1.x + 0.5;
	coord.y = c1.y + 0.5;
	i = 1;
	while (i < length)
	{
		if (is_inside_screen_float(coord, image))
			mlx_put_pixel(image, coord.x, coord.y, color);
		coord.x += d.x;
		coord.y += d.y;
		i++;
	}
}

void	draw_wall(t_images *images, t_ray ray)
{
	t_coord	a;
	t_coord	b;

	a.x = ray.x_on_screen;
	b.x = ray.x_on_screen;
	a.y = (SCREEN_HEIGHT - ray.wall_height) / 2;
	b.y = (SCREEN_HEIGHT - ray.wall_height) / 2 + ray.wall_height;
	if (ray.is_north_hit)//BLUE
		draw_line(images->wall, a, b, 0x0000FFFF);
	else if (ray.is_east_hit)//GREEN
		draw_line(images->wall, a, b, 0x00FF00FF);
	else if (ray.is_south_hit)//RED
		draw_line(images->wall, a, b, 0xFF0000FF);
	else if (ray.is_west_hit)//PURPLE
		draw_line(images->wall, a, b, 0x800080FF);
}
