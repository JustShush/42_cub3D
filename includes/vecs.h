/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:27:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/04/16 21:30:13 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECS_H
# define VECS_H

typedef struct t_v2
{
	int	x;
	int	y;
}	t_v2;

typedef struct t_v2f
{
	double	x;
	double	y;
}	t_v2f;

typedef struct t_v3f
{
	double	x;
	double	y;
	double	z;
}	t_v3f;

t_v2	v2add(t_v2 a, t_v2 b);
t_v2	v2add_scalar(t_v2 a, int scalar);
t_v2f	v2ffrom_angle(double angle);
t_v2	v2from_angle(double angle, int scalar);
t_v2f	v2mul_scalar(t_v2f a, int scalar);
t_v2	rotate_point(t_v2 point, t_v2 center, double angle);

#endif