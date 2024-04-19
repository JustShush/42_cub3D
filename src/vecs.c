/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:11:48 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/19 00:31:33 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vecs.h>
#include <math.h>
#include <stdio.h>

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

t_v2f	v2ffrom_angle(double angle)
{
	return ((t_v2f){cos(angle), sin(angle)});
}

t_v2	v2from_angle(double angle, double scalar)
{
	t_v2f	v;

	v = v2ffrom_angle(angle);
	v = v2fmul_scalar(v, scalar);
	return ((t_v2){v.x, v.y});
}

t_v2f	v2fmul_scalar(t_v2f a, double scalar)
{
	return ((t_v2f){a.x * scalar, a.y * scalar});
}

t_v2f	v2_to_v2f(t_v2 a)
{
	return ((t_v2f){a.x, a.y});
}

t_v2	rotate_point(t_v2 point, t_v2 center, double angle)
{
	double	s;
	double	c;
	double	xnew;
	double	ynew;

	s = sin(angle);
	c = cos(angle);
	// translate point back to origin:
	point.x -= center.x;
	point.y -= center.y;
	// rotate point
	xnew = point.x * c - point.y * s;
	ynew = point.x * s + point.y * c;
	// translate point back:
	point.x = xnew + center.x;
	point.y = ynew + center.y;
	return (point);
}
