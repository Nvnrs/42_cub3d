/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:39:07 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/16 14:40:12 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

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
	char *extension;

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
		return (print_error("The program need a file whith map configuration\n"));
	if (!extension_is_valid(argv[1]))
		return (print_error("Extension is invalid. The programm accept only \".cub\" extension\n"));
	return (TRUE);
}
