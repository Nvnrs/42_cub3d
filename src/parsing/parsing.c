/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:27:25 by nicolas           #+#    #+#             */
/*   Updated: 2025/04/19 15:26:49 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

t_bool	map_is_valid(int argc, char **argv)
{
	char		*file;
	t_key_val	**elements;
	
	// basics_checks
	if (!check_args_and_extension(argc, argv))
		return (FALSE);
	file = get_file(argv[1]);
	if (file == NULL)
		return (free(file), print_error("The file is not readable\n"));
	if (!file_have_minimal_lines(file))
		return (free(file), print_error("The file need have 9 lines minimal\n"));
	if (!elements_are_valid(file))
		return (free(file), FALSE);
	if (!description_of_map_is_valid(file))
		return (free(file), FALSE);
	free(file);
	return (TRUE);
}