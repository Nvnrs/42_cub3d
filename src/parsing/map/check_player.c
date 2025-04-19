/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:09 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 18:04:36 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

#define MSG_ERR_DUP_PLAYER "The player can only be defined once\n"
#define MSG_ERR_EMPTY_PLAYER "The description of map must be contain a PLAYER\n"

t_bool	player_is_not_duplicate(char *desc_map, int i)
{
	char	*c_for_print;

	while (desc_map[i])
	{
		if (c_is_in_charset(desc_map[i], "NSEW"))
		{
			c_for_print = ft_substr(desc_map, i, 1);
			print_error_details(MSG_ERR_DUP_PLAYER, c_for_print);
			free(c_for_print);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

t_bool	map_have_one_player(char *desc_map)
{
	int		i;
	char	ref_player;
	t_bool	have_player;

	i = 0;
	have_player = FALSE;
	while (desc_map[i])
	{
		if (c_is_in_charset(desc_map[i], "NSEW"))
		{
			have_player = TRUE;
			ref_player = desc_map[i];
			i++;
			break ;
		}
		i++;
	}
	if (have_player == FALSE)
		return (print_error(MSG_ERR_EMPTY_PLAYER));
	if (!player_is_not_duplicate(desc_map, i))
		return (FALSE);
	return (TRUE);
}
