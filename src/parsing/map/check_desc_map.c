/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_desc_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:36:13 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 15:29:29 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

t_bool	check_if_line_is_empty_also_space(char *file, int i_start)
{
	t_bool	line_is_empty;
	int		i;

	line_is_empty = TRUE;
	i = i_start;
	while (file[i] && file[i] != '\n')
	{
		if (file[i] != ' ' && file[i] != '\t')
			line_is_empty = FALSE;
		i += 1;
	}
	return (line_is_empty);
}

t_bool	description_map_contain_empty_line(char *desc_map)
{
	int	i;

	i = 0;
	while (desc_map[i])
	{
		if (check_if_line_is_empty_also_space(desc_map, i))
		{
			print_error("The description of map must not contain any empty lines.\n");
			return (TRUE);
		}
		i = skip_line(desc_map, i);
		// printf("LINE SKIP : %sEND\n", &desc_map[i]);
		// printf("LEN %d", (int)ft_strlen(desc_map));
		// printf("I: %d\n", i);
	}
	return (FALSE);
}

t_bool	linebreak_at_last_line(char *desc_map)
{
	int	last;

	last = ft_strlen(desc_map) - 1;
	if (desc_map[last] == '\n')
	{
		print_error("The description of map must not have a linebreak at end.\n");
		return (TRUE);
	}
	return (FALSE);
}

t_bool	description_of_map_is_valid(char *file)
{
	char *description_of_map;
	t_map	*map;

	description_of_map = get_description_of_map(file);
	// print_yellow();
	// printf("desc :\n%s\n", description_of_map);
	// print_reset();
	
	if (description_map_contain_empty_line(description_of_map))
		return (free(description_of_map), FALSE);
	if (linebreak_at_last_line(description_of_map))
	return (free(description_of_map), FALSE);
	if (!characters_in_map_are_valid(description_of_map))
	return (free(description_of_map), FALSE);
	if (!map_have_one_player(description_of_map))
		return (free(description_of_map), FALSE);
	map = init_map_parsing(description_of_map);
	free(description_of_map);
	if (!player_enclosed_by_wall(map))
		return (free_map_parsing(map), FALSE);
	free_map_parsing(map);
	return (TRUE);
}
