/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_in_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:17:51 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/21 14:59:42 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

/**
 * Takes a string like: 255,0,255.
 * Convert it like: 0xFF00FFFF but in decimal -> 4278255615.
 */
static unsigned int	convert_rgb_to_rgba(char *rgb, unsigned int a)
{
	char				**rgb_split;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;

	rgb_split = ft_split(rgb, ',');
	r = ft_atoi(rgb_split[0]);
	g = ft_atoi(rgb_split[1]);
	b = ft_atoi(rgb_split[2]);
	free_tab_str(rgb_split);
	return (r * 16777216 + g * 65536 + b * 256 + a);
}

void	init_floor_and_ceiling_in_map(t_map *map, t_key_val **map_elements)
{
	int				i;
	char			*floor_str;
	char			*ceiling_str;
	unsigned int	ceiling_ui;

	i = 0;
	while (map_elements[i])
	{
		if (ft_strcmp(map_elements[i]->key, "F") == 0)
			floor_str = map_elements[i]->val;
		else if (ft_strcmp(map_elements[i]->key, "C") == 0)
			ceiling_str = map_elements[i]->val;
		i++;
	}
	ceiling_ui = convert_rgb_to_rgba(ceiling_str, 255);
	map->colors.floor = convert_rgb_to_rgba(floor_str, 255);
	map->colors.ceiling = ceiling_ui;
	if (map->colors.floor == ceiling_ui)
		map->colors.ceiling = convert_rgb_to_rgba(ceiling_str, 127);
}

static void	extract_info_from_texture(t_texture *texture_in_map,
	mlx_texture_t *texture)
{
	texture_in_map->width = texture->width;
	texture_in_map->height = texture->height;
	texture_in_map->bytes_per_pixel = texture->bytes_per_pixel;
	texture_in_map->pixels = init_tab_pixels_color(texture);
	copy_pixels_color_in_tab(texture_in_map->pixels, texture);
	mlx_delete_texture(texture);
}

void	init_textures_in_map(t_map *map, t_key_val **map_elements)
{
	int				i;
	mlx_texture_t	*texture;

	i = 0;
	while (map_elements[i])
	{
		if (ft_strcmp(map_elements[i]->key, "NO") == 0
			|| ft_strcmp(map_elements[i]->key, "SO") == 0
			|| ft_strcmp(map_elements[i]->key, "WE") == 0
			|| ft_strcmp(map_elements[i]->key, "EA") == 0)
			texture = mlx_load_png(map_elements[i]->val);
		if (ft_strcmp(map_elements[i]->key, "NO") == 0)
			extract_info_from_texture(&map->textures.north, texture);
		else if (ft_strcmp(map_elements[i]->key, "SO") == 0)
			extract_info_from_texture(&map->textures.south, texture);
		else if (ft_strcmp(map_elements[i]->key, "WE") == 0)
			extract_info_from_texture(&map->textures.west, texture);
		else if (ft_strcmp(map_elements[i]->key, "EA") == 0)
			extract_info_from_texture(&map->textures.east, texture);
		i++;
	}
}
