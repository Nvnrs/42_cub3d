/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:02:11 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/19 17:35:14 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_data_to_key_hook *param,
	double move_speed, double vec_x, double vec_y)
{
	if (param->map->grid[(int)param->player->y]
		[(int)(param->player->x + vec_x * move_speed)] != '1')
		param->player->x += vec_x * move_speed;
	if (param->map->grid[(int)(param->player->y + vec_y * move_speed)]
		[(int)param->player->x] != '1')
		param->player->y += vec_y * move_speed;
}

void	walk_forward(t_data_to_key_hook *param, double move_speed)
{
	move(param, move_speed, param->player->dir_x, param->player->dir_y);
}

void	walk_backward(t_data_to_key_hook *param, double move_speed)
{
	move(param, -move_speed, param->player->dir_x, param->player->dir_y);
}

void	strafe_right(t_data_to_key_hook *param, double move_speed)
{
	move(param, move_speed, param->player->plane_x, param->player->plane_y);
}

void	strafe_left(t_data_to_key_hook *param, double move_speed)
{
	move(param, -move_speed, param->player->plane_x, param->player->plane_y);
}
