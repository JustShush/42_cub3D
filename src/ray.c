/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:17:16 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 13:16:21 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef struct t_rayhelper
{
	t_v2f			dir;
	t_v2f			raystart;
	t_v2f			vrayunitstepsize;
	t_v2			mapcheck;
	t_v2f			vraylength;
	t_v2			vstep;
	double			maxraydist;
	double			dist;
	bool			hitwall;
	enum e_ray_side	side;
}	t_rayhelper;

static void	init_rayhelper(t_rayhelper *rhelper, t_v2f raystart, double angle)
{
	rhelper->dir = v2ffrom_angle(angle);
	rhelper->raystart = raystart;
	rhelper->vrayunitstepsize.x = sqrt(1 + (rhelper->dir.y / rhelper->dir.x)
			*(rhelper->dir.y / rhelper->dir.x));
	rhelper->vrayunitstepsize.y = sqrt(1 + (rhelper->dir.x / rhelper->dir.y)
			*(rhelper->dir.x / rhelper->dir.y));
	rhelper->mapcheck = (t_v2){raystart.x, raystart.y};
	rhelper->vraylength.x = this_or_thatf(rhelper->dir.x < 0,
			(raystart.x - rhelper->mapcheck.x) * rhelper->vrayunitstepsize.x,
			(rhelper->mapcheck.x + 1 - raystart.x)
			* rhelper->vrayunitstepsize.x);
	rhelper->vraylength.y = this_or_thatf(rhelper->dir.y < 0,
			(raystart.y - rhelper->mapcheck.y) * rhelper->vrayunitstepsize.y,
			(rhelper->mapcheck.y + 1 - raystart.y)
			* rhelper->vrayunitstepsize.y);
	rhelper->vstep.x = this_or_that(rhelper->dir.x < 0, -1, 1);
	rhelper->vstep.y = this_or_that(rhelper->dir.y < 0, -1, 1);
	rhelper->dist = 0;
	rhelper->hitwall = false;
	rhelper->side = EAST;
}

static void	raycalcs(t_rayhelper *rhelper)
{
	if (rhelper->vraylength.x < rhelper->vraylength.y)
	{
		rhelper->mapcheck.x += rhelper->vstep.x;
		rhelper->dist = rhelper->vraylength.x;
		rhelper->vraylength.x += rhelper->vrayunitstepsize.x;
		rhelper->side = this_or_that(rhelper->dir.x < 0, WEST, EAST);
	}
	else
	{
		rhelper->mapcheck.y += rhelper->vstep.y;
		rhelper->dist = rhelper->vraylength.y;
		rhelper->vraylength.y += rhelper->vrayunitstepsize.y;
		rhelper->side = this_or_that(rhelper->dir.y < 0, NORTH, SOUTH);
	}
}

t_ray	raycast(t_windata *windata, double angle)
{
	t_rayhelper		rhelper;

	init_rayhelper(&rhelper, windata->player.pos, angle);
	rhelper.maxraydist = windata->smap.tilemap.size.x
		* windata->smap.tilemap.size.y / 2;
	while (!rhelper.hitwall && rhelper.dist < rhelper.maxraydist)
	{
		raycalcs(&rhelper);
		if (rhelper.mapcheck.x >= 0 && rhelper.mapcheck.y >= 0
			&& rhelper.mapcheck.x < windata->smap.tilemap.size.x
			&& rhelper.mapcheck.y < windata->smap.tilemap.size.y)
		{
			if (windata->smap.tilemap.map
				[rhelper.mapcheck.y][rhelper.mapcheck.x])
				rhelper.hitwall = true;
		}
	}
	return ((t_ray){(t_v2f){
		rhelper.raystart.x + rhelper.dir.x * rhelper.dist,
		rhelper.raystart.y + rhelper.dir.y * rhelper.dist},
		rhelper.dist, rhelper.side
	});
}
