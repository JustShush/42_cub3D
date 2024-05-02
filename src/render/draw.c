/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:37:59 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 16:03:35 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdint.h>
#include <string.h>

typedef struct s_linehelper
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}		t_linehelper;

static void	line_helper_init(t_linehelper *lh, t_v2 start, t_v2 end)
{
	lh->dx = abs(end.x - start.x);
	lh->dy = abs(end.y - start.y);
	if (start.x < end.x)
		lh->sx = 1;
	else
		lh->sx = -1;
	if (start.y < end.y)
		lh->sy = 1;
	else
		lh->sy = -1;
	if (lh->dx > lh->dy)
		lh->err = lh->dx / 2;
	else
		lh->err = -lh->dy / 2;
}

// Draws a line between two points inside the window buffer
void	line(t_windata *windata, int color, t_v2 start, t_v2 end)
{
	t_linehelper	lh;

	line_helper_init(&lh, start, end);
	while (1)
	{
		pixel_to_buffer(windata, color, start);
		if (start.x == end.x && start.y == end.y)
			break ;
		lh.e2 = lh.err;
		if (lh.e2 > -lh.dx)
		{
			lh.err -= lh.dy;
			start.x += lh.sx;
		}
		if (lh.e2 < lh.dy)
		{
			lh.err += lh.dx;
			start.y += lh.sy;
		}
	}
}

void	pixel_to_buffer(t_windata *windata, int color, t_v2 pos)
{
	char	*dst;

	dst = windata->win_buffer.addr + (pos.y * windata->win_buffer.line_length
			+ pos.x * (windata->win_buffer.bits_per_pixel / 8));
	if (dst < windata->win_buffer.addr || dst >= windata->win_buffer.addr
		+ windata->win_buffer.line_length * WIN_HEIGHT)
		return ;
	*(unsigned int *)dst = color;
}

// Draws a rectangle of a given size and color
void	rect(t_windata *windata, int color, t_v2 start, int size)
{
	int	i;

	i = start.x;
	while (i < start.x + size)
	{
		line(windata, color, (t_v2){i, start.y}, (t_v2){i, start.y + size});
		i++;
	}
}

// Resets the buffer to the ceiling and floor colors
void	reset_buffer(t_imgbuffer *buffer, t_sprites *sprites)
{
	int	pixel_index;
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			pixel_index = i * buffer->line_length + j * (buffer->bits_per_pixel
					/ 8);
			if (i < WIN_HEIGHT / 2)
				*(int *)&buffer->addr[pixel_index] = sprites->ceiling;
			else
				*(int *)&buffer->addr[pixel_index] = sprites->floor;
			j++;
		}
		i++;
	}
}
