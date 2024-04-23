/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/22 20:28:35 by tiagoliv         ###   ########.fr       */
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

int loop_hook(t_windata *data) {
    struct timeval now;
    long elapsed;

    gettimeofday(&now, NULL);
    elapsed = (now.tv_sec - data->frame_control.last_update.tv_sec) * 1000;
    elapsed += (now.tv_usec - data->frame_control.last_update.tv_usec) / 1000;

    if (elapsed >= data->frame_control.frame_delay) {
        drawMapToScreen(data);  // Your update and render functions
        data->frame_control.last_update = now;
    }

    return (0);
}

int	main(int argc, char **argv)
{
	t_windata	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_windata));
	data.player = (t_player){(t_v2f){5, 5}, PI / 2, PI / 2, -1};
	gettimeofday(&data.frame_control.last_update, NULL);  // Get current time
	data.frame_control.frame_delay = 1000.0 / 60.0;  // For 60 FPS, 1000 ms / 60
	update_settings(&data);
	data.settings.ceiling_color = 0x0000DD;
	data.settings.floor_color = 0x964B00;
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
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	free(data.mlx);
	free(data.mlx_win);
	return (0);
}

void	drawMapToScreen(t_windata *windata)
{
	clear_img_buffer(&windata->win_buffer, &windata->settings);
	draw_minimap(windata, map);
	drawScreen(windata);
	mlx_put_image_to_window(windata->mlx, windata->mlx_win,
		windata->win_buffer.img, 0, 0);
}

void	draw_vertical_line(t_windata *windata, t_v2 bounds, t_ray ray, int x)
{
	char *img_data = windata->win_buffer.addr;
    int bytes_per_pixel = windata->win_buffer.bits_per_pixel / 8;
	unsigned char *	tex = (unsigned char *) get_sprite_by_side(&windata->sprites, ray.side).addr;

    if (x < 0) x = 0;
    if (x >= WIN_WIDTH) x = WIN_WIDTH - 1;

    for (int screen_y = 0; screen_y < WIN_HEIGHT; screen_y++) {
        int pixel_index = screen_y * windata->win_buffer.line_length + x * bytes_per_pixel;

		if (img_data[pixel_index]) {
			continue;
		}
        else if (screen_y < bounds.x) {
            // Sky
            for (int i = 0; i < bytes_per_pixel; i++) {
                img_data[pixel_index + i] = (windata->settings.ceiling_color >> (i * 8)) & 0xFF;
            }
        } else if (screen_y >= bounds.x && screen_y < bounds.y) {
            // Wall
            double relY = (screen_y - bounds.x) / (double)(bounds.y - bounds.x);
            int texY = (int)(relY * IMG_SIZE) % IMG_SIZE;
            int texX;
            if (ray.side == EAST || ray.side == WEST) {
                texX = (int)((ray.hit_pos.y - (int)ray.hit_pos.y) * IMG_SIZE) % IMG_SIZE;
            } else {
                texX = (int)((ray.hit_pos.x - (int)ray.hit_pos.x) * IMG_SIZE) % IMG_SIZE;
            }

            int index = texY * windata->sprites.wall.line_length + (texX * (windata->sprites.wall.bits_per_pixel / 8));
            for (int i = 0; i < bytes_per_pixel; i++) {
                img_data[pixel_index + i] = tex[index + i];
            }
        } else {
            // Ground
            for (int i = 0; i < bytes_per_pixel; i++) {
                img_data[pixel_index + i] = (windata->settings.floor_color >> (i * 8)) & 0xFF;
            }
        }
    }
}

void	drawScreen(t_windata *windata)
{
	t_ray	ray;
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
		ray = raycast(windata, map, angle);
		tmpangle = windata->player.angle - angle;
		if (tmpangle < 0)
			tmpangle += 2 * PI;
		if (tmpangle > 2 * PI)
			tmpangle -= 2 * PI;
		draw_minimap_ray(windata, ray.hit_pos);
		ray.dist *= cos(tmpangle); // Applying fisheye correction
		projected_wall_height = (int)(windata->settings.projection_plane_distance / ray.dist);
		wall_top = (WIN_HEIGHT / 2) - (projected_wall_height / 2);
		wall_bottom = (WIN_HEIGHT / 2) + (projected_wall_height / 2);
		draw_vertical_line(windata, (t_v2){wall_top, wall_bottom}, ray, (int)i);
		angle += windata->settings.ray_increment;
		i++;
	}
#ifdef PROFILER
	end = clock();

	// Calculate the time taken
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("Time taken: %fms\n", cpu_time_used);
#endif
}

