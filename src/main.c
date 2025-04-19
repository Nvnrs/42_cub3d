/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:24:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/19 13:24:06 by pchateau         ###   ########.fr       */
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

void	init_floor_and_ceiling_in_map(t_map *map, t_key_val **map_elements)
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

uint32_t	**init_tab_pixels_color(mlx_texture_t *texture)
{
	uint32_t	**tab;
	int			x;
	int			y;

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
	int	x;
	int	y;
	int	i;

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

// void	format_textures_pixels(t_map *map)
// {
// 	map->textures.north_pixels = init_tab_pixels_color(map->textures.north);
// 	copy_pixels_color_in_tab(map->textures.north_pixels, map->textures.north);
// 	map->textures.south_pixels = init_tab_pixels_color(map->textures.south);
// 	copy_pixels_color_in_tab(map->textures.south_pixels, map->textures.south);
// 	map->textures.east_pixels = init_tab_pixels_color(map->textures.east);
// 	copy_pixels_color_in_tab(map->textures.east_pixels, map->textures.east);
// 	map->textures.west_pixels = init_tab_pixels_color(map->textures.west);
// 	copy_pixels_color_in_tab(map->textures.west_pixels, map->textures.west);
// }

void	extract_info_from_texture(t_texture *texture_in_map, mlx_texture_t *texture)
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
	init_textures_in_map(map, map_elements);
	// format_textures_pixels(map);
	init_floor_and_ceiling_in_map(map, map_elements);
	return (map);
}

void	set_player_info(t_player *player, t_map *map, int x, int y)
{
	player->x = (double)x;
	player->y = (double)y;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	if (map->grid[y][x] == 'N')
	{
		player->dir_y = -1.0;
		player->plane_x = 0.66;
	}
	else if (map->grid[y][x] == 'S')
	{
		player->dir_y = 1.0;
		player->plane_x = -0.66;
	}
	else if (map->grid[y][x] == 'W')
	{
		player->dir_x = -1.0;
		player->plane_y = 0.66;
	}
	else if (map->grid[y][x] == 'E')
	{
		player->dir_x = 1.0;
		player->plane_y = -0.66;
	}
}

t_player	*init_player(t_map *map)
{
	t_player	*player;
	int	y;
	int	x;
	
	player = malloc(sizeof(t_player));
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (c_is_in_charset(map->grid[y][x], "NSEW"))
			{
				set_player_info(player, map, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
	return (player);
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

void	print_pixels_texture(mlx_texture_t *texture)
{
	uint32_t	max_i;
	uint32_t	i;

	max_i = texture->width * texture->height * texture->bytes_per_pixel;
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

void	put_pixel_texture(int x, int y, mlx_texture_t *texture, t_data_to_key_hook *data)
{
	uint32_t	color;
	static	uint32_t i;
	uint8_t		offset;

	offset = x * texture->bytes_per_pixel + y * texture->height;
	color = (texture->pixels[offset] * 16777216 + texture->pixels[offset + 1]  * 65536 + texture->pixels[offset + 2]  * 256 + texture->pixels[offset + 3]);
	mlx_put_pixel(data->images->bg, x, y, color);
}

void	put_pixels_texture(mlx_texture_t *texture, uint32_t **tab_pixels, t_data_to_key_hook *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{	
			// mlx_put_pixel(x, y, color);
			// put_pixel_texture(x, y, texture, data);
			mlx_put_pixel(data->images->bg, x, y, tab_pixels[y][x]);
			x++;
		}
		// put_pixel_texture(x, y, texture, data);
		// y++;
		y++;
	}
}

void	print_tab_pixels(uint32_t **tab, mlx_texture_t *texture)
{
	int	x;
	int	y;

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


void	test_texture(t_data_to_key_hook *data)
{
	mlx_texture_t *texture;
	uint32_t	**tab_pixels;
	t_coord	start;
	t_coord	end;
	int x;

	start.x = 0;
	start.y = 0;
	end.x = SCREEN_WIDTH;
	end.y = SCREEN_HEIGHT;
	texture = mlx_load_png("./error.png");
	tab_pixels = init_tab_pixels_color(texture);
	copy_pixels_color_in_tab(tab_pixels, texture);
	// printf("Texture pixels :%d\n", texture->pixels[64]);
	// print_pixels_texture(texture);
	// while (x < texture->width)
	// {
	// 	put_pixels_texture(x, texture, data);
	// 	x++;
	// }
	put_pixels_texture(texture, tab_pixels, data);
	// put_pixels_texture(2, texture, data);
	// put_pixels_texture(3, texture, data);
	// put_pixels_texture(4, texture, data);
	// put_pixels_texture(5, texture, data);
	// put_pixels_texture(6, texture, data);
}


// int	main()
// {
// 	uint32_t **tab_pixels;
// 	mlx_texture_t *texture;

// 	texture = mlx_load_png("./texture.png");
// 	tab_pixels = init_tab_pixels_color(texture);
// 	copy_pixels_color_in_tab(tab_pixels, texture);
// 	print_tab_pixels(tab_pixels, texture);
// 	mlx_delete_texture(texture);
// 	free_tab_pixels(tab_pixels);
// }

int	main(int argc, char *argv[])
{
	// t_player	*player;
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
	// player = init_player(map);
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
	// test_texture(&data);
	mlx_key_hook(mlx, &my_keyhook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
