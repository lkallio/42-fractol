/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:48 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/13 13:17:48 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_iteration(double *x, double *y)
{
	y[1] = y[1] * (x[1] + x[1]) + y[0];
	x[1] = x[2] - y[2] + x[0];
	if (x[1] * x[1] == x[2] && y[1] * y[1] == y[2])
		return (1);
	y[2] = y[1] * y[1];
	x[2] = x[1] * x[1];
	return (0);
}

void	mandelbrot_it_init(t_fract *v, double *x, double *y, t_xypair in)
{
	x[0] = get_complex(v->x, v->zoom, in.x);
	y[0] = get_complex(v->y, v->zoom, in.y);
	x[1] = 0;
	y[1] = 0;
	x[2] = 0;
	y[2] = 0;
}
