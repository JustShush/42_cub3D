/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 14:40:13 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	init(t_windata *data)
{
	if (!ends_with(data->smap.filename, MAP_EXT))
		return (pe(INVALID_MAP_EXT), false);
	if (!map_init(&data->smap))
		return (free_map(&data->smap, data->mlx), false);
	if (!player_init(&data->player, v2_to_v2f(data->smap.player_pos),
			data->smap.player_dir))
		return (false);
	gettimeofday(&data->frame_control.last_update, NULL);
	data->frame_control.frame_delay = 1000.0 / FPS;
	update_settings(data);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT,
			PROGRAM_NAME);
	if (!load_sprites(data->mlx, &data->smap.sprites))
		close_win(data);
	init_event_handlers(data);
	data->win_buffer.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->win_buffer.img)
	{
		pe(MALLOC_ERROR);
		exit(EXIT_FAILURE);
	}
	return (data->win_buffer.addr = mlx_get_data_addr(data->win_buffer.img,
			&data->win_buffer.bits_per_pixel, &data->win_buffer.line_length,
			&data->win_buffer.endian), true);
}

int	loop_hook(t_windata *data)
{
	struct timeval	now;
	long			elapsed;

	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - data->frame_control.last_update.tv_sec) * 1000;
	elapsed += (now.tv_usec - data->frame_control.last_update.tv_usec) / 1000;
	if (elapsed >= data->frame_control.frame_delay)
	{
		reset_buffer(&data->win_buffer, &data->smap.sprites);
		drawscreen(data);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->win_buffer.img, 0, 0);
		data->frame_control.last_update = now;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_windata	data;

	if (argc != 2)
		return (pe(INVALID_ARGS), -1);
	ft_memset(&data, 0, sizeof(t_windata));
	data.smap.tilemap = (t_tilemap){0};
	data.smap.filename = argv[1];
	if (!init(&data))
		exit(EXIT_FAILURE);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
