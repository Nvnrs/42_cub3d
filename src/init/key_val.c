/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:49:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/14 11:02:13 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "calculation.h"
#include "parsing.h"

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

void	free_key_val(t_key_val *el)
{
	if (el->key != NULL)
		free(el->key);
	if (el->val != NULL)
		free(el->val);
	free(el);
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
	free(tab);
}
