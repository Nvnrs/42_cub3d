/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:02:11 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/16 16:06:34 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walk_forward(t_data_to_key_hook *param, double move_speed)
{
	if (param->map->grid[(int)param->player->y][(int)(param->player->x + param->player->dir_x * move_speed)] == '0')
		param->player->x += param->player->dir_x * move_speed;
	if (param->map->grid[(int)(param->player->y + param->player->dir_y * move_speed)][(int)param->player->x] == '0')
		param->player->y += param->player->dir_y * move_speed;
}

void	walk_backward(t_data_to_key_hook *param, double move_speed)
{
	if (param->map->grid[(int)param->player->y][(int)(param->player->x - param->player->dir_x * move_speed)] == '0')
		param->player->x -= param->player->dir_x * move_speed;
	if (param->map->grid[(int)(param->player->y - param->player->dir_y * move_speed)][(int)param->player->x] == '0')
		param->player->y -= param->player->dir_y * move_speed;
}

void	strafe_right(t_data_to_key_hook *param, double move_speed)
{
	if (param->map->grid[(int)param->player->y][(int)(param->player->x + param->player->plane_x * move_speed)] == '0')
		param->player->x += param->player->plane_x * move_speed;
	if (param->map->grid[(int)(param->player->y + param->player->plane_y * move_speed)][(int)param->player->x] == '0')
		param->player->y += param->player->plane_y * move_speed;
}

void	strafe_left(t_data_to_key_hook *param, double move_speed)
{
	if (param->map->grid[(int)param->player->y][(int)(param->player->x - param->player->plane_x * move_speed)] == '0')
		param->player->x -= param->player->plane_x * move_speed;
	if (param->map->grid[(int)(param->player->y - param->player->plane_y * move_speed)][(int)param->player->x] == '0')
		param->player->y -= param->player->plane_y * move_speed;
}
