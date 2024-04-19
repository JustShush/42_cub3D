/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:37:59 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/19 00:38:29 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <string.h>
#include <stdint.h>

void	line(t_windata *windata, int color, t_v2 start, t_v2 end, bool buffer)
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
		if (buffer)
			pixel_to_buffer(windata, color, start, false);
		else
			pixel(windata, color, start);
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

void	pixel_to_buffer(t_windata *windata, int color, t_v2 pos, bool only_if_0)
{
	char	*dst;

	dst = windata->win_buffer.addr + (pos.y * windata->win_buffer.line_length
			+ pos.x * (windata->win_buffer.bits_per_pixel / 8));
	if (only_if_0 && *(unsigned int *)dst != 0)
		return ;
	*(unsigned int *)dst = color;
}

void	square(t_windata *windata, int color, t_v2 center, int side_length,
		float angle)
{
	t_v2	vertices[4];
	int		half_side;

	half_side = side_length / 2;
	// Calculate the original square vertices centered at origin
	vertices[0] = (t_v2){center.x - half_side, center.y - half_side};
	vertices[1] = (t_v2){center.x + half_side, center.y - half_side};
	vertices[2] = (t_v2){center.x + half_side, center.y + half_side};
	vertices[3] = (t_v2){center.x - half_side, center.y + half_side};
	// Rotate each vertex
	for (int i = 0; i < 4; i++)
	{
		vertices[i] = rotate_point(vertices[i], center, angle);
	}
	// Draw lines between the rotated vertices to form the square
	line(windata, color, vertices[0], vertices[1], true);
	line(windata, color, vertices[1], vertices[2], true);
	line(windata, color, vertices[2], vertices[3], true);
	line(windata, color, vertices[3], vertices[0], true);
}

void	rect(t_windata *windata, int color, t_v2 start, int size)
{
	int	i;

	i = start.x;
	while (i < start.x + size)
	{
		line(windata, color, (t_v2){i, start.y}, (t_v2){i, start.y + size}, true);
		i++;
	}
}

// Cleans the buffer window
void	clear_window(t_windata *windata)
{
	mlx_clear_window(windata->mlx, windata->mlx_win);
}

void	clear_buffer(t_imgbuffer *buffer)
{
	ft_memset(buffer->addr, 0, buffer->line_length * WIN_HEIGHT);
}
