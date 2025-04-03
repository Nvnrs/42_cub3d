/** A DEFINIR AU DEPART
* taille des murs (cubes)
* taille du joueur
* FOV du joueur
* position du joueur
* dimensions du plan de projection (ecran)
* relation entre le joueur et le plan de projection (ecran)
*/

typedef struct s_player
{
	// int	height;
	// int	fov;
	int	x;
	int	y;
}	t_player;

// typedef struct	s_projection_plane
// {
// 	int	width;
// 	int	height;
// }	t_projection_plane;



// int	main(void)
// {
// 	int	wall_height;
// 	t_player	player;
// 	t_projection_plane	projection_plane;
// 	int	distance_between_player_and_projection_plane;

// 	wall_height = 64;
// 	player.height = wall_height / 2;
// 	player.fov = 60;
// 	player.x = 96;
// 	player.y = 96;
// 	projection_plane.width = 1920;
// 	projection_plane.height = 1080;
// 	return (0);
// }

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MLX42/MLX42.h"
#include "../lib/MYLIB42/mylib42.h"

#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	200
#define CUBE_SIZE		64
#define FOV 			60.0
#define M_PI			3.14159265358979323846



// -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

t_bool	is_wall(int x, int y, char **map, int x_max, int y_max)
{
	int	x_in_map;
	int	y_in_map;

	x_in_map = x / CUBE_SIZE;
	y_in_map = y / CUBE_SIZE;
	if (x_in_map >= x_max || y_in_map >= y_max || map[y_in_map][x_in_map] == '1')
		return (TRUE);
	return (FALSE);
}

// char	**map_test(int x_max, int y_max)
// {
// 	char **map;
// 	int x;
// 	int y;

// 	map = malloc((x_max) * sizeof(char*));
// 	x = 0;
// 	//map[x][y]
// 	while (x < x_max)
// 	{
// 		y = 0;
// 		map[x] = malloc(x_max * sizeof(char));
// 		while (y < y_max)
// 		{
// 			if (x == 0 || x == x_max - 1 || y == 0 || y == y_max - 1)
// 				map[x][y] = '1';
// 			else
// 				map[x][y] = '0';
// 			if (x == 5 && y == 3)
// 				map[x][y] = 'P';
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (map);
// }

char	**map_test(int x_max, int y_max)
{
	char **map;
	int x;
	int y;

	map = malloc((y_max) * sizeof(char*));
	y = 0;
	//map[x][y]
	while (y < y_max)
	{
		x = 0;
		map[y] = malloc(x_max * sizeof(char));
		while (x < x_max)
		{
			if (x == 0 || x == x_max - 1 || y == 0 || y == y_max - 1)
				map[y][x] = '1';
			else
				map[y][x] = '0';
			if (x == 5 && y == 3)
				map[y][x] = 'P';
			x++;
		}
		y++;
	}
	return (map);
}

void	print_map(char **map, int x_max, int y_max)
{
	int	x;
	int	y;

	y = 0;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			printf("%c ", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	
}

/**
 * Convert degree to radian.
 */
double convert_degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

/**
 * Calculte the distance between the player and the camera plane.
 */
int	calculate_distance_between_player_and_plane(void)
{
	return ((SCREEN_WIDTH / 2) / tan(convert_degree_to_radian(FOV/2)));
}

/**
 * Calculte the angle between each ray in degree.
 */
double	calculate_angle_between_each_ray(void)
{
	return (FOV / SCREEN_WIDTH);
}

/**
 * Calculte the slope of a ray with the angle in degree.
 */
double	calculate_ray_slope(double degree)
{
	return (tan(convert_degree_to_radian(degree)));
}

int32_t main(void)
{
	t_player	player;
	char **map;
	
	map = map_test(10, 10);
	player.x = 5 * CUBE_SIZE - CUBE_SIZE / 2;
	player.y = 3 * CUBE_SIZE - CUBE_SIZE / 2;
	printf("player is inside wall: %d\n", is_wall(CUBE_SIZE, CUBE_SIZE, map, 10, 10));
	// mlx_t* mlx;

	// // Gotta error check this stuff
	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	// {
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (!(image = mlx_new_image(mlx, 128, 128)))
	// {
	// 	mlx_close_window(mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (mlx_image_to_window(mlx, image, 100, 300) == -1)
	// {
	// 	mlx_close_window(mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	print_map(map, 10, 10);
	return (EXIT_SUCCESS);
}
