/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:31:23 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/15 17:28:34 by tiagoliv         ###   ########.fr       */
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
# define ERROR_LOAD_WALL "Failed to load wall sprite\n"
# define ERROR_LOAD_FLOOR "Failed to load floor sprite\n"
# define ERROR_IMG_SIZE "Invalid sprite size\n"

# include <stdbool.h>
# include <vecs.h>

typedef struct t_sprites
{
	void	*wall;
	void	*floor;
}	t_sprites;

//  Render
bool	load_sprites(void *mlx, t_sprites *sprites);
void	draw_sprite(void *mlx, void *mlx_win, t_v2 pos, void *sprite);

#endif