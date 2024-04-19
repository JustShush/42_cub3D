/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/19 01:16:55 by tiagoliv         ###   ########.fr       */
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
	ft_memset(&data, 0, sizeof(t_windata));
	data.player = (t_player){(t_v2f){5, 5}, -PI / 2, PI / 2};
	update_settings(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT,
			PROGRAM_NAME);
	if (!load_sprites(data.mlx, &data.sprites))
		close_win(&data);
	init_event_handlers(&data);
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
	clear_buffer(&windata->win_buffer);
	draw_minimap(windata, map);
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
			/* PUT SKY PIXELS */
			for (int i = 0; i < bytes_per_pixel; i++)
			{
				img_data[pixel_index + i] = (SKY_COLOR >> (i * 8)) & 0xFF;
			}
		}
		if (y >= top && y < bottom)
		{
			/* PUT WALL PIXELS */
			for (int i = 0; i < bytes_per_pixel; i++)
			{
				img_data[pixel_index + i] = (color >> (i * 8)) & 0xFF;
			}
		}
		if (y >= bottom && y < WIN_HEIGHT)
		{
			/* PUT GROUND PIXELS */
			for (int i = 0; i < bytes_per_pixel; i++)
			{
				img_data[pixel_index + i] = (GROUND_COLOR >> (i * 8)) & 0xFF;
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
		rayInter = raycast(windata, map, angle);
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

