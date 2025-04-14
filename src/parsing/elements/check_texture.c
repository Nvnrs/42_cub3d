/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:09:33 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 10:42:37 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"
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

