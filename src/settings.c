/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:11:37 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/19 01:12:40 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	update_settings(t_windata	*windata)
{
	windata->settings.projection_plane_distance
		= (WIN_WIDTH / 2) / tan(windata->player.fov / 2);
	windata->settings.ray_increment = windata->player.fov / WIN_WIDTH;
}
