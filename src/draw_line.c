/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:20:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/16 14:38:12 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
