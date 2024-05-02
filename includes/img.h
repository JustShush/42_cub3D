/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:31:23 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 16:06:41 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# define IMG_SIZE 512
# define SPRITES_DIR "sprites/"
# define IMG_FORMAT_EXT ".xpm"

// Errors
# define ERROR_IMG_SIZE "Invalid sprite size\n"
# define ERROR_LOAD_SPRITE "Failed to load sprite\n"
# define ERROR_LOAD_ADDR "Failed to get image address\n"
# define INVALID_SPRITE_EXT "Invalid sprite format\n"

# include <stdbool.h>

typedef struct t_imgbuffer
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imgbuffer;

typedef struct t_sprite
{
	t_imgbuffer	img;
	char		*filename;
}	t_sprite;

typedef struct t_sprites
{
	t_sprite	north;
	t_sprite	south;
	t_sprite	west;
	t_sprite	east;
	int			ceiling;
	int			floor;
}	t_sprites;

//  Render
bool		load_sprites(void *mlx, t_sprites *sprites);
void		unload_sprites(void *mlx, t_sprites *sprites);
t_imgbuffer	load_sprite(void *mlx, char *filename);

#endif