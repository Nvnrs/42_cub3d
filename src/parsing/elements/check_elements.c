/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:41:09 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 17:14:48 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"
#include "parsing.h"

#define MSG_ERR_ELEMENTS_INVALID "Elements (textures / colors) format are not valid, please make you sure :\n\
- elements are before map description\n\
- elements are a duo key _val for example : NO ./my_texture_path"
#define MSG_ERR_KEYS "The keys handle are : NO, SO, WE, EA, F, C\n"
#define MSG_ERR_COLOR "The color is not RGB.\n"

t_bool	key_is_valid(char *key)
{
	if (ft_strcmp(key, "NO") == 0
		|| ft_strcmp(key, "SO") == 0
		|| ft_strcmp(key, "WE") == 0
		|| ft_strcmp(key, "EA") == 0
		|| ft_strcmp(key, "F") == 0
		|| ft_strcmp(key, "C") == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	elements_are_valid(char *file)
{
	int	i;
	t_key_val	**elements;

	i = 0;
	elements = get_elements(file);
	if (elements == NULL)
		return (print_error(MSG_ERR_ELEMENTS_INVALID));
	while (elements[i])
	{
		if (!key_is_valid(elements[i]->key))
		{
			print_error_details(MSG_ERR_KEYS, elements[i]->key);
			free_tab_key_val(elements);
			return (FALSE);
		}
		if (is_texture(elements[i]->key) && !try_to_load_texture(elements[i]->val))
		{
			print_error_details("The Texture is not supported.\n", elements[i]->val);
			free_tab_key_val(elements);
			return (FALSE);
		}
		if (is_color(elements[i]->key) && !color_is_rgb(elements[i]->val))
		{
			print_error_details(MSG_ERR_COLOR, elements[i]->val);
			free_tab_key_val(elements);
			return (FALSE);
		}
		i++;
	}
	free_tab_key_val(elements);
	return (TRUE);
}

