/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:41:37 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/29 19:15:42 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <img.h>

bool	load_sprites(void *mlx, t_sprites *sprites)
{
	sprites->north.img = load_sprite(mlx, sprites->north.filename);
	if (!sprites->north.img)
		return (false);
	sprites->south.img = load_sprite(mlx, sprites->south.filename);
	if (!sprites->south.img)
		return (false);
	sprites->west.img = load_sprite(mlx, sprites->west.filename);
	if (!sprites->west.img)
		return (false);
	sprites->east.img = load_sprite(mlx, sprites->east.filename);
	if (!sprites->east.img)
		return (false);
	return (true);
}

void	draw_sprite(void *mlx, void *mlx_win, t_v2 pos, void *sprite)
{
	mlx_put_image_to_window(mlx, mlx_win, sprite, pos.x, pos.y);
}

void	*load_sprite(void *mlx, char *filename)
{
	int		width;
	int		height;
	void	*sprite;

	width = 0;
	height = 0;
	printf("loading sprite %s\n", filename);
	sprite = mlx_xpm_file_to_image(mlx, filename, &width, &height);
	if (!sprite)
		return (pe(ERROR_LOAD_WALL), NULL);
	if (width != IMG_SIZE || height != IMG_SIZE)
		return (pe(ERROR_IMG_SIZE), NULL);
	return (sprite);
}
