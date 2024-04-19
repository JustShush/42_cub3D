/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:15:03 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/19 01:16:02 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	move_player(t_player *player, enum e_player_direction dir)
{
	t_v2f	new_pos;
	t_v2f	vdir;


	if (dir == DOWN)
		vdir = v2fmul_scalar(v2ffrom_angle(player->angle), -MOVEMENT_SPEED);
	else if (dir == UP)
		vdir = v2fmul_scalar(v2ffrom_angle(player->angle), +MOVEMENT_SPEED);
	else
		return (false);

	new_pos = v2fadd(player->pos, vdir);
	player->pos = new_pos;
	return (true);
}

bool	rotate_player(t_player *player, enum e_player_direction dir)
{
	if (dir == LEFT)
		player->angle -= ROTATION_SPEED;
	else if (dir == RIGHT)
		player->angle += ROTATION_SPEED;
	else
		return (false);
	while (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	while (player->angle < -2 * PI)
		player->angle += 2 * PI;
	return (true);
}

bool	player_zoom(t_player *player, double zoom)
{
	player->fov += zoom;
	return (true);
}
