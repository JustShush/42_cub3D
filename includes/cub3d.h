/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:40 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/28 19:38:01 by dimarque         ###   ########.fr       */
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

typedef struct t_RGB
{
	int	r;
	int	g;
	int	b;
}				t_RGB;

typedef struct t_textures
{
	t_RGB	*c;
	t_RGB	*f;
}				t_textures;

typedef struct t_map
{
	char		**file; // the entire map file
	char		**map; // just the map
	int			y; // height of the map
	t_textures	textures;
	int			c_texture; // cealing texture count
	int			f_texture; // floor texture count
}	t_map;


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
	int		ceiling_color;
	int		floor_color;
}	t_settings;

typedef struct t_windata
{
	void		*mlx;
	void		*mlx_win;
	t_imgbuffer	win_buffer;
	t_sprites	sprites;
	t_minimap	minimap;
	t_player	player;
	t_settings	settings;
	char		*input;
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
void	clear_buffer(t_imgbuffer *buffer);

//  Player
bool	move_player(t_player *player, enum e_player_direction dir);
bool	rotate_player(t_player *player, enum e_player_direction dir);
bool	player_zoom(t_player *player, double zoom);

//  Raycasting
t_v3f	raycast(t_windata *windata, int map[][10], double angle);

//  Minimap
void	draw_minimap(t_windata *windata, int map[][10]);
void	draw_minimap_ray(t_windata *windata, t_v3f rayInter);

//  Settings
void	update_settings(t_windata	*windata);



// -------
char	**map_init(char *file);
char	**copy_array(char **arr);
int		get_start_map(char **map);
int		first_str(char *s1, char *s2);

// map folder
// check.c
int		check_map_closed(t_map map, char **bmap);
int		check_chars(char **map);
int	check_valid_color(t_textures textures);
int		check_color(char *line, char **color);
int		check_double_map(t_map map);
// textures.c
int		get_textures(t_map map);
int		check_textures(t_map map);

// in utils folder
// in map_utils.c
int		get_y(char *file);
int		first_char(char *line, char c);

// in map_utils2.c
char	*ft_chrtrim(char *line, char c);
void	make_null(t_map map, char dir);

int		empty_line(char *line);

// frees
void	free_array(char **arr);

#endif