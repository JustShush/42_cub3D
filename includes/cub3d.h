/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:40 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/18 17:05:00 by tiagoliv         ###   ########.fr       */
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

# include <mlx.h>
# include <libft.h>

# include <vecs.h>
# include <img.h>

# define PROGRAM_NAME "Cub3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 640

# define PI 3.14159265358979323846f
# define ROTATION_SPEED 0.11
# define FOV PI / 1.8
# define RAY_NUM WIN_WIDTH
# define RAY_INCREMENT FOV / RAY_NUM

# define SKY_COLOR 0x0000FF
# define GROUND_COLOR 0x964B00

//# define PROFILER
# ifdef PROFILER
#  include <time.h>
# endif

# define PROJECTION_PLANE_DISTANCE (WIN_WIDTH) / tan(FOV / 2)

enum	e_player_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct t_player
{
	t_v2	pos;
	double	angle;
}	t_player;

typedef struct t_imgbuffer
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imgbuffer;

typedef struct t_windata
{
	void		*mlx;
	void		*mlx_win;
	t_imgbuffer	win_buffer;
	t_sprites	sprites;
	t_player	player;
}	t_windata;

void	drawMap(t_windata *windata, t_sprites *sprites);
void	drawScreen(t_windata *windata);

void	init_event_handlers(t_windata *windata);
void	close_win(t_windata *windata);

//  Render 
// 	 \	draw.c
void	line(t_windata *windata, int color, t_v2 start, t_v2 end);
void	pixel(t_windata *windata, int color, t_v2 pos);
void	pixel_to_buffer(t_windata *windata, int color, t_v2 pos, bool only_if_0);
void    square(t_windata *windata, int color, t_v2 center, int side_length, float angle);
void	rect(t_windata *windata, int color, t_v2 start, t_v2 end);
void	clear_window(t_windata *windata);
void	clear_buffer(t_imgbuffer *buffer);

//  Player
bool	move_player(t_player *player, enum e_player_direction dir);
bool	rotate_player(t_player *player, enum e_player_direction dir);

//  Raycasting
t_v3f	raycast(t_windata *windata, int map[][10], double angle);


#endif