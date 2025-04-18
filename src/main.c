/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:24:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/18 10:37:04 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

char	**map_test(int x_max, int y_max)
{
	char **map;
	int x;
	int y;

	map = malloc((y_max) * sizeof(char*));
	y = 0;
	//map[x][y]
	while (y < y_max)
	{
		x = 0;
		map[y] = malloc(x_max * sizeof(char));
		while (x < x_max)
		{
			if (x == 0 || x == x_max - 1 || y == 0 || y == y_max - 1)
				map[y][x] = '1';
			else
				map[y][x] = '0';
			// if (x == 5 && y == y_max - 3)
				// map[y][x] = 'P';
			x++;
		}
		y++;
	}
	return (map);
}

// void	print_map(char **map, int x_max, int y_max)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < y_max)
// 	{
// 		x = 0;
// 		while (x < x_max)
// 		{
// 			printf("%c ", map[y][x]);
// 			x++;
// 		}
// 		printf("\n");
// 		y++;
// 	}
	
// }

// IMAGES
t_images	*init_images(mlx_t *mlx)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	images->bg = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	images->wall = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	images->minimap = mlx_new_image(mlx, SCREEN_HEIGHT / 4, SCREEN_HEIGHT / 4);
	return (images);
}

// int	main(int argc, char **argv)
// {
// 	if (!map_is_valid(argc, argv))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

void	load_texture_in_map(t_map *map, t_key_val **map_elements)
{
	int	i;

	i = 0;
	while (map_elements[i])
	{
		if (ft_strcmp(map_elements[i]->key, "NO") == 0)
			map->textures.north = mlx_load_png(map_elements[i]->val);
		else if (ft_strcmp(map_elements[i]->key, "SO") == 0)
			map->textures.south = mlx_load_png(map_elements[i]->val);
		else if (ft_strcmp(map_elements[i]->key, "WE") == 0)
			map->textures.west = mlx_load_png(map_elements[i]->val);
		else if (ft_strcmp(map_elements[i]->key, "EA") == 0)
			map->textures.east = mlx_load_png(map_elements[i]->val);
		i++;
	}
}

/**
 * Takes a string like: 255,0,255.
 * Convert it like: 0xFF00FFFF but in decimal -> 4278255615.
 */
unsigned int	convert_rgb_to_rgba(char *rgb)
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

void	init_color_in_map(t_map *map, t_key_val **map_elements)
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

t_map	*init_map2(t_key_val **map_elements, char *desc_map)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->x_max = get_x_max(desc_map);
	map->y_max = get_y_max(desc_map);
	map->grid = init_tab_str(map->y_max, map->x_max, 'V');
	// print_tab(map->grid);
	copy_desc_map_in_grid(map, desc_map);//peut etre strdup desc_map
	// print_map(map);
	load_texture_in_map(map, map_elements);
	init_color_in_map(map, map_elements);
	return (map);
}

t_map	*extract_map_info(char *filename)
{
	char *file;
	char *desc_map;
	t_key_val **map_elements;
	t_map	*map;
	
	file = get_file(filename);
	map_elements = get_elements(file);
	desc_map = get_description_of_map(file);
	map = init_map2(map_elements, desc_map);
	free(file);
	free_tab_key_val(map_elements);
	return (map);
}

int	main(int argc, char *argv[])
{
	t_player	player;
	t_map		*map;
	t_images	*images;
	mlx_t		*mlx;
	t_data_to_key_hook data;
	
	
	if (!map_is_valid(argc, argv))
		return (EXIT_FAILURE);
	map = extract_map_info(argv[1]);
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", true);
	images = init_images(mlx);
	printf("Floor color: %u\n", map->colors.floor);
	printf("Ceiling color: %u\n", map->colors.ceiling);
	draw_and_put_bg(mlx, images->bg, map);
	// map.grid = map_test(10, 10);
	// map.x_max = 10;
	// map.y_max = 10;
	player.x = 1.5;
	player.y = 2.5;
	player.dir_x = -1.0;
	player.dir_y = 0.0;
	player.plane_x = 0.0;
	player.plane_y = 0.66;
	// print_map(map.grid, 10, 10);
	// draw_bg_minimap(images);
	raycasting_loop(player, *map, images);
	// draw_border_minimap(images);
	// draw_player_on_minimap(player, images);
	mlx_image_to_window(mlx, images->wall, 0, 0);
	// mlx_image_to_window(mlx, images->minimap,
		// SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	data.player = &player;
	data.map = map;
	data.images = images;
	data.mlx = mlx;
	mlx_key_hook(mlx, &my_keyhook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
