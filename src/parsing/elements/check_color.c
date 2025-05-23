/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:08:59 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/23 11:54:49 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

t_bool	is_color(char *key)
{
	if (ft_strcmp(key, "F") == 0
		|| ft_strcmp(key, "C") == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	channel_color_is_in_range(char *channel)
{
	int	channel_int;

	channel_int = ft_atoi(channel);
	if (channel_int > 255 || channel_int < 0)
		return (FALSE);
	return (TRUE);
}

t_bool	color_is_valid_for_split(char *color)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (FALSE);
		while (color[i] && ft_isdigit(color[i]))
			i++;
		if (color[i] == ',')
			comma_count++;
		else if (comma_count == 2 && color[i] == '\0')
			return (TRUE);
		else
			return (FALSE);
		i++;
	}
	return (FALSE);
}

t_bool	length_color_is_valid(char *channel)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (channel[i] == '0')
		i++;
	while (channel[i])
	{
		length++;
		i++;
	}
	if (length > 3)
		return (FALSE);
	return (TRUE);
}

t_bool	color_is_rgb(char *color)
{
	char	**channels;
	t_bool	is_valid;
	int		i;

	i = 0;
	is_valid = TRUE;
	if (!color_is_valid_for_split(color))
		return (FALSE);
	channels = ft_split(color, ',');
	if (len_tab(channels) != 3)
		return (free_tab_str(channels), FALSE);
	while (channels[i])
	{
		if (!length_color_is_valid(channels[i])
			||!channel_color_is_in_range(channels[i]))
			return (free_tab_str(channels), FALSE);
		i++;
	}
	free_tab_str(channels);
	return (TRUE);
}
