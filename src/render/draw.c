/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:37:59 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/15 18:50:00 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	line(t_windata *windata, int color, t_v2 start, t_v2 end)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	sx = start.x < end.x ? 1 : -1;
	sy = start.y < end.y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		mlx_pixel_put(windata->mlx, windata->mlx_win, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			start.y += sy;
		}
	}
}

void	pixel(t_windata *windata, int color, t_v2 pos)
{
	mlx_pixel_put(windata->mlx, windata->mlx_win, pos.x, pos.y, color);
}

void    square(t_windata *windata, int color, t_v2 center, int side_length, float angle)
{
    t_v2 vertices[4];
    int half_side = side_length / 2;

    // Calculate the original square vertices centered at origin
    vertices[0] = (t_v2){center.x - half_side, center.y - half_side};
    vertices[1] = (t_v2){center.x + half_side, center.y - half_side};
    vertices[2] = (t_v2){center.x + half_side, center.y + half_side};
    vertices[3] = (t_v2){center.x - half_side, center.y + half_side};

    // Rotate each vertex
    for (int i = 0; i < 4; i++) {
        vertices[i] = rotate_point(vertices[i], center, angle);
    }

    // Draw lines between the rotated vertices to form the square
    line(windata, color, vertices[0], vertices[1]);
    line(windata, color, vertices[1], vertices[2]);
    line(windata, color, vertices[2], vertices[3]);
    line(windata, color, vertices[3], vertices[0]);
}

void	rect(t_windata *windata, int color, t_v2 start, t_v2 end)
{
	line(windata, color, start, (t_v2){end.x, start.y});
	line(windata, color, start, (t_v2){start.x, end.y});
	line(windata, color, end, (t_v2){end.x, start.y});
	line(windata, color, end, (t_v2){start.x, end.y});
}

void	clear_window(t_windata *windata)
{
	mlx_clear_window(windata->mlx, windata->mlx_win);
}