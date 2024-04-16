/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:41:37 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/15 18:05:45 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <img.h>

bool	load_sprites(void *mlx, t_sprites *sprites)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	sprites->wall = mlx_xpm_file_to_image(mlx,
			SPRITES_DIR WALL_PATH, &width, &height);
	if (!sprites->wall)
		return (perror(ERROR_LOAD_WALL), false);
	if (width != IMG_SIZE || height != IMG_SIZE)
		return (perror(ERROR_IMG_SIZE), false);
	sprites->floor = mlx_xpm_file_to_image(mlx,
			SPRITES_DIR FLOOR_PATH, &width, &height);
	if (!sprites->floor)
		return (perror(ERROR_LOAD_FLOOR), false);
	if (width != IMG_SIZE || height != IMG_SIZE)
		return (perror(ERROR_IMG_SIZE), false);
	return (true);
}

void	draw_sprite(void *mlx, void *mlx_win, t_v2 pos, void *sprite)
{
	mlx_put_image_to_window(mlx, mlx_win, sprite, pos.x, pos.y);
}
