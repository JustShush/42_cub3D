/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:41:37 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/22 20:01:07 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <img.h>

bool	load_sprites(void *mlx, t_sprites *sprites)
{
	sprites->wall = load_sprite(mlx, SPRITES_DIR WALL_PATH);
	if (!sprites->wall.img || !sprites->wall.addr)
		return (unload_sprites(mlx, sprites), false);
	sprites->wall2 = load_sprite(mlx, SPRITES_DIR WALL2_PATH);
	if (!sprites->wall2.img || !sprites->wall.addr)
		return (unload_sprites(mlx, sprites), false);
	sprites->wall3 = load_sprite(mlx, SPRITES_DIR WALL3_PATH);
	if (!sprites->wall3.img || !sprites->wall.addr)
		return (unload_sprites(mlx, sprites), false);
	sprites->wall4 = load_sprite(mlx, SPRITES_DIR WALL4_PATH);
	if (!sprites->wall4.img || !sprites->wall.addr)
		return (unload_sprites(mlx, sprites), false);
	return (true);
}

t_imgbuffer	load_sprite(void *mlx, char *path)
{
	t_imgbuffer	sprite;
	int			width;
	int			height;

	ft_memset(&sprite, 0, sizeof(t_imgbuffer));
	width = 0;
	height = 0;
	sprite.img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!sprite.img)
		return (perror(ERROR_LOAD_SPRITE), sprite);
	if (width != IMG_SIZE || height != IMG_SIZE)
		return (perror(ERROR_IMG_SIZE), sprite);
	sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel,
			&sprite.line_length, &sprite.endian);
	if (!sprite.addr)
		return (perror(ERROR_LOAD_ADDR), sprite);
	return (sprite);
}

void	unload_sprites(void *mlx, t_sprites *sprites)
{
	mlx_destroy_image(mlx, sprites->wall.img);
	mlx_destroy_image(mlx, sprites->wall2.img);
	mlx_destroy_image(mlx, sprites->wall3.img);
	mlx_destroy_image(mlx, sprites->wall4.img);
}

void	draw_sprite(void *mlx, void *mlx_win, t_v2 pos, void *sprite)
{
	mlx_put_image_to_window(mlx, mlx_win, sprite, pos.x, pos.y);
}
