/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:14:30 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/19 15:28:24 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# define CHARSET_MAP "01NSEW"
#define NB_ELEMENTS 6

// FILE
t_bool	check_args_and_extension(int argc, char **argv);
t_bool	file_have_minimal_lines(char *file);
char *get_file(char *filename);

// ERRORS
t_bool	print_error(char *message);
t_bool	print_error_details(char *message, char *failed);
t_bool	description_of_map_is_valid(char *file);
t_bool	characters_in_map_are_valid(char *desc_map);

// ELEMENTS
t_bool	color_is_rgb(char *color);
t_key_val	**get_elements(char *file);
t_bool	elements_are_valid(char *file);
t_bool	try_to_load_texture(char *val);
t_bool	is_texture(char *key);
t_bool	is_color(char *key);

int	len_tab(char **tab);
void	free_tab_str(char **tab);
char	**init_tab_str(int col_max, int row_max, char c_fill);
char	*cat_or_dup_str(char *s1, char *s2);
void	fill_tab_null(void	**tab, int size);
void	print_tab(char **tab);
t_key_val	*init_key_val(char *key, char *val);
void	free_tab_key_val(t_key_val **tab);
t_map	*init_map_parsing(char	*desc_map);
void	free_map_parsing(t_map *map);
t_bool	check_if_line_is_empty(char *file, int i_start);
int	skip_line(char *file, int i_start);
int	skip_next_line_after_empty(char *file, int i_start);
char	*get_description_of_map(char *file);
void	copy_desc_map_in_grid(t_map *map, char *desc_map);
t_bool	map_have_one_player(char *desc_map);
t_bool	player_enclosed_by_wall(t_map *map);
void	print_map(t_map *map);
void	print_key_val(t_key_val *el);
void	print_tab_key_val(t_key_val **tab);
t_bool	map_is_valid(int argc, char **argv);
int	get_x_max(char	*desc_map);
int	get_y_max(char	*desc_map);

#endif