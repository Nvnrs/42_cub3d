/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:41:09 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 15:10:17 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

void	print_pixels_texture(mlx_texture_t *texture)
{
	uint32_t	max_i;
	uint32_t	i;

	max_i = texture->width * texture->height * texture->bytes_per_pixel;
	i = 0;
	while (i < max_i)
	{
		if (i % 4 == 0)
		{
			print_purple();
			printf("\n__New Pixel__\n");
		}
		print_reset();
		printf("%d ", texture->pixels[i]);
		i++;
	}
}


void	print_tab_pixels(uint32_t **tab, mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			printf("%u", tab[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}	
}
