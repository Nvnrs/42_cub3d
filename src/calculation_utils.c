/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:51:59 by pchateau          #+#    #+#             */
/*   Updated: 2025/04/08 16:15:11 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

/**
 * Convert degree to radian.
 */
float convert_degree_to_radian(float degree)
{
	return (degree * M_PI / 180);
}
