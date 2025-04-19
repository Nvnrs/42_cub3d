/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:10:33 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/19 17:31:41 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_escape(mlx_key_data_t keydata, t_data_to_key_hook *data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_all_and_terminate(data->mlx,
			data->player, data->map, data->images);
		exit(EXIT_SUCCESS);
	}
}

t_bool	key_is_press(mlx_key_data_t keydata, keys_t key)
{
	if (keydata.key == key
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		return (TRUE);
	return (FALSE);
}

void	my_keyhook(mlx_key_data_t keydata, void *void_param)
{
	t_data_to_key_hook	*param;
	double				move_speed;
	double				rot_speed;

	rot_speed = 0.02;
	move_speed = 0.1;
	param = (t_data_to_key_hook *)void_param;
	reset_wall_image(param->images);
	handle_escape(keydata, param);
	if (key_is_press(keydata, MLX_KEY_W))
		walk_forward(param, move_speed);
	if (key_is_press(keydata, MLX_KEY_S))
		walk_backward(param, move_speed);
	if (key_is_press(keydata, MLX_KEY_D))
		strafe_right(param, move_speed);
	if (key_is_press(keydata, MLX_KEY_A))
		strafe_left(param, move_speed);
	if (key_is_press(keydata, MLX_KEY_RIGHT))
		turn_right(param, rot_speed);
	if (key_is_press(keydata, MLX_KEY_LEFT))
		turn_left(param, rot_speed);
	raycasting_loop(*param->player, *param->map, param->images);
}
