/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:19:30 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 20:23:28 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_imgbuffer	get_sprite_by_side(t_sprites *sprites, enum e_ray_side side)
{
	if (side == NORTH)
		return (sprites->north.img);
	else if (side == SOUTH)
		return (sprites->south.img);
	else if (side == EAST)
		return (sprites->east.img);
	else if (side == WEST)
		return (sprites->west.img);
	return (sprites->north.img);
}
