/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:24:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/09 11:49:40 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "cub3d.h"

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
			if (x == 5 && y == y_max - 3)
				map[y][x] = 'P';
			x++;
		}
		y++;
	}
	return (map);
}

void	print_map(char **map, int x_max, int y_max)
{
	int	x;
	int	y;

	y = 0;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			printf("%c ", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	
}

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

// void	free_images()
// {
	
// }

void	fill_zone(t_coord start, t_coord end, mlx_image_t *image, uint32_t color)
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

void	draw_and_put_bg(mlx_t *mlx, mlx_image_t *bg)
{
	t_coord	sky_start;
	t_coord	sky_end;
	t_coord	ground_start;
	t_coord	ground_end;

	// draw sky
	sky_start.x = 0;
	sky_start.y = 0;
	sky_end.x = SCREEN_WIDTH;
	sky_end.y = SCREEN_HEIGHT / 2;
	fill_zone(sky_start, sky_end, bg, 0xFFFFFFFF);
	ground_start.x = 0;
	ground_start.y = SCREEN_HEIGHT / 2;
	ground_end.x = SCREEN_WIDTH;
	ground_end.y = SCREEN_HEIGHT;
	fill_zone(sky_start, sky_end, bg, 0xFFFFFFAA);
	mlx_image_to_window(mlx, bg, 0, 0);
}

int	main(void)
{
	t_player	player;
	t_map		map;
	t_images	*images;
	mlx_t		*mlx;
	
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", true);
	images = init_images(mlx);
	draw_and_put_bg(mlx, images->bg);
	map.grid = map_test(10, 10);
	map.x_max = 10;
	map.y_max = 10;
	player.x = 2 * CUBE_SIZE - CUBE_SIZE / 2;
	player.y = (map.y_max - 5) * CUBE_SIZE - CUBE_SIZE / 2;
	player.direction_angle = 270;
	print_map(map.grid, 10, 10);
	draw_bg_minimap(images);
	raycasting(player, map, images);
	draw_border_minimap(images);
	draw_player_on_minimap(player, images);
	mlx_image_to_window(mlx, images->wall, 0, 0);
	mlx_image_to_window(mlx, images->minimap,
		SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
