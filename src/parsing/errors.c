/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:47:57 by nveneros          #+#    #+#             */
/*   Updated: 2025/04/21 10:48:14 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	print_error(char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(message, 2);
	}
	return (FALSE);
}

t_bool	print_error_details(char *message, char *failed)
{
	print_error(message);
	ft_putstr_fd("The program stop at:", 2);
	ft_putstr_fd(failed, 2);
	ft_putstr_fd("\n", 2);
	return (FALSE);
}
