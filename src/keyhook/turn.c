/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:07:19 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/19 14:05:44 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_right(t_data_to_key_hook *param, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = param->player->dir_x;
	old_plane_x = param->player->plane_x;
	param->player->dir_x = param->player->dir_x * cos(rot_speed) - param->player->dir_y * sin(rot_speed);
	param->player->dir_y = old_dir_x * sin(rot_speed) + param->player->dir_y * cos(rot_speed);
	param->player->plane_x = param->player->plane_x * cos(rot_speed) - param->player->plane_y * sin(rot_speed);
	param->player->plane_y = old_plane_x * sin(rot_speed) + param->player->plane_y * cos(rot_speed);
}

void	turn_left(t_data_to_key_hook *param, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = param->player->dir_x;
	old_plane_x = param->player->plane_x;
	param->player->dir_x = param->player->dir_x * cos(-rot_speed) - param->player->dir_y * sin(-rot_speed);
	param->player->dir_y = old_dir_x * sin(-rot_speed) + param->player->dir_y * cos(-rot_speed);
	param->player->plane_x = param->player->plane_x * cos(-rot_speed) - param->player->plane_y * sin(-rot_speed);
	param->player->plane_y = old_plane_x * sin(-rot_speed) + param->player->plane_y * cos(-rot_speed);
}
