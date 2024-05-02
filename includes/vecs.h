/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:27:41 by tiagoliv          #+#    #+#             */
/*   Updated: 2024/05/02 15:10:18 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECS_H
# define VECS_H

# include <math.h>

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

// V2

t_v2	v2add(t_v2 a, t_v2 b);
t_v2f	v2fadd(t_v2f a, t_v2f b);
t_v2	v2add_scalar(t_v2 a, int scalar);
t_v2f	v2ffrom_angle(double angle);
t_v2f	v2_to_v2f(t_v2 a);
// V2F

t_v2	v2from_angle(double angle, double scalar);
t_v2f	v2fmul_scalar(t_v2f a, double scalar);

#endif