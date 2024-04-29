/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:54:21 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/29 20:04:22 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap(t_windata *windata)
{
	int		i;
	int		j;
	t_v2	pos;

	i = 0;
	j = 0;
	while (i < windata->smap.tilemap.size.y)
	{
		j = 0;
		pos = (t_v2){MINIMAP_OFFSET, MINIMAP_OFFSET};
		while (j < windata->smap.tilemap.size.x)
		{
			pos.x = MINIMAP_OFFSET + j * MINIMAP_WALL_SIZE;
			pos.y = MINIMAP_OFFSET + i * MINIMAP_WALL_SIZE;
			if (windata->smap.tilemap.map[i][j] == 1)
				rect(windata, MINIMAP_COLOR_PRIMARY, pos, MINIMAP_WALL_SIZE);
			else if (windata->smap.tilemap.map[i][j] == 0)
				rect(windata, MINIMAP_COLOR_SECONDARY, pos, MINIMAP_WALL_SIZE);
			j++;
		}
		i++;
	}
}

void	draw_minimap_ray(t_windata *windata, t_v3f rayInter)
{
	t_v2	start;
	t_v2	end;

	start = (t_v2){MINIMAP_OFFSET + windata->player.pos.x * MINIMAP_WALL_SIZE,
		MINIMAP_OFFSET + windata->player.pos.y * MINIMAP_WALL_SIZE};
	end = (t_v2){MINIMAP_OFFSET + rayInter.x * MINIMAP_WALL_SIZE,
		MINIMAP_OFFSET + rayInter.y * MINIMAP_WALL_SIZE};
	line(windata, MINIMAP_RAY_COLOR, start, end, true);
}
