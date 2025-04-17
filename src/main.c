/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:24:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/17 09:54:12 by pchateau         ###   ########.fr       */
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

int	main(void)
{
	t_player	player;
	t_map		map;
	t_images	*images;
	mlx_t		*mlx;
	t_data_to_key_hook data;
	
	
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", true);
	images = init_images(mlx);
	draw_and_put_bg(mlx, images->bg);
	map.grid = map_test(10, 10);
	map.x_max = 10;
	map.y_max = 10;
	player.x = 6.0;
	player.y = 3.5;
	player.dir_x = -1.0;
	player.dir_y = 0.0;
	player.plane_x = 0.0;
	player.plane_y = 0.66;
	// print_map(map.grid, 10, 10);
	// draw_bg_minimap(images);
	raycasting_loop(player, map, images);
	// draw_border_minimap(images);
	// draw_player_on_minimap(player, images);
	mlx_image_to_window(mlx, images->wall, 0, 0);
	// mlx_image_to_window(mlx, images->minimap,
		// SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	data.player = &player;
	data.map = &map;
	data.images = images;
	data.mlx = mlx;
	mlx_key_hook(mlx, &my_keyhook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
