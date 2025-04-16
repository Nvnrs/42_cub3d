/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:43:16 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/16 14:40:30 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

t_key_val	**get_elements(char *file)
{
	int			i;
	char		**lines;
	char		**split;
	t_key_val	**elements;

	i = 0;
	lines = ft_split(file, '\n');
	elements = NULL;
	elements = malloc((NB_ELEMENTS + 1) * sizeof(t_key_val *));
	fill_tab_null((void **)elements, NB_ELEMENTS + 1);
	while (i < NB_ELEMENTS)
	{
		split = ft_split(lines[i], ' ');
		if (len_tab(split) != 2)
		{
			free_tab_str(lines);
			free_tab_str(split);
			free_tab_key_val(elements);
			return (NULL);
		}
		elements[i] = init_key_val(split[0], split[1]);
		free_tab_str(split);
		i++;
	}
	elements[i] = NULL;
	free_tab_str(lines);
	return (elements);
}



