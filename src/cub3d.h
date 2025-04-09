/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:21:13 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/09 13:48:28 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/MYLIB42/mylib42.h"

#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	200
#define CUBE_SIZE		64
#define FOV 			60.0
#define M_PI			3.14159265358979323846

typedef struct	s_key_val
{
	char *key;
	char *val;
}	t_key_val;


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
	mlx_image_t	*minimap;
} t_images;

void	draw_line(mlx_image_t *image, t_coord c1, t_coord c2, uint32_t color);
void	fill_zone(t_coord start, t_coord end, mlx_image_t *image, uint32_t color);

#endif