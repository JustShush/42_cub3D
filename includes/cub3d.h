/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:40 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/29 20:05:11 by tiagoliv         ###   ########.fr       */
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
# include <stddef.h>

# include <mlx.h>
# include <libft.h>

# include <vecs.h>
# include <img.h>
# include <map.h>

# define PROGRAM_NAME "Cub3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 640

# define PI 3.14159265358979323846f
# define ROTATION_SPEED 0.11f
# define MOVEMENT_SPEED 0.15f
# define RAY_NUM WIN_WIDTH
# define PLAYER_ZOOM 0.1f

# define MINIMAP_WALL_SIZE 8
# define MINIMAP_OFFSET 5
# define MINIMAP_COLOR_PRIMARY (int) 0xDDDDDD
# define MINIMAP_COLOR_SECONDARY (int) 0x555555
# define MINIMAP_PLAYER_COLOR (int) 0x0000FF
# define MINIMAP_RAY_COLOR (int) 0xDD1111

# define WALL_COLOR (int) 0x00DD00

// ERRORS
# define MALLOC_ERROR "Malloc failed\n"

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

typedef struct t_player
{
	t_v2f	pos;
	double	angle;
	double	fov;
}	t_player;

typedef struct t_imgbuffer
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imgbuffer;

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
}	t_settings;

typedef struct t_windata
{
	void		*mlx;
	void		*mlx_win;
	t_imgbuffer	win_buffer;
	t_minimap	minimap;
	t_player	player;
	t_settings	settings;
	t_map		smap;
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
void	reset_buffer(t_imgbuffer *buffer, t_sprites *sprites);

//  Player
bool	move_player(t_player *player, enum e_player_direction dir);
bool	rotate_player(t_player *player, enum e_player_direction dir);
bool	player_zoom(t_player *player, double zoom);

//  Raycasting
t_v3f	raycast(t_windata *windata, double angle);

//  Minimap
void	draw_minimap(t_windata *windata);
void	draw_minimap_ray(t_windata *windata, t_v3f rayInter);

//  Settings
void	update_settings(t_windata	*windata);



// -------
char	**copy_array(char **arr);
int		get_start_map(char **map);

// check.c
int		check_map_closed(t_map map, char **bmap);
int		check_chars(char **map);
int		check_color(char *line, char **color);

// in map_utils.c
bool	ends_with(char *s1, char *s2);

// gen_utils.c
int		first_str(char *s1, char *s2);
bool	char_in_set(char c, char *set);
bool	only_digits(char *str);
void	pe(char *msg);

int		empty_line(char *line);

// frees
void	free_array(char **arr);

#endif