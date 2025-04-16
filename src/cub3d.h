/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:32:33 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/16 15:51:55 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/time.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/MYLIB42/mylib42.h"

# define SCREEN_WIDTH	320
# define SCREEN_HEIGHT	200
# define CUBE_SIZE		64
# define FOV 			60.0
# define M_PI			3.14159265358979323846

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

typedef	struct s_map
{
	char **grid;
	int	x_max;
	int	y_max;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	t_bool	hit;
	int		side;//enum?
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_data_to_keyhook
{
	t_player	*player;
	t_map		*map;
	t_images	*images;
	mlx_t		*mlx;
}	t_data_to_key_hook;

t_images	*init_images(mlx_t *mlx);

void	fill_zone(t_coord start, t_coord end, mlx_image_t *image, uint32_t color);
void	draw_and_put_bg(mlx_t *mlx, mlx_image_t *bg);
void	reset_wall_image(t_images *images);
void	draw_vertical_line(mlx_image_t *image, int draw_start, int draw_end, int x, uint32_t color);


void	raycasting(t_player player, t_map map, t_images *images);

void	set_camera_x(t_ray *ray, int x);
void	set_dir(t_ray *ray, t_player player);
void	set_delta_dist(t_ray *ray);
void	set_side_dist(t_ray *ray, t_player player, int map_x, int map_y);
void	cast(t_ray *ray, t_map map, int map_x, int map_y);
void	calculate_perpendicular_wall_dist(t_ray *ray);
void	draw_wall(t_ray *ray, t_images *images, int x);


void my_keyhook(mlx_key_data_t keydata, void* void_param);

#endif