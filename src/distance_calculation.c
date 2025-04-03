/**
 * Calculte the distance between the player and the camera plane.
 */
int	calculate_distance_between_player_and_plane(void)
{
	return ((SCREEN_WIDTH / 2) / tan(convert_degree_to_radian(FOV/2)));
}

/**
 * Calculate the distance between two points.
 */
int	calculate_distance_between_two_points(int xa, int ya, int xb, int yb)
{
	return (sqrt(pow(xb - xa, 2) + pow(yb - ya, 2)));
}
