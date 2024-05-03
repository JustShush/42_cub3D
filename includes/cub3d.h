/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:40 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 16:07:43 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <img.h>
# include <libft.h>
# include <map.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <vecs.h>

# define PROGRAM_NAME "Cub3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 640

# define PI 3.14159265358979323846f
# define ROTATION_SPEED 0.11f
# define MOVEMENT_SPEED 0.15f
# define RAY_NUM WIN_WIDTH
# define FPS 60.0

# define MINIMAP_WALL_SIZE 8
# define MINIMAP_OFFSET 5
# define MINIMAP_COLOR_PRIMARY 0xDDDDDD
# define MINIMAP_COLOR_SECONDARY 0x555555
# define MINIMAP_RAY_COLOR 0xDD1111

// ERRORS
# define MALLOC_ERROR "Malloc failed\n"
# define INVALID_ARGS "Invalid arguments\nUsage: ./cub3d <map>\n"

enum				e_player_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum				e_ray_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct t_ray
{
	t_v2f			hit_pos;
	double			dist;
	enum e_ray_side	side;
}					t_ray;

typedef struct t_player
{
	t_v2f			pos;
	double			angle;
	double			fov;
	int				mouse_x;
}					t_player;

typedef struct t_minimap
{
	t_v2			pos;
	t_imgbuffer		square_primary;
	t_imgbuffer		square_secondary;
}					t_minimap;

typedef struct t_settings
{
	double			projection_plane_distance;
	double			ray_increment;
}					t_settings;

typedef struct s_frame_control
{
	struct timeval	last_update;
	float			frame_delay;
}					t_frame_control;

typedef struct t_windata
{
	void			*mlx;
	void			*mlx_win;
	t_imgbuffer		win_buffer;
	t_minimap		minimap;
	t_player		player;
	t_settings		settings;
	t_map			smap;
	t_frame_control	frame_control;
}					t_windata;

//  Render
// 		\	draw.c
void				line(t_windata *windata, int color, t_v2 start, t_v2 end);
void				pixel_to_buffer(t_windata *windata, int color, t_v2 pos);
void				rect(t_windata *windata, int color, t_v2 start, int size);
void				reset_buffer(t_imgbuffer *buffer, t_sprites *sprites);

// 		\	sprites_utils.c
t_imgbuffer			get_sprite_by_side(t_sprites *sprites,
						enum e_ray_side side);

//      \   screen.c
void				drawscreen(t_windata *windata);
void				draw_vertical_line(t_windata *windata, t_v2 bounds,
						t_ray ray, int x);

//  Player
bool				move_player(t_player *player, t_tilemap *tilemap,
						enum e_player_direction dir);
bool				rotate_player(t_player *player,
						enum e_player_direction dir);
bool				player_set_direction(t_player *player, char player_dir);
bool				player_init(t_player *player, t_v2f pos, char player_dir);

//  Raycasting
t_ray				raycast(t_windata *windata, double angle);

//  Minimap
void				draw_minimap(t_windata *windata);
void				draw_minimap_ray(t_windata *windata, t_v2f rayInter);
void				draw_minimap_rays(t_windata *windata);

//  Settings
void				update_settings(t_windata *windata);

// Utils.c
bool				char_in_set(char c, char *set);
bool				only_digits(char *str);
void				pe(char *msg);
int					empty_line(char *line);
bool				ends_with(char *s1, char *s2);

// Utils2.c

int					this_or_that(bool condition, int this, int that);
float				this_or_thatf(bool condition, float this, float that);
float				normalize_radian(float angle);

// frees
void				free_array(char **arr);
void				free_map(t_map *map, void *mlx);

// EventHandlers
void				init_event_handlers(t_windata *windata);
void				close_win(t_windata *windata);

#endif