/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:31:23 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/19 15:49:36 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

// Available image sizes 64 / 128
# define IMG_SIZE 64
# define SPRITES_DIR "sprites/"

# define WALL_PATH "rock_wall.xpm"
# define FLOOR_PATH "wood_floor.xpm"

// Errors
# define ERROR_IMG_SIZE "Invalid sprite size\n"
# define ERROR_LOAD_SPRITE "Failed to load sprite\n"
# define ERROR_LOAD_ADDR "Failed to get image address\n"

# include <stdbool.h>
# include <vecs.h>

typedef struct t_imgbuffer
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imgbuffer;

typedef struct t_sprites
{
	t_imgbuffer	wall;
	t_imgbuffer	floor;
}	t_sprites;

//  Render
bool		load_sprites(void *mlx, t_sprites *sprites);
t_imgbuffer	load_sprite(void *mlx, char *path);
void		unload_sprites(void *mlx, t_sprites *sprites);
void		draw_sprite(void *mlx, void *mlx_win, t_v2 pos, void *sprite);

#endif