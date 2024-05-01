/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 19:44:36 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	init(t_windata *data)
{
	if (!ends_with(data->smap.filename, MAP_EXT))
		return (pe(INVALID_MAP_EXT), false);
	if (!map_init(&data->smap))
		return (free_map(&data->smap, data->mlx), false);
	return (true);
}
int loop_hook(t_windata *data)
{
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

	if (argc != 2)
		return (pe(INVALID_ARGS), -1);
	ft_memset(&data, 0, sizeof(t_windata));
	data.smap.tilemap = (t_tilemap){0};
	data.smap.filename = argv[1]; // ..............................
	if (!init(&data))
		exit(EXIT_FAILURE);
	if (!player_init(&data.player, v2_to_v2f(data.smap.player_pos), data.smap.player_dir))
		exit(EXIT_FAILURE);
	//data.player = (t_player){v2_to_v2f(data.smap.player_pos),  PI / 2, PI / 2, -1};// TODO: set rotation depending on the map char dir
	//printf("Player pos: %d, %d\n", data.player.pos.x, data.player.pos.y);
	gettimeofday(&data.frame_control.last_update, NULL);  // Get current time
	data.frame_control.frame_delay = 1000.0 / 60.0;  // For 60 FPS, 1000 ms / 60
	update_settings(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT,
			PROGRAM_NAME);
	if (!load_sprites(data.mlx, &data.smap.sprites))
		close_win(&data);
	init_event_handlers(&data);
	data.win_buffer.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.win_buffer.img)
	{
		pe("Failed to allocate memory for image\n");
		exit(EXIT_FAILURE);
	}
	data.win_buffer.addr = mlx_get_data_addr(data.win_buffer.img,
			&data.win_buffer.bits_per_pixel, &data.win_buffer.line_length,
			&data.win_buffer.endian);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	free(data.mlx);
	free(data.mlx_win);
	return (0);
}

void	drawMapToScreen(t_windata *windata)
{
	reset_buffer(&windata->win_buffer, &windata->smap.sprites);
	drawScreen(windata);
	draw_minimap(windata);
	mlx_put_image_to_window(windata->mlx, windata->mlx_win,
		windata->win_buffer.img, 0, 0);
}

void draw_vertical_line(t_windata *windata, t_v2 bounds, t_ray ray, int x)
{
    char *img_data = windata->win_buffer.addr;
    int bytes_per_pixel = windata->win_buffer.bits_per_pixel / 8;
    t_imgbuffer sprite = get_sprite_by_side(&windata->smap.sprites, ray.side);
    unsigned char *tex = (unsigned char *)sprite.addr;

    if (x < 0) x = 0;
    if (x >= WIN_WIDTH) x = WIN_WIDTH - 1;

    for (int screen_y = 0; screen_y < WIN_HEIGHT; screen_y++) {
        int pixel_index = screen_y * windata->win_buffer.line_length + x * bytes_per_pixel;

    	if (screen_y >= bounds.x && screen_y < bounds.y) {
            // Wall
            double relY = (screen_y - bounds.x) / (double)(bounds.y - bounds.x);
            int texY = (int)(relY * IMG_SIZE) % IMG_SIZE;
            int texX;
            if (ray.side == EAST || ray.side == WEST) {
                texX = (int)((ray.hit_pos.y - (int)ray.hit_pos.y) * IMG_SIZE) % IMG_SIZE;
            } else {
                texX = (int)((ray.hit_pos.x - (int)ray.hit_pos.x) * IMG_SIZE) % IMG_SIZE;
            }

            int index = texY * sprite.line_length + texX * (sprite.bits_per_pixel / 8);
            *(int *)&img_data[pixel_index] = *(int *)&tex[index];
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
	while (angle < windata->player.angle + windata->player.fov / 2)
	{
		ray = raycast(windata, angle);
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
}

