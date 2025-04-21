/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:39:07 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/21 14:35:17 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

#define MSG_ERR_NB_ARGS "The program needs only file with map configuration\n"
#define MSG_ERR_EXTENSION "Extension is invalid. \
The program accept only \".cub\" extension\n"

t_bool	filename_contain_one_point(char *filename)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (filename[i])
	{
		if (filename[i] == '.')
			count++;
		i++;
	}
	if (count != 1)
		return (FALSE);
	return (TRUE);
}

t_bool	extension_egal_cub(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (ft_strcmp(extension, ".cub") != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	extension_is_valid(char *filename)
{
	if (!filename_contain_one_point(filename))
		return (FALSE);
	if (!extension_egal_cub(filename))
		return (FALSE);
	return (TRUE);
}

t_bool	check_args_and_extension(int argc, char **argv)
{
	if (argc != 2)
		return (print_error(MSG_ERR_NB_ARGS));
	if (!extension_is_valid(argv[1]))
		return (print_error(MSG_ERR_EXTENSION));
	return (TRUE);
}
