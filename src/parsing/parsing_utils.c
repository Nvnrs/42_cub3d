/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:55 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 13:31:52 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"

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
