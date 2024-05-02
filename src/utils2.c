/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 21:40:46 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 13:08:43 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	this_or_that(bool condition, int this, int that)
{
	if (condition)
		return (this);
	return (that);
}

float	this_or_thatf(bool condition, float this, float that)
{
	if (condition)
		return (this);
	return (that);
}
