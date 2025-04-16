/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:24:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/16 15:52:07 by pchateau         ###   ########.fr       */
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

void my_keyhook(mlx_key_data_t keydata, void* void_param)
{
	t_data_to_key_hook	*param;
	
	param = (t_data_to_key_hook *)void_param;
	reset_wall_image(param->images);
	double	move_speed;
	double	rot_speed;
	move_speed = 0.2;
	rot_speed = 0.05;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (param->map->grid[(int)param->player->y][(int)(param->player->x + param->player->dir_x * move_speed)] == '0')
			param->player->x += param->player->dir_x * move_speed;
		if (param->map->grid[(int)(param->player->y + param->player->dir_y * move_speed)][(int)param->player->x] == '0')
			param->player->y += param->player->dir_y * move_speed;
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (param->map->grid[(int)param->player->y][(int)(param->player->x - param->player->dir_x * move_speed)] == '0')
			param->player->x -= param->player->dir_x * move_speed;
		if (param->map->grid[(int)(param->player->y - param->player->dir_y * move_speed)][(int)param->player->x] == '0')
			param->player->y -= param->player->dir_y * move_speed;
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (param->map->grid[(int)param->player->y][(int)(param->player->x + param->player->plane_x * move_speed)] == '0')
			param->player->x += param->player->plane_x * move_speed;
		if (param->map->grid[(int)(param->player->y + param->player->plane_y * move_speed)][(int)param->player->x] == '0')
			param->player->y += param->player->plane_y * move_speed;
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (param->map->grid[(int)param->player->y][(int)(param->player->x - param->player->plane_x * move_speed)] == '0')
			param->player->x -= param->player->plane_x * move_speed;
		if (param->map->grid[(int)(param->player->y - param->player->plane_y * move_speed)][(int)param->player->x] == '0')
			param->player->y -= param->player->plane_y * move_speed;
	}
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = param->player->dir_x;
		old_plane_x = param->player->plane_x;
		param->player->dir_x = param->player->dir_x * cos(-rot_speed) - param->player->dir_y * sin(-rot_speed);
		param->player->dir_y = old_dir_x * sin(-rot_speed) + param->player->dir_y * cos(-rot_speed);
		param->player->plane_x = param->player->plane_x * cos(-rot_speed) - param->player->plane_y * sin(-rot_speed);
		param->player->plane_y = old_plane_x * sin(-rot_speed) + param->player->plane_y * cos(-rot_speed);
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = param->player->dir_x;
		old_plane_x = param->player->plane_x;
		param->player->dir_x = param->player->dir_x * cos(rot_speed) - param->player->dir_y * sin(rot_speed);
		param->player->dir_y = old_dir_x * sin(rot_speed) + param->player->dir_y * cos(rot_speed);
		param->player->plane_x = param->player->plane_x * cos(rot_speed) - param->player->plane_y * sin(rot_speed);
		param->player->plane_y = old_plane_x * sin(rot_speed) + param->player->plane_y * cos(rot_speed);
	}
	raycasting(*param->player, *param->map, param->images);
	// else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	// {
		
	// }
	// else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	// {
	// 	param->player->direction_angle -= 1;
	// 	if (param->player->direction_angle >= 360)	
	// 		param->player->direction_angle -= 360;
	// 	else if (param->player->direction_angle < 0)
	// 		param->player->direction_angle += 360;
	// 	draw_bg_minimap(param->images);
	// 	reset_wall_image(param->images);
	// 	raycasting(*param->player, *param->map, param->images);
	// 	draw_border_minimap(param->images);
	// 	draw_player_on_minimap(*param->player, param->images);
	// 	mlx_image_to_window(param->mlx, param->images->wall, 0, 0);
	// 	mlx_image_to_window(param->mlx, param->images->minimap,
	// 	SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	// }
	// else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	// {
	// 	param->player->direction_angle += 1;
	// 	if (param->player->direction_angle >= 360)	
	// 		param->player->direction_angle -= 360;
	// 	else if (param->player->direction_angle < 0)
	// 		param->player->direction_angle += 360;
	// 	draw_bg_minimap(param->images);
	// 	reset_wall_image(param->images);
	// 	raycasting(*param->player, *param->map, param->images);
	// 	draw_border_minimap(param->images);
	// 	draw_player_on_minimap(*param->player, param->images);
	// 	mlx_image_to_window(param->mlx, param->images->wall, 0, 0);
	// 	mlx_image_to_window(param->mlx, param->images->minimap,
	// 	SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	// }
}

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
	raycasting(player, map, images);
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
