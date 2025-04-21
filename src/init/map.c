/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:52:02 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/21 11:11:35 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

t_map	*init_map(char *filename)
{
	char		*file;
	char		*desc_map;
	t_key_val	**map_elements;
	t_map		*map;

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
