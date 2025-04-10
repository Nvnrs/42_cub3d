/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:33:22 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/10 11:33:44 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"

/**
 * ATTENTION A PRENDRE EN COMPTE LA DIRECTION DU JOUEUR POUR LES DEPLACEMENTS.
 * POUR LES TESTS JE N'Y FAIS PAS ATTENTION.
 */
void my_keyhook(mlx_key_data_t keydata, void* void_param)
{
	t_data_to_key_hook	*param;
	
	param = (t_data_to_key_hook *)void_param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		param->player->x += 1;
		draw_bg_minimap(param->images);
		reset_wall_image(param->images);
		raycasting(*param->player, *param->map, param->images);
		draw_border_minimap(param->images);
		draw_player_on_minimap(*param->player, param->images);
		mlx_image_to_window(param->mlx, param->images->wall, 0, 0);
		mlx_image_to_window(param->mlx, param->images->minimap,
		SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		param->player->x -= 1;
		draw_bg_minimap(param->images);
		reset_wall_image(param->images);
		raycasting(*param->player, *param->map, param->images);
		draw_border_minimap(param->images);
		draw_player_on_minimap(*param->player, param->images);
		mlx_image_to_window(param->mlx, param->images->wall, 0, 0);
		mlx_image_to_window(param->mlx, param->images->minimap,
		SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		param->player->y += 1;
		draw_bg_minimap(param->images);
		reset_wall_image(param->images);
		raycasting(*param->player, *param->map, param->images);
		draw_border_minimap(param->images);
		draw_player_on_minimap(*param->player, param->images);
		mlx_image_to_window(param->mlx, param->images->wall, 0, 0);
		mlx_image_to_window(param->mlx, param->images->minimap,
		SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		param->player->y -= 1;
		draw_bg_minimap(param->images);
		reset_wall_image(param->images);
		raycasting(*param->player, *param->map, param->images);
		draw_border_minimap(param->images);
		draw_player_on_minimap(*param->player, param->images);
		mlx_image_to_window(param->mlx, param->images->wall, 0, 0);
		mlx_image_to_window(param->mlx, param->images->minimap,
		SCREEN_WIDTH - SCREEN_HEIGHT / 4, 0);
	}
}
