/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:09 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 11:04:13 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"
#include "parsing.h"

t_bool	map_have_one_player(char *desc_map)
{
	int		i;
	char	ref_player;
	char	*c_for_print;
	t_bool	have_player;

	i = 0;
	have_player = FALSE;
	while (desc_map[i])
	{
		if (c_is_in_charset(desc_map[i], "NSEW"))
		{
			have_player = TRUE;
			ref_player = desc_map[i];
			// printf("REF find :%c\n", ref_player);
			i++;
			break;
		}
		i++;
	}
	if (have_player == FALSE)
		return print_error("The description of map must be contain a PLAYER\n");
	while (desc_map[i])
	{
		if (c_is_in_charset(desc_map[i], "NSEW"))
		{
			c_for_print = ft_substr(desc_map, i, 1);
			print_error_details("The player can only be defined once\n", c_for_print);
			free(c_for_print);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

