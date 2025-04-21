/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:27:25 by nicolas           #+#    #+#             */
/*   Updated: 2025/04/21 14:33:41 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

#define MSG_ERR_FILE_LINES "The file needs a minimum of 9 non-empty lines\n"
#define MSG_ERR_FILE_READ "The file is not readable\n"

t_bool	map_is_valid(int argc, char **argv)
{
	char	*file;

	if (!check_args_and_extension(argc, argv))
		return (FALSE);
	file = get_file(argv[1]);
	if (file == NULL)
		return (free(file), print_error(MSG_ERR_FILE_READ));
	if (!file_have_minimal_lines(file))
		return (free(file), print_error(MSG_ERR_FILE_LINES));
	if (!elements_are_valid(file))
		return (free(file), FALSE);
	if (!description_of_map_is_valid(file))
		return (free(file), FALSE);
	free(file);
	return (TRUE);
}
