/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:10:33 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/17 09:54:03 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_keyhook(mlx_key_data_t keydata, void* void_param)
{
	t_data_to_key_hook	*param;
	double	move_speed;
	double	rot_speed;
	
	rot_speed = 0.05;
	move_speed = 0.2;
	param = (t_data_to_key_hook *)void_param;
	reset_wall_image(param->images);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		walk_forward(param, move_speed);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		walk_backward(param, move_speed);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		strafe_right(param, move_speed);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		strafe_left(param, move_speed);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		turn_right(param, rot_speed);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		turn_left(param, rot_speed);
	raycasting_loop(*param->player, *param->map, param->images);
}
