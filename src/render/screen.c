/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:24:21 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 15:56:56 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	drawscreen(t_windata *windata)
{
	t_ray	ray;
	double	angle;
	double	i;
	int		projected_wall_height;
	t_v2	wall_bounds;

	angle = windata->player.angle - windata->player.fov / 2;
	i = 0;
	while (angle < windata->player.angle + windata->player.fov / 2)
	{
		ray = raycast(windata, angle);
		ray.dist *= cos(normalize_radian(windata->player.angle - angle));
		projected_wall_height
			= (int)(windata->settings.projection_plane_distance / ray.dist);
		wall_bounds = (t_v2){(WIN_HEIGHT / 2) - (projected_wall_height / 2),
			(WIN_HEIGHT / 2) + (projected_wall_height / 2)};
		draw_vertical_line(windata, wall_bounds, ray, (int)i);
		angle += windata->settings.ray_increment;
		i++;
	}
}

typedef struct t_vertical_line_helper
{
	t_imgbuffer	sprite;
	t_v2		bounds;
	int			pixel_index;
	int			sprite_index;
	double		rel_y;
	int			screen_y;
	int			tex_y;
	int			tex_x;
}	t_vertical_line_helper;

static void	vertical_line_draw_pixel(t_windata *windata,
		t_vertical_line_helper *helper, t_ray ray, int x)
{
	helper->pixel_index = helper->screen_y * windata->win_buffer.line_length + x
		* windata->win_buffer.bits_per_pixel / 8;
	helper->rel_y = (helper->screen_y - helper->bounds.x)
		/ (double)(helper->bounds.y - helper->bounds.x);
	helper->tex_y = (int)(helper->rel_y * IMG_SIZE) % IMG_SIZE;
	if (ray.side == EAST || ray.side == WEST)
	{
		helper->tex_x = (int)((ray.hit_pos.y - (int)ray.hit_pos.y) * IMG_SIZE)
			% IMG_SIZE;
	}
	else
	{
		helper->tex_x = (int)((ray.hit_pos.x - (int)ray.hit_pos.x) * IMG_SIZE)
			% IMG_SIZE;
	}
	helper->sprite_index = helper->tex_y * helper->sprite.line_length
		+ helper->tex_x * (helper->sprite.bits_per_pixel / 8);
	*(int *)&windata->win_buffer.addr[helper->pixel_index]
		= *(int *)&helper->sprite.addr[helper->sprite_index];
}

void	draw_vertical_line(t_windata *windata, t_v2 bounds, t_ray ray, int x)
{
	t_vertical_line_helper	helper;

	helper.sprite = get_sprite_by_side(&windata->smap.sprites, ray.side);
	x = this_or_that(x < 0, 0, x);
	x = this_or_that(x >= WIN_WIDTH, WIN_WIDTH - 1, x);
	helper.bounds = bounds;
	helper.screen_y = 0;
	while (helper.screen_y < WIN_HEIGHT)
	{
		if (helper.screen_y >= bounds.x && helper.screen_y < bounds.y)
		{
			vertical_line_draw_pixel(windata, &helper, ray, x);
		}
		helper.screen_y++;
	}
}
