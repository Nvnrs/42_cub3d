/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:05:51 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/17 10:59:34 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"


int	get_y_max(char	*desc_map)
{
	int	y_count;
	int	i;

	y_count = 0;
	i = 0;
	while (desc_map[i])
	{
		if (desc_map[i] == '\n')
			y_count++;
		if (desc_map[i + 1] == '\0')
			y_count++;
		i++;
	}
	return (y_count);
}

int	get_x_max(char	*desc_map)
{
	int	best_x;
	int	curr_x;
	int	i;

	best_x = 0;
	curr_x = 0;
	i = 0;
	while (desc_map[i])
	{
		if (desc_map[i] == '\n')
		{
			if (curr_x > best_x)
				best_x = curr_x;
			curr_x = 0;
		}
		else
			curr_x++;
		if (desc_map[i + 1] == '\0')
		{
			if (curr_x > best_x)
				best_x = curr_x;
			curr_x = 0;
		}
		i++;
	}
	return (best_x);
}


char	**init_tab_str(int row_max, int col_max, char c_fill)
{
	int	col;	
	int	row;
	char **tab;

	row = 0;
	tab = malloc((row_max + 1) * sizeof(char *));
	while (row < row_max)
	{
		col = 0;
		tab[row] = malloc((col_max + 1) * sizeof(char));
		while (col < col_max)
		{
			tab[row][col] = c_fill;
			col++;
		}
		tab[row][col] = '\0';
		row++;
	}
	tab[row] = NULL;
	return (tab);
}


t_map	*init_map(char	*desc_map)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->x_max = get_x_max(desc_map);
	map->y_max = get_y_max(desc_map);
	map->grid = init_tab_str(map->y_max, map->x_max, 'V');
	// print_tab(map->grid);
	copy_desc_map_in_grid(map, desc_map);
	print_map(map);
	return (map);
}

void	free_map(t_map *map)
{
	free_tab_str(map->grid);
	free(map);
}
