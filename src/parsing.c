/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:27:25 by nicolas           #+#    #+#             */
/*   Updated: 2025/04/06 22:43:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


#define MSG_ERR_ELEMENTS_INVALID "Elements (textures / colors) format are not valid, please make you sure :\n\
- elements are before map description\n\
- elements are a duo key _val for example : NO ./my_texture_path"

t_bool	handle_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	return (FALSE);
}
// check extension

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

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

// FILE

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



void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] :%s\n", i, tab[i]);
		i++;
	}
	
}

int	len_tab(char **tab)
{
	int	i;

	 i = 0;
	 while (tab[i])
	 {
		i++;
	 }
	 return (i);
}

void	free_tab_str(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*cat_or_dup_str(char *s1, char *s2)
{
	if (s1 == NULL)
		return (ft_strdup(s2));
	else
		return (cft_strcat_realloc(s1, s2));
}

#define NB_ELEMENTS 6

t_key_val	*init_key_val(char *key, char *val)
{
	t_key_val *el;

	el = malloc(sizeof(t_key_val));
	if (key)
		el->key = ft_strdup(key);
	else
		el->key = NULL;
	if (val)
		el->val = ft_strdup(val);
	else
		el->val = NULL;
	return (el);
}

void	fill_tab_null(void	**tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i] = NULL;
		i++;
	}
	
}
void	free_key_val(t_key_val *el)
{
	if (el->key != NULL)
		free(el->key);
	if (el->val != NULL)
		free(el->val);
	free(el);
}

void	print_key_val(t_key_val *el)
{
	printf("el->key:%s\n", el->key);
	printf("el->val:%s\n", el->val);
}

void	print_tab_key_val(t_key_val **tab)
{
	int	i;

	 i =0;
	 while (tab[i])
	 {
		printf("-- EL %d\n", i);
		print_key_val(tab[i]);
		i++;
	 }
}

void	free_tab_key_val(t_key_val **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free_key_val(tab[i]);
		i++;
	}
}

t_key_val	**get_elements(char *file)
{
	int			i;
	char		**lines;
	char		**split;
	t_key_val	**elements;

	i = 0;
	lines = ft_split(file, '\n');
	elements = NULL;
	elements = malloc(NB_ELEMENTS + 1 * sizeof(t_key_val *));
	fill_tab_null((void **)elements, NB_ELEMENTS + 1);
	while (i < 6)
	{
		split = ft_split(lines[i], ' ');
		if (len_tab(split) != 2)
		{
			free_tab_str(lines);
			free_tab_str(split);
			free_tab_key_val(elements);
			return (NULL);
		}
		elements[i] = init_key_val(split[0], split[1]);
		free_tab_str(split);
		i++;
	}
	free_tab_str(lines);
	return (elements);
}



t_bool	map_is_valid(int argc, char **argv)
{
	char		*file;
	t_key_val	**elements;
	if (argc != 2)
		return (handle_error("The program need a file whith map configuration\n"));
	if (!extension_is_valid(argv[1]))
		return (handle_error("Extension is invalid. The programm accept only \".cub\" extension\n"));
	file = get_file(argv[1]);
	if (file == NULL)
		return (handle_error("The file is not readable\n"));
	// check minimal lines 9
	elements = get_elements(file);
	if (elements == NULL)
		return (handle_error(MSG_ERR_ELEMENTS_INVALID));
	// check key is valid
	// check open texture
	// check color
	print_tab_key_val(elements);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	if (!map_is_valid(argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}