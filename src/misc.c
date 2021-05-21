/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:51 by lkallio           #+#    #+#             */
/*   Updated: 2021/05/02 20:39:14 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fract_loop(void)
{
	mlx_loop(get_master()->m);
	exit(0);
}

void	put_image(t_window *win)
{
	static t_master *master;

	if (!master)
		master = get_master();
	mlx_put_image_to_window(master->m, win->p, win->i.p, 0, 0);
	if (win->record)
		record(win);
}

void	fractol_error(void)
{
	if (errno)
		strerror(errno);
	exit(0);
}

void	fractol_usage(void)
{
	ft_printf("usage: ./fractol [fractal1 [fractal2 ...]]\n\
	available fractals:\n\
	  - mandelbrot\n\
	  - julia\n\
	  - burning_ship\n\
NOTE: Press [h] to view controls\n");
	fractol_error();
}

void	mul_double3(double *v, double muller)
{
	v[0] *= muller;
	v[1] *= muller;
	v[2] *= muller;
}
