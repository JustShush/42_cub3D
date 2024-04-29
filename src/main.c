/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/29 20:04:44 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*int map[10][10] = {
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
};*/

void	printMap(char **map) {
	if (map == NULL) {
		printf("map is NULL\n");
		return ;
	}
	for (int i = 0; map[i] != NULL; i++) {
		printf("%s\n",  map[i]);
	}
}

bool	init(t_windata *data)
{
	// check valid map name (ends with ext .cub) and exists in the fs
	if (!ends_with(data->smap.filename, MAP_EXT))
		return (pe(INVALID_MAP_EXT), false);
	if (!map_init(&data->smap))
		return (false);
	
	int i = 0;
	int j = 0;
	while (i < data->smap.tilemap.size.y)
	{
		j = 0;
		while (j < data->smap.tilemap.size.x)
		{
			if (data->smap.tilemap.map[i][j] == -1)
				printf("-");
			else if (data->smap.tilemap.map[i][j] == 0)
				printf("0");
			else
				printf("1");
			j++;
		}
		printf("\n");
		i++;
	}

	return (true);
}

int	check_map(t_map map)
{
	if (check_map_closed(map, map.file))
		return (1);
	else if (check_chars(map.file))
		return (1);
	/*else if (check_valid_color(map.textures))
		return (1);*/
	return (0);
}

int	main(int argc, char **argv)
{
	t_windata	data;

	(void)argc;
	ft_memset(&data, 0, sizeof(t_windata));
	data.smap.filename = argv[1]; // ..............................
	if (!init(&data))
		exit(EXIT_FAILURE);
	data.player = (t_player){v2_to_v2f(data.smap.player_pos), - PI / 2, PI / 2};// TODO: set rotation depending on the map char dir
	//printf("Player pos: %d, %d\n", data.player.pos.x, data.player.pos.y);
	update_settings(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT,
			PROGRAM_NAME);
	if (!load_sprites(data.mlx, &data.smap.sprites))
		close_win(&data);
	init_event_handlers(&data);
	/*if (check_map(data.smap))
		return (printf("here\n"), -1);*/
	// buffer logic
	data.win_buffer.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.win_buffer.img)
	{
		fprintf(stderr, "Failed to allocate memory for image\n");
		exit(EXIT_FAILURE);
	}
	data.win_buffer.addr = mlx_get_data_addr(data.win_buffer.img,
			&data.win_buffer.bits_per_pixel, &data.win_buffer.line_length,
			&data.win_buffer.endian);
	if (!data.win_buffer.addr)
	{
		fprintf(stderr, "Failed to get image address\n");
		exit(EXIT_FAILURE);
	}
	drawMapToScreen(&data);
	mlx_loop(data.mlx);
	free(data.mlx);
	free(data.mlx_win);
	return (0);
}

void	drawMapToScreen(t_windata *windata)
{
	reset_buffer(&windata->win_buffer, &windata->smap.sprites);
	draw_minimap(windata);
	drawScreen(windata);
	clear_window(windata);
	mlx_put_image_to_window(windata->mlx, windata->mlx_win,
		windata->win_buffer.img, 0, 0);
}

void	draw_vertical_line(t_windata *windata, int x, int top, int bottom,
		int color)
{
	char	*img_data;
	int		bytes_per_pixel;
	int		line_length;
	int		pixel_index;

	img_data = windata->win_buffer.addr;
	bytes_per_pixel = windata->win_buffer.bits_per_pixel / 8;
	line_length = windata->win_buffer.line_length;
	if (top < 0)
		top = 0;
	if (bottom > WIN_HEIGHT)
		bottom = WIN_HEIGHT;
	if (x < 0)
		x = 0;
	if (x >= WIN_WIDTH)
		x = WIN_WIDTH - 1;
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		pixel_index = y * line_length + x * bytes_per_pixel;
		if (pixel_index >= line_length * WIN_HEIGHT)
		{
			// the code should never get here!
			fprintf(stderr, "Pixel index out of bounds\n");
			break ;
		}
		if (img_data[pixel_index] != 0)
			continue ;
		if (y >= 0 && y < top)
		{
			// PUT SKY PIXELS 
			for (int i = 0; i < bytes_per_pixel; i++)
			{
				img_data[pixel_index + i] = (windata->smap.sprites.ceiling >> (i * 8)) & 0xFF;
			}
		}
		if (y >= top && y < bottom)
		{
			// PUT WALL PIXELS
			for (int i = 0; i < bytes_per_pixel; i++)
			{
				img_data[pixel_index + i] = (color >> (i * 8)) & 0xFF;
			}
		}
		if (y >= bottom && y < WIN_HEIGHT)
		{
			// PUT GROUND PIXELS
			for (int i = 0; i < bytes_per_pixel; i++)
			{
				img_data[pixel_index + i] = (windata->smap.sprites.floor >> (i * 8)) & 0xFF;
			}
		}
	}
}

void	drawScreen(t_windata *windata)
{
	t_v3f	rayInter;
	double	angle;
	double	i;
	double	tmpangle;
	int		projected_wall_height;
	int		wall_top;
	int		wall_bottom;

	angle = windata->player.angle - windata->player.fov / 2;
	i = 0;
#ifdef PROFILER
	clock_t start, end;
	double cpu_time_used;
	start = clock();
#endif
	while (angle < windata->player.angle + windata->player.fov / 2)
	{
		rayInter = raycast(windata, angle);
		tmpangle = windata->player.angle - angle;
		if (tmpangle < 0)
			tmpangle += 2 * PI;
		if (tmpangle > 2 * PI)
			tmpangle -= 2 * PI;
		draw_minimap_ray(windata, rayInter);
		rayInter.z *= cos(tmpangle); // Applying fisheye correction
		projected_wall_height = (int)(windata->settings.projection_plane_distance / rayInter.z);
		wall_top = (WIN_HEIGHT / 2) - (projected_wall_height / 2);
		wall_bottom = (WIN_HEIGHT / 2) + (projected_wall_height / 2);
		draw_vertical_line(windata, (int)i, wall_top, wall_bottom, WALL_COLOR);
		angle += windata->settings.ray_increment;
		i++;
	}
#ifdef PROFILER
	end = clock();

	// Calculate the time taken
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken: %f\n", cpu_time_used);
#endif
}

