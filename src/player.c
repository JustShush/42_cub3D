/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:15:03 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/16 15:57:08 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_player(t_player *player, enum e_player_direction dir)
{
	t_v2	new_pos;
	t_v2	vdir;


	if (dir == DOWN)
		vdir = v2from_angle(player->angle, -20);
	else if (dir == UP)
		vdir = v2from_angle(player->angle, +20);
	
	new_pos = v2add(player->pos, vdir);
	/*if (map[(int)new_pos.y][(int)new_pos.x] == 0)*/
	player->pos = new_pos;
}

void	rotate_player(t_player *player, enum e_player_direction dir)
{
	if (dir == LEFT)
		player->angle -= ROTATION_SPEED;
	else if (dir == RIGHT)
		player->angle += ROTATION_SPEED;
	/*while (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	while (player->angle < -2 * PI)
		player->angle += 2 * PI;*/
}
