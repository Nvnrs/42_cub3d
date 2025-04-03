/**
 * Calculte the angle between each ray in degree.
 */
double	calculate_angle_between_each_ray(void)
{
	return (FOV / SCREEN_WIDTH);
}

/**
 * Calculte the slope of a ray with its angle in degree.
 */
double	calculate_ray_slope(t_ray ray)
{
	return (tan(convert_degree_to_radian(ray.angle)));
}
/**
 * Calculate the ray's y intercept from the ray slope and the player's position.
 */
double	calculate_ray_y_intercept(t_ray ray, t_player player)
{
	return (player.y - ray.slope * player.x);
}

/**
 * Calculate the ray's direction from the player's direction angle and the ray's angle.
 */
double	calculate_ray_direction(t_player player, t_ray ray)
{
	return (player.direction_angle - FOV / 2 + ray.angle);
}
