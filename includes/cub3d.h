/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:40 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/22 20:04:24 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

# include <mlx.h>
# include <libft.h>

# include <vecs.h>
# include <img.h>

# define PROGRAM_NAME "Cub3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 640

# define PI 3.14159265358979323846f
# define ROTATION_SPEED 0.11f
# define MOVEMENT_SPEED 0.15f
# define RAY_NUM WIN_WIDTH
# define PLAYER_ZOOM 0.1f

# define MINIMAP_WALL_SIZE 20
# define MINIMAP_OFFSET MINIMAP_WALL_SIZE
# define MINIMAP_COLOR_PRIMARY (int) 0xDDDDDD
# define MINIMAP_COLOR_SECONDARY (int) 0x555555
# define MINIMAP_RAY_COLOR (int) 0xDD1111

# define WALL_COLOR (int) 0x00DD00

//# define PROFILER
# ifdef PROFILER
#  include <time.h>
# endif


enum	e_player_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum	e_ray_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct t_ray
{
	t_v2f				hit_pos;
	double				dist;
	enum	e_ray_side	side;
}	t_ray;

typedef struct t_player
{
	t_v2f	pos;
	double	angle;
	double	fov;
	int		mouse_x;
}	t_player;

typedef struct t_minimap
{
	t_v2		pos;
	t_imgbuffer	square_primary;
	t_imgbuffer	square_secondary;
}	t_minimap;

typedef struct t_settings
{
	double	projection_plane_distance;
	double	ray_increment;
	int		ceiling_color;
	int		floor_color;
}	t_settings;

typedef struct s_frame_control {
    struct timeval last_update;
    float frame_delay;
} t_frame_control;

typedef struct t_windata
{
	void			*mlx;
	void			*mlx_win;
	t_imgbuffer		win_buffer;
	t_sprites		sprites;
	t_minimap		minimap;
	t_player		player;
	t_settings		settings;
	t_frame_control frame_control;
}	t_windata;

void	drawMapToScreen(t_windata *windata);
void	drawScreen(t_windata *windata);

void	init_event_handlers(t_windata *windata);
void	close_win(t_windata *windata);

//  Render 
// 	 \	draw.c
void	line(t_windata *windata, int color, t_v2 start, t_v2 end, bool buffer);
void	pixel(t_windata *windata, int color, t_v2 pos);
void	pixel_to_buffer(t_windata *windata, int color, t_v2 pos, bool only_if_0);
void    square(t_windata *windata, int color, t_v2 center, int side_length, float angle);
void	rect(t_windata *windata, int color, t_v2 start, int size);
void	clear_window(t_windata *windata);
void	clear_img_buffer(t_imgbuffer *buffer, t_settings *settings);

//  Player
bool	move_player(t_player *player, enum e_player_direction dir);
bool	rotate_player(t_player *player, enum e_player_direction dir);
bool	player_zoom(t_player *player, double zoom);

//  Raycasting
t_ray	raycast(t_windata *windata, int map[][10], double angle);

//  Minimap
void	draw_minimap(t_windata *windata, int map[][10]);
void	draw_minimap_ray(t_windata *windata, t_v2f rayInter);

//  Settings
void	update_settings(t_windata	*windata);

//  Utils
int		darken_color(int hexColor, double blendFactor);
double	map_number(double x, t_v2f in, t_v2f out);
t_imgbuffer	get_sprite_by_side(t_sprites *sprites, enum e_ray_side side);

#endif