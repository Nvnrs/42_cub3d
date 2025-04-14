/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:28:17 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 10:29:27 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"

char *get_file(char *filename)
{
	char	*file;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (file == NULL)
			file = ft_strdup(line);
		else
			file = cft_strcat_realloc(file, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (file);
}

int	get_line_end(char *file, int start)
{
	int	i;

	i = start;
	while (file[i] && file[i] != '\n')
		i++;
	if (file[i] == '\n')
		i++;
	return (i);
}
