/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:32:33 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/18 17:40:53 by nveneros         ###   ########.fr       */
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

# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080
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

typedef struct s_textures
{
	mlx_texture_t*	north;
	mlx_texture_t*	south;
	mlx_texture_t*	east;
	mlx_texture_t*	west;
}	t_textures;

typedef struct s_colors
{
	unsigned int	floor;
	unsigned int	ceiling;
}	t_colors;

typedef	struct s_map
{
	char **grid;
	int	x_max;
	int	y_max;
	t_textures	textures;
	t_colors	colors;
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

enum	e_side
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef enum e_side	t_side;

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
	t_side	side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int	tex_x;
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
void	draw_and_put_bg(mlx_t *mlx, mlx_image_t *bg, t_map *map);
void	reset_wall_image(t_images *images);
void	draw_vertical_line(mlx_image_t *image, int draw_start, int draw_end, int x, uint32_t color);


void	raycasting_loop(t_player player, t_map map, t_images *images);

void	set_camera_x(t_ray *ray, int x);
void	set_dir(t_ray *ray, t_player player);
void	set_delta_dist(t_ray *ray);
void	set_side_dist(t_ray *ray, t_player player, int map_x, int map_y);
void	cast(t_ray *ray, t_map map, int map_x, int map_y);
void	calculate_perpendicular_wall_dist(t_ray *ray);
void	draw_wall(t_ray *ray, t_images *images, int x, t_map map);

void	find_wall_hitpoint(t_ray *ray, t_player player);
void	find_texture_x(t_ray *ray, mlx_texture_t *texture);
void	draw_vertical_line_texture(mlx_image_t *image, t_ray *ray, int x, mlx_texture_t *texture);


void my_keyhook(mlx_key_data_t keydata, void* void_param);

void	walk_forward(t_data_to_key_hook *param, double move_speed);
void	walk_backward(t_data_to_key_hook *param, double move_speed);
void	strafe_right(t_data_to_key_hook *param, double move_speed);
void	strafe_left(t_data_to_key_hook *param, double move_speed);
void	turn_right(t_data_to_key_hook *param, double rot_speed);
void	turn_left(t_data_to_key_hook *param, double rot_speed);

#endif