/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:17:16 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/22 17:58:28 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ray	raycast(t_windata *windata, int map[][10], double angle)
{
	t_v2f	dir = v2ffrom_angle(angle);
    t_v2f	rayStart = windata->player.pos;
    t_v2f	vRayUnitStepSize = {
	sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x)), 
	   sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y)) 
    };
    t_v2	mapCheck = {rayStart.x, rayStart.y};
    t_v2f	vRayLength = {0, 0};
    t_v2	vStep = {dir.x < 0 ? -1 : 1, dir.y < 0 ? -1 : 1};

    // Calculate initial ray lengths
    if (dir.x < 0) {
        vRayLength.x = (rayStart.x - mapCheck.x) * vRayUnitStepSize.x;
    } else {
        vRayLength.x = (mapCheck.x + 1 - rayStart.x) * vRayUnitStepSize.x;
    }
    if (dir.y < 0) {
        vRayLength.y = (rayStart.y - mapCheck.y) * vRayUnitStepSize.y;
    } else {
        vRayLength.y = (mapCheck.y + 1 - rayStart.y) * vRayUnitStepSize.y;
    }
	double	maxRaydist = 10 * 2;
	double	dist = 0;
	bool	hitWall = false;
	enum e_ray_side side = EAST;
	while (!hitWall && dist < maxRaydist)
	{
		if (vRayLength.x < vRayLength.y)
		{
			mapCheck.x += vStep.x;
			dist = vRayLength.x;
			vRayLength.x += vRayUnitStepSize.x;
			side = (dir.x < 0) ? WEST : EAST;
		}
		else
		{
			mapCheck.y += vStep.y;
			dist = vRayLength.y;
			vRayLength.y += vRayUnitStepSize.y;
			side = (dir.y < 0) ? SOUTH : NORTH;
		}
		if (mapCheck.x >= 0 && mapCheck.y >= 0 && mapCheck.x < 10 && mapCheck.y < 10)
		{
			if (map[mapCheck.y][mapCheck.x])
				hitWall = true;
		}
	}

	t_v2f	rayIntersection = (t_v2f){rayStart.x + dir.x * dist, rayStart.y + dir.y * dist};
	//printf("Ray intersection: %f, %f\n", rayIntersection.x, rayIntersection.y);
	return ((t_ray){rayIntersection, dist, side});
}
