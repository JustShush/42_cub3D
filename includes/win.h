/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:50:07 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/15 15:58:28 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIN_H
# define WIN_H

enum					e_hooking_event
{
	KeyPress = 2,
	DestroyNotify = 17,
};

enum					e_event_mask
{
	NoEventMask = 0L,
	KeyPressMask = (1L << 0)
};

enum					e_key_code
{
	K_W = 119,
	K_A = 97,
	K_S = 115,
	K_D = 100,
	K_UP = 65362,
	K_LEFT = 65361,
	K_DOWN = 65364,
	K_RIGHT = 65363,
	K_ESC = 65307,
};

#endif