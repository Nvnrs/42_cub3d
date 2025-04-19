/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_desc_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:19:43 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 11:26:18 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

t_bool	check_if_line_is_empty(char *file, int i_start)
{
	t_bool	line_is_empty;
	int		i;

	line_is_empty = TRUE;
	i = i_start;
	while (file[i] && file[i] != '\n')
	{
		line_is_empty = FALSE;
		i += 1;
	}
	return (line_is_empty);
}

int	skip_line(char *file, int i_start)
{
	int i;

	i = i_start;
	while (file[i] && file[i] != '\n')
		i += 1;
	if (file[i] == '\n')
		i += 1;
	return (i);
}


int	skip_next_line_after_empty(char *file, int i_start)
{
	int	i;

	i = i_start;
	while (check_if_line_is_empty(file, i))
		i = skip_line(file, i);
	i = skip_line(file, i);
	return (i);
}
char	*get_description_of_map(char *file)
{
	int			i_file;
	int			nb_line_skip;
	char		*description_of_map;

	i_file = 0;
	nb_line_skip = 0;
	// skip line
	// printf("BEFORE :%s\n", file);
	while (nb_line_skip < NB_ELEMENTS)
	{
		i_file = skip_next_line_after_empty(file, i_file);
		nb_line_skip++;
	}
	while (check_if_line_is_empty(file, i_file))
		i_file = skip_line(file, i_file);
	
	description_of_map = ft_strdup(&file[i_file]);
	// printf("AFTER :%s", description_of_map);
	return (description_of_map);
}

void	copy_desc_map_in_grid(t_map *map, char *desc_map)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	x = 0;
	while (desc_map[i])
	{
		if (desc_map[i] == '\n')
		{	
			x = 0;
			y++;
		}
		else
		{
			if (desc_map[i] != ' ')
				map->grid[y][x] = desc_map[i];
			x++;
		}
		i++;
	}
	print_reset();
}
