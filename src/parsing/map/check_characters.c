/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:15:31 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 17:55:05 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

#define MSG_ERR_CHARS "The characters authorized in map are: 01NSEW\n"

t_bool	characters_in_map_are_valid(char *desc_map)
{
	int		i;
	char	*c_for_print;

	i = 0;
	while (desc_map[i])
	{
		if (!c_is_in_charset(desc_map[i], CHARSET_MAP)
			&& desc_map[i] != ' '
			&& desc_map[i] != '\n')
		{
			c_for_print = ft_substr(desc_map, i, 1);
			print_error_details(MSG_ERR_CHARS, c_for_print);
			free(c_for_print);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
