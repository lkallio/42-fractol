/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:39 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/29 18:05:02 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_iteration(double x[3], double y[3])
{
	y[1] = y[1] * (x[1] + x[1]) + y[0];
	x[1] = x[2] - y[2] + x[0];
	if (x[1] * x[1] == x[2] && y[1] * y[1] == y[2])
		return (1);
	y[2] = y[1] * y[1];
	x[2] = x[1] * x[1];
	return (0);
}

void	julia_it_init(t_fract *v, double *x, double *y, t_xypair in)
{
	x[0] = v->x.mouse_pos;
	y[0] = v->y.mouse_pos;
	x[1] = get_complex(v->x, v->zoom, in.x);
	y[1] = get_complex(v->y, v->zoom, in.y);
	x[2] = x[1] * x[1];
	y[2] = y[1] * y[1];
}
