/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/15 15:22:14 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#include <mlx.h>

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;

	(void)argc;
	(void)argv;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1620, 880, "Cub3D");
	mlx_loop(mlx);
	free(mlx);
	free(mlx_win);
	return (0);
}
