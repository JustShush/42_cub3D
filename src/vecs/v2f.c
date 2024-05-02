/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2f.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:25:00 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 20:25:25 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vecs.h>

t_v2f	v2ffrom_angle(double angle)
{
	return ((t_v2f){cos(angle), sin(angle)});
}

t_v2f	v2fmul_scalar(t_v2f a, double scalar)
{
	return ((t_v2f){a.x * scalar, a.y * scalar});
}
