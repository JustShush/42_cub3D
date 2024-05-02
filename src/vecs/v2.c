/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:11:48 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/01 20:25:41 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vecs.h>

t_v2	v2add(t_v2 a, t_v2 b)
{
	return ((t_v2){a.x + b.x, a.y + b.y});
}

t_v2f	v2fadd(t_v2f a, t_v2f b)
{
	return ((t_v2f){a.x + b.x, a.y + b.y});
}

t_v2	v2add_scalar(t_v2 a, int scalar)
{
	return ((t_v2){a.x + scalar, a.y + scalar});
}

t_v2	v2from_angle(double angle, double scalar)
{
	t_v2f	v;

	v = v2ffrom_angle(angle);
	v = v2fmul_scalar(v, scalar);
	return ((t_v2){v.x, v.y});
}

t_v2f	v2_to_v2f(t_v2 a)
{
	return ((t_v2f){a.x, a.y});
}
