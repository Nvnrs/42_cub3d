/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:21:13 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/04 18:37:21 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/MYLIB42/mylib42.h"

#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	768
#define CUBE_SIZE		64
#define FOV 			60.0
#define M_PI			3.14159265358979323846

typedef struct	s_coord
{
	int x;
	int y;
} t_coord;

typedef struct	s_coord_float
{
	float x;
	float y;
} t_coord_float;

typedef struct	s_images
{
	mlx_image_t *bg;
	mlx_image_t *wall;
} t_images;

void	draw_line(mlx_image_t *image, t_coord c1, t_coord c2);

#endif