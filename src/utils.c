/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:56:07 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/19 15:13:13 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	darken_color(int hexColor, double blendFactor)
{
	int	r;
	int	g;
	int	b;

	if (blendFactor < 0)
		blendFactor = 0;
	if (blendFactor > 1)
		blendFactor = 1;
	r = (hexColor >> 16) & 0xFF;
	g = (hexColor >> 8) & 0xFF;
	b = hexColor & 0xFF;
	return (((int)((1 - blendFactor) * r) << 16)
			| ((int)((1 - blendFactor) * g) << 8)
			| (int)((1 - blendFactor) * b));
}

double	map_number(double x, t_v2f in, t_v2f out)
{
	return (out.x + (x - in.x) * (out.y - out.x) / (in.y - in.x));
}
