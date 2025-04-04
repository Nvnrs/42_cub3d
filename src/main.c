/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:24:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/04 11:32:59 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

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
			if (x == 5 && y == 3)
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

int	main(void)
{
	t_player	player;
	t_map		map;
	
	map.grid = map_test(10, 10);
	map.x_max = 10;
	map.y_max = 10;
	player.x = 5 * CUBE_SIZE - CUBE_SIZE / 2;
	player.y = 3 * CUBE_SIZE - CUBE_SIZE / 2;
	player.direction_angle = 90;
	print_map(map.grid, 10, 10);
	raycasting(player, map);
	return (0);
}
