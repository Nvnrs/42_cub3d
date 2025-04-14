/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:13:20 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 17:07:55 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"
#include "parsing.h"

t_coord	*get_position_player_in_grid(t_map *map)
{
	int		y;
	int		x;
	t_coord	*player;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (c_is_in_charset(map->grid[y][x], "NSEW"))
			{
				player = malloc(sizeof(t_coord));
				player->x = x;
				player->y = y;
				return (player);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}


void	test_direction_player(int y_player, int x_player, t_map *map, t_bool *end)
{
	if (*end == TRUE)
		return;
	if (x_player >= map->x_max
		|| y_player >= map->y_max
		|| x_player < 0
		|| y_player < 0
		|| map->grid[y_player][x_player] == 'V')
	{	
		*end = TRUE;
		return;
	}
	if (map->grid[y_player][x_player]  == '1'
	|| map->grid[y_player][x_player]  == 'X')
		return;
	map->grid[y_player][x_player] = 'X';
	// print_map(map);
	test_direction_player(y_player + 1, x_player, map, end);
	test_direction_player(y_player - 1, x_player, map, end);
	test_direction_player(y_player, x_player + 1, map, end);
	test_direction_player(y_player, x_player - 1, map, end);
}

t_bool	player_enclosed_by_wall(t_map *map)
{
	t_coord	*player_in_grid;
	t_bool	end;

	end = FALSE;
	player_in_grid = get_position_player_in_grid(map);
	if (player_in_grid == NULL)
		return (FALSE);
	print_blue();
	printf("Player X:%d\n", player_in_grid->x);
	printf("Player Y:%d\n", player_in_grid->y);
	print_reset();
	test_direction_player(player_in_grid->y, player_in_grid->x, map, &end);
	free(player_in_grid);
	if (end == TRUE)
	{
		print_error("The map need wall around\n");
		return (FALSE);
	}
	return (TRUE);
}
