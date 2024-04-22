/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventHandlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:48:28 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/22 20:06:17 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <win.h>

static int	key_press(int keycode, t_windata *windata);
static int	handle_close(t_windata *windata);
static int	mouse_move(int x, int y, t_windata *windata);

void	init_event_handlers(t_windata *windata)
{
	mlx_hook(windata->mlx_win, KeyPress, KeyPressMask, key_press, windata);
	mlx_hook(windata->mlx_win, DestroyNotify, KeyPressMask, handle_close,
		windata);
	mlx_hook(windata->mlx_win, MotionNotify, PointerMotionMask, mouse_move, (void*) windata);
}

static int	handle_close(t_windata *windata)
{
	unload_sprites(windata->mlx, &windata->sprites);
	mlx_destroy_image(windata->mlx, windata->win_buffer.img);
	close_win(windata);
	return (0);
}

static int	key_press(int keycode, t_windata *windata)
{
	if (keycode == K_W || keycode == K_UP)
		move_player(&windata->player, UP);
	else if (keycode == K_A || keycode == K_LEFT)
		move_player(&windata->player, LEFT);
	else if (keycode == K_S || keycode == K_DOWN)
		move_player(&windata->player, DOWN);
	else if (keycode == K_D || keycode == K_RIGHT)
		move_player(&windata->player, RIGHT);
	else if (keycode == K_PLUS || keycode == K_MINUS)
	{
		if (keycode == K_PLUS)
			player_zoom(&windata->player, PLAYER_ZOOM);
		else
			player_zoom(&windata->player, -PLAYER_ZOOM);
		update_settings(windata);
	}
	else if (keycode == K_ESC)
		handle_close(windata);
	return (0);
}

static int	mouse_move(int x, int y, t_windata *windata)
{
	(void)y;
	if (windata->player.mouse_x != -1) {
        int delta_x = x - windata->player.mouse_x;
        double sensitivity = 0.005;
	
		windata->player.angle += delta_x * sensitivity;
        windata->player.angle = fmod(windata->player.angle, 2 * PI);
    }
    windata->player.mouse_x = x;
	return (0);
}

void	close_win(t_windata *windata)
{
	mlx_destroy_window(windata->mlx, windata->mlx_win);
	mlx_destroy_display(windata->mlx);
	free(windata->mlx);
	exit(EXIT_SUCCESS);
}
