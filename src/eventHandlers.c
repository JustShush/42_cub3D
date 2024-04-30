/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventHandlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:48:28 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/30 21:08:10 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <win.h>

static int	key_press(int keycode, t_windata *windata);
static int	handle_close(t_windata *windata);

void	init_event_handlers(t_windata *windata)
{
	mlx_hook(windata->mlx_win, KeyPress, KeyPressMask, key_press, windata);
	mlx_hook(windata->mlx_win, DestroyNotify, KeyPressMask, handle_close,
		windata);
}

static int	handle_close(t_windata *windata)
{
	close_win(windata);
	return (0);
}

static int	key_press(int keycode, t_windata *windata)
{
	(void)windata;
	bool	moved;

	moved = false;
	//printf("keycode: %d\n", keycode);
	if (keycode == K_W || keycode == K_UP)
		moved = move_player(&windata->player, UP);
	else if (keycode == K_A || keycode == K_LEFT)
		moved = rotate_player(&windata->player, LEFT);
	else if (keycode == K_S || keycode == K_DOWN)
		moved = move_player(&windata->player, DOWN);
	else if (keycode == K_D || keycode == K_RIGHT)
		moved = rotate_player(&windata->player, RIGHT);
	else if (keycode == K_PLUS || keycode == K_MINUS)
	{
		if (keycode == K_PLUS)
			moved = player_zoom(&windata->player, PLAYER_ZOOM);
		else
			moved = player_zoom(&windata->player, -PLAYER_ZOOM);
		update_settings(windata);
	}
	else if (keycode == K_ESC)
		close_win(windata);
	if (moved)
		drawMapToScreen(windata);
	return (0);
}

void	close_win(t_windata *windata)
{
	mlx_destroy_window(windata->mlx, windata->mlx_win);
	mlx_destroy_display(windata->mlx);
	free_map(&windata->smap, windata->mlx);
	free(windata->mlx);
	exit(EXIT_SUCCESS);
}
