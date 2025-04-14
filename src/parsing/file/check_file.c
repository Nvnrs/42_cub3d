/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:42:15 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 11:30:30 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"
#include "parsing.h"

t_bool	file_have_minimal_lines(char *file)
{
	char	**lines;
	t_bool	have;

	lines = ft_split(file, '\n');
	have = TRUE;
	if (len_tab(lines) < 9)
		have = FALSE;
	free_tab_str(lines);
	return (have);
}


