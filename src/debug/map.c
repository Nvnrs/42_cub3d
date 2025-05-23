/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:08:32 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 17:10:39 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

static void	print_infos_map(t_map *map)
{
	print_purple();
	printf("____MAP____\n");
	print_reset();
	printf("y_max : %d\n", map->y_max);
	printf("x_max : %d\n", map->x_max);
}

void	print_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	print_infos_map(map);
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '0')
				print_black();
			else if (map->grid[y][x] == '1')
				print_blue();
			else if (map->grid[y][x] == 'V')
				print_yellow();
			else
				print_red();
			printf("%c", map->grid[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	print_reset();
}
