/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:41:37 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 20:19:39 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <img.h>

bool	load_sprites(void *mlx, t_sprites *sprites)
{
	sprites->north.img = load_sprite(mlx, sprites->north.filename);
	if (!sprites->north.img.img)
		return (false);
	sprites->south.img = load_sprite(mlx, sprites->south.filename);
	if (!sprites->south.img.img)
		return (false);
	sprites->west.img = load_sprite(mlx, sprites->west.filename);
	if (!sprites->west.img.img)
		return (false);
	sprites->east.img = load_sprite(mlx, sprites->east.filename);
	if (!sprites->east.img.img)
		return (false);
	return (true);
}

void	unload_sprites(void *mlx, t_sprites *sprites)
{
	if (sprites->north.img.img)
		mlx_destroy_image(mlx, sprites->north.img.img);
	if (sprites->north.filename)
		free(sprites->north.filename);
	if (sprites->south.img.img)
		mlx_destroy_image(mlx, sprites->south.img.img);
	if (sprites->south.filename)
		free(sprites->south.filename);
	if (sprites->west.img.img)
		mlx_destroy_image(mlx, sprites->west.img.img);
	if (sprites->west.filename)
		free(sprites->west.filename);
	if (sprites->east.img.img)
		mlx_destroy_image(mlx, sprites->east.img.img);
	if (sprites->east.filename)
		free(sprites->east.filename);
}

t_imgbuffer	load_sprite(void *mlx, char *filename)
{
	t_imgbuffer	sprite;
	int			width;	
	int			height;

	ft_memset(&sprite, 0, sizeof(t_imgbuffer));
	width = 0;
	height = 0;
	sprite.img = mlx_xpm_file_to_image(mlx, filename, &width, &height);
	if (!sprite.img)
		return (pe(ERROR_LOAD_SPRITE), sprite);
	if (width != IMG_SIZE || height != IMG_SIZE)
	{
		mlx_destroy_image(mlx, sprite.img);
		sprite.img = NULL;
		return (pe(ERROR_IMG_SIZE), sprite);
	}
	sprite.addr = mlx_get_data_addr(sprite.img,
			&sprite.bits_per_pixel,
			&sprite.line_length,
			&sprite.endian);
	return (sprite);
}
