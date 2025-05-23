/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:44:34 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/21 09:45:20 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_default_player_info(t_player *player, int x, int y)
{
	player->x = (double)x + 0.5;
	player->y = (double)y + 0.5;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
}

static void	set_player_info(t_player *player, t_map *map, int x, int y)
{
	set_default_player_info(player, x, y);
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
		player->plane_y = -0.66;
	}
	else if (map->grid[y][x] == 'E')
	{
		player->dir_x = 1.0;
		player->plane_y = 0.66;
	}
}

t_player	*init_player(t_map *map)
{
	t_player	*player;
	int			y;
	int			x;

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
