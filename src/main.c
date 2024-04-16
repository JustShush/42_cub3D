/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/16 16:42:06 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


int	main(int argc, char **argv)
{
	t_windata	data;

	(void)argc;
	(void)argv;
	data.player = (t_player){(t_v2){100, 100}, 0};
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT,
			PROGRAM_NAME);
	if (!load_sprites(data.mlx, &data.sprites))
		close_win(&data);
	init_event_handlers(&data);
	drawMap(&data, &data.sprites);
	mlx_loop(data.mlx);
	free(data.mlx);
	free(data.mlx_win);
	return (0);
}

void	drawMap(t_windata *windata, t_sprites *sprites)
{
	int	i = 0;
	int	j = 0;

	clear_window(windata);
	while (i < (int)(sizeof(map) / sizeof(map[0])))
	{
		j = 0;
		t_v2 pos = {0,0};
		while (j < (int) (sizeof(map[0]) / sizeof(map[0][0])))
		{
			pos.x = j * IMG_SIZE;
			pos.y = i * IMG_SIZE;
			if (map[i][j])
				draw_sprite(windata->mlx, windata->mlx_win, pos, sprites->wall);
			else
				draw_sprite(windata->mlx, windata->mlx_win, pos, sprites->floor);
			j++;
		}
		i++;
	}
	square(windata, 0x0000FF, windata->player.pos, 20, windata->player.angle);
	line(windata, 0xFF0000, windata->player.pos, 
		v2add(windata->player.pos, v2from_angle(windata->player.angle, 20))
	);
	//drawGrid(windata);
	drawRays(windata);
}

void	drawGrid(t_windata *windata)
{
	int i = 0;
	int j = 0;
	t_v2 start = {0, 0};
	t_v2 end = {0, 0};

	while (i < IMG_SIZE * 10)
	{
		start.x = 0;
		start.y = i;
		end.x = WIN_WIDTH / 2;
		end.y = i;
		line(windata, 0x006600, start, end);
		i += IMG_SIZE;
	}
	while (j < IMG_SIZE * 10)
	{
		start.x = j;
		start.y = 0;
		end.x = j;
		end.y = WIN_HEIGHT;
		line(windata, 0x006600, start, end);
		j += IMG_SIZE;
	}
}

void	drawRays(t_windata *windata)
{
	t_v2f	rayInter;
	double	angle;

	angle = windata->player.angle - FOV / 2;
	while (angle < windata->player.angle + FOV / 2)
	{
		rayInter = raycast(windata, map, angle);
		line(windata, 0x00FF00, windata->player.pos, 
			(t_v2){rayInter.x * IMG_SIZE, rayInter.y * IMG_SIZE}
		);
		angle += RAY_INCREMENT;
	}
}
