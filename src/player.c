/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:15:03 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 17:51:52 by tiagoliv         ###   ########.fr       */
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

bool	player_init(t_player *player, t_v2f pos, char player_dir)
{
	player->pos = (t_v2f){pos.x + 0.5, pos.y + 0.5};
	player->fov = PI / 2;
	player->angle = 0;
	if (!player_set_direction(player, player_dir))
		return (false);
	return (true);
}

bool	player_set_direction(t_player *player, char player_dir)
{
	if (!char_in_set(player_dir, PLAYER_DIRS))
		return (false);
	if (player_dir == 'N')
		player->angle = - PI / 2;
	else if (player_dir == 'E')
		player->angle = 0;
	else if (player_dir == 'S')
		player->angle = PI / 2;
	else if (player_dir == 'W')
		player->angle = PI;
	return (true);
}
