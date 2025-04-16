/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:09:33 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/16 14:40:28 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

t_bool	is_texture(char *key)
{
	if (ft_strcmp(key, "NO") == 0
		|| ft_strcmp(key, "SO") == 0
		|| ft_strcmp(key, "WE") == 0
		|| ft_strcmp(key, "EA") == 0)
		return (TRUE);
	return (FALSE);
}


t_bool	try_to_load_texture(char *val)
{
	mlx_texture_t 	*texture;
	
	texture = mlx_load_png(val);
	if (!texture)
		return (FALSE);
	mlx_delete_texture(texture);
	return (TRUE);
}

