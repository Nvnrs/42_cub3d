/**
 * Cast rays in the player's field of view (FOV).
 */
void	raycasting(t_player player, t_map map)
{
	double	angle_between_each_ray;
	t_ray	ray;
	int		i;

	angle_between_each_ray = calculate_angle_between_each_ray();
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray.angle = player.direction_angle - (FOV / 2) + (i / SCREEN_WIDTH) * FOV;
		ray.slope = calculate_ray_slope(ray);
		ray.y_intercept = calculate_ray_y_intercept(ray, player);
		ray.distance_vertical_intersection = vertical_intersection(ray, player, map);
		ray.distance_horizontal_intersection = horizontal_intersection(ray, player, map);
		if (ray.distance_vertical_intersection < ray.distance_horizontal_intersection)
			ray.smallest_distance = ray.distance_vertical_intersection;
		else
			ray.smallest_distance = ray.distance_horizontal_intersection;
		//calculer la hauteur du mur
		i++;
	}
}
