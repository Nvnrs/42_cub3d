/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:52:02 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 15:31:11 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"


/**
 * Takes a string like: 255,0,255.
 * Convert it like: 0xFF00FFFF but in decimal -> 4278255615.
 */
static unsigned int	convert_rgb_to_rgba(char *rgb)
{
	char	**rgb_split;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
	
	rgb_split = ft_split(rgb, ',');
	r = ft_atoi(rgb_split[0]);
	g = ft_atoi(rgb_split[1]);
	b = ft_atoi(rgb_split[2]);
	free_tab_str(rgb_split);
	return (r * 16777216 + g * 65536 + b * 256 + 255);
}

static void	init_floor_and_ceiling_in_map(t_map *map, t_key_val **map_elements)
{
	int	i;

	i = 0;
	while (map_elements[i])
	{
		if (ft_strcmp(map_elements[i]->key, "F") == 0)
			map->colors.floor = convert_rgb_to_rgba(map_elements[i]->val);
		else if (ft_strcmp(map_elements[i]->key, "C") == 0)
			map->colors.ceiling = convert_rgb_to_rgba(map_elements[i]->val);
		i++;
	}
}

static void	extract_info_from_texture(t_texture *texture_in_map, mlx_texture_t *texture)
{
	texture_in_map->width = texture->width;
	texture_in_map->height = texture->height;
	texture_in_map->bytes_per_pixel = texture->bytes_per_pixel;
	texture_in_map->pixels = init_tab_pixels_color(texture);
	copy_pixels_color_in_tab(texture_in_map->pixels, texture);
	mlx_delete_texture(texture);
} 

static void	init_textures_in_map(t_map *map, t_key_val **map_elements)
{
	int	i;
	mlx_texture_t	*texture;

	i = 0;
	while (map_elements[i])
	{
		if (ft_strcmp(map_elements[i]->key, "NO") == 0
			|| ft_strcmp(map_elements[i]->key, "SO") == 0
			||	ft_strcmp(map_elements[i]->key, "WE") == 0
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
			// map->textures.north = mlx_load_png(map_elements[i]->val);
			// map->textures.south = mlx_load_png(map_elements[i]->val);
			// map->textures.west = mlx_load_png(map_elements[i]->val);
			// map->textures.east = mlx_load_png(map_elements[i]->val);
		i++;
	}
}

t_map	*init_map(char *filename)
{
	char *file;
	char *desc_map;
	t_key_val **map_elements;
	t_map	*map;
	
	file = get_file(filename);
	map_elements = get_elements(file);
	desc_map = get_description_of_map(file);
	map = malloc(sizeof(t_map));
	map->x_max = get_x_max(desc_map);
	map->y_max = get_y_max(desc_map);
	map->grid = init_tab_str(map->y_max, map->x_max, 'V');
	copy_desc_map_in_grid(map, desc_map);
	init_textures_in_map(map, map_elements);
	init_floor_and_ceiling_in_map(map, map_elements);
	free(desc_map);
	free(file);
	free_tab_key_val(map_elements);
	return (map);
}


void	free_map(t_map *map)
{
	free_tab_pixels(map->textures.north.pixels);
	free_tab_pixels(map->textures.south.pixels);
	free_tab_pixels(map->textures.east.pixels);
	free_tab_pixels(map->textures.west.pixels);
	free_tab_str(map->grid);
	free(map);
}
