/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:17:16 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 22:22:30 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef struct t_rayhelper
{
	t_v2f			dir;
	t_v2f			rayStart;
	t_v2f			vRayUnitStepSize;
	t_v2			mapCheck;
	t_v2f			vRayLength;
	t_v2			vStep;
	double			maxRaydist;
	double			dist;
	bool			hitWall;
	enum e_ray_side	side;
}	t_rayhelper;

static void	init_rayhelper(t_rayhelper *rhelper, t_v2f rayStart, double angle)
{
	rhelper->dir = v2ffrom_angle(angle);
	rhelper->rayStart = rayStart;
	rhelper->vRayUnitStepSize.x = sqrt(1 + (rhelper->dir.y / rhelper->dir.x)
			*(rhelper->dir.y / rhelper->dir.x));
	rhelper->vRayUnitStepSize.y = sqrt(1 + (rhelper->dir.x / rhelper->dir.y)
			*(rhelper->dir.x / rhelper->dir.y));
	rhelper->mapCheck = (t_v2){rayStart.x, rayStart.y};
	rhelper->vRayLength.x = this_or_that(rhelper->dir.x < 0,
			(rayStart.x - rhelper->mapCheck.x) * rhelper->vRayUnitStepSize.x,
			(rhelper->mapCheck.x + 1 - rayStart.x)
			* rhelper->vRayUnitStepSize.x);
	rhelper->vRayLength.y = this_or_that(rhelper->dir.y < 0,
			(rayStart.y - rhelper->mapCheck.y) * rhelper->vRayUnitStepSize.y,
			(rhelper->mapCheck.y + 1 - rayStart.y)
			* rhelper->vRayUnitStepSize.y);
	rhelper->vStep.x = this_or_that(rhelper->dir.x < 0, -1, 1);
	rhelper->vStep.y = this_or_that(rhelper->dir.y < 0, -1, 1);
	rhelper->dist = 0;
	rhelper->hitWall = false;
	rhelper->side = EAST;
}

static void	raycalcs(t_rayhelper *rhelper)
{
	if (rhelper->vRayLength.x < rhelper->vRayLength.y)
	{
		rhelper->mapCheck.x += rhelper->vStep.x;
		rhelper->dist = rhelper->vRayLength.x;
		rhelper->vRayLength.x += rhelper->vRayUnitStepSize.x;
		rhelper->side = this_or_that(rhelper->dir.x < 0, WEST, EAST);
	}
	else
	{
		rhelper->mapCheck.y += rhelper->vStep.y;
		rhelper->dist = rhelper->vRayLength.y;
		rhelper->vRayLength.y += rhelper->vRayUnitStepSize.y;
		rhelper->side = this_or_that(rhelper->dir.y < 0, SOUTH, NORTH);
	}
}

t_ray	raycast(t_windata *windata, double angle)
{
	t_rayhelper		rhelper;

	init_rayhelper(&rhelper, windata->player.pos, angle);
	rhelper.maxRaydist = windata->smap.tilemap.size.x
		* windata->smap.tilemap.size.y / 2;
	printf("Ray start: %f, %f\n", rhelper.rayStart.x, rhelper.rayStart.y);
	printf("Ray direction: %f, %f\n", rhelper.dir.x, rhelper.dir.y);
	printf("Ray unit step size: %f, %f\n", rhelper.vRayUnitStepSize.x, rhelper.vRayUnitStepSize.y);
	printf("Map check: %d, %d\n", rhelper.mapCheck.x, rhelper.mapCheck.y);
	printf("Ray length: %f, %f\n", rhelper.vRayLength.x, rhelper.vRayLength.y);
	printf("Step: %d, %d\n", rhelper.vStep.x, rhelper.vStep.y);
	exit(1);
	while (!rhelper.hitWall && rhelper.dist < rhelper.maxRaydist)
	{
		raycalcs(&rhelper);
		if (rhelper.mapCheck.x >= 0 && rhelper.mapCheck.y >= 0
			&& rhelper.mapCheck.x < windata->smap.tilemap.size.x
			&& rhelper.mapCheck.y < windata->smap.tilemap.size.y)
		{
			if (windata->smap.tilemap.map
				[rhelper.mapCheck.y][rhelper.mapCheck.x])
				rhelper.hitWall = true;
		}
	}

	return ((t_ray){(t_v2f){
		rhelper.rayStart.x + rhelper.dir.x * rhelper.dist,
		rhelper.rayStart.y + rhelper.dir.y * rhelper.dist},
		rhelper.dist, rhelper.side
	});
}


/*t_ray	raycast(t_windata *windata, double angle)
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
	double	maxRaydist = windata->smap.tilemap.size.x * windata->smap.tilemap.size.y / 2;
	double	dist = 0;
	bool	hitWall = false;
	enum e_ray_side side = EAST;
	(void)raycalcs;
	(void)init_rayhelper;
	printf("Ray start: %f, %f\n", rayStart.x, rayStart.y);
	printf("Ray direction: %f, %f\n", dir.x, dir.y);
	printf("Ray unit step size: %f, %f\n", vRayUnitStepSize.x, vRayUnitStepSize.y);
	printf("Map check: %d, %d\n", mapCheck.x, mapCheck.y);
	printf("Ray length: %f, %f\n", vRayLength.x, vRayLength.y);
	printf("Step: %d, %d\n", vStep.x, vStep.y);
	exit(1);
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
		if (mapCheck.x >= 0 && mapCheck.y >= 0 && mapCheck.x < windata->smap.tilemap.size.x && mapCheck.y < windata->smap.tilemap.size.y)
		{
			if (windata->smap.tilemap.map[mapCheck.y][mapCheck.x])
				hitWall = true;
		}
	}

	t_v2f	rayIntersection = (t_v2f){rayStart.x + dir.x * dist, rayStart.y + dir.y * dist};
	//printf("Ray intersection: %f, %f\n", rayIntersection.x, rayIntersection.y);
	return ((t_ray){rayIntersection, dist, side});
}*/