#include "cub3d.h"

t_images	*init_images(mlx_t *mlx)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	images->bg = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	images->wall = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	return (images);
}
void	free_images(mlx_t *mlx, t_images *images)
{
	mlx_delete_image(mlx, images->bg);
	mlx_delete_image(mlx, images->wall);
	free(images);
}