/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:38:34 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 15:26:05 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include "parsing.h"

uint32_t	**init_tab_pixels_color(mlx_texture_t *texture)
{
	uint32_t	**tab;
	uint32_t	x;
	uint32_t	y;

	tab = malloc((texture->height + 1) * sizeof(uint32_t *));
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		tab[y] = malloc(texture->width * sizeof(uint32_t));
		while (x < texture->width)
		{
			tab[y][x] = 0;
			x++;
		}
		y++;
	}
	tab[y] = NULL;
	return tab;
}

void	copy_pixels_color_in_tab(uint32_t **tab, mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;

	y = 0;
	x = 0;
	i = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			tab[y][x] = texture->pixels[i] * 16777216 + texture->pixels[i + 1]  * 65536 + texture->pixels[i + 2]  * 256 + texture->pixels[i + 3];
			i+= 4;
			x++;
		}
		y++;
	}	
}

void	free_tab_pixels(uint32_t **tab)
{
	int	y;

	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}
