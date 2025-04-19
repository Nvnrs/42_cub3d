/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:24:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/19 15:30:29 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

void	free_all_and_terminate(mlx_t *mlx, t_player *player, t_map *map, t_images *images)
{
	free_images(mlx, images);
	free_map(map);
	free(player);
	mlx_terminate(mlx);
}

int	main(int argc, char *argv[])
{
	t_player	*player;
	t_map		*map;
	t_images	*images;
	mlx_t		*mlx;
	t_data_to_key_hook data;
	
	if (!map_is_valid(argc, argv))
		return (EXIT_FAILURE);
	map = init_map(argv[1]);
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42", true);
	images = init_images(mlx);
	draw_and_put_bg(mlx, images->bg, map);
	player = init_player(map);
	raycasting_loop(*player, *map, images);
	mlx_image_to_window(mlx, images->wall, 0, 0);
	data.player = player;
	data.map = map;
	data.images = images;
	data.mlx = mlx;
	mlx_key_hook(mlx, &my_keyhook, &data);
	mlx_loop(mlx);
	free_all_and_terminate(mlx, player, map, images);
	return (0);
}
