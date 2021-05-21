/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:22 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/30 15:49:27 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fract_zoom(t_fract *v, int x, int y, double zoom)
{
	double	x_old;
	double	y_old;

	x_old = (v->x.max - v->x.min) * v->zoom;
	y_old = (v->y.max - v->y.min) * v->zoom;
	v->x.off -= ((double)x / v->x.dim) * (x_old * zoom - x_old);
	v->y.off -= ((double)y / v->y.dim) * (y_old * zoom - y_old);
	v->zoom *= zoom;
}

int	scrollwheel(int b, int x, int y, void *in)
{
	static int		slower = 0;
	t_window		*win;

	win = (t_window *)in;
	if (win->help_displayed || slower++ % ZOOM_STEP)
		return (1);
	x += win->fract_var.x.r_off;
	y += win->fract_var.y.r_off;
	if (b == 5)
		fract_zoom(&win->fract_var, x, y, 0.9);
	else if (b == 4)
		fract_zoom(&win->fract_var, x, y, 1.1);
	else
		return (1);
	fract_window(win);
	return (0);
}

int	julia_c(int x, int y, void *in)
{
	static int		slower = 0;
	t_fract			*v;
	t_window		*win;

	win = (t_window *)in;
	if (win->julia_color_mode)
		return (mouse_color(x, y, in));
	if (win->frozen || win->help_displayed || slower++ % 7)
		return (1);
	v = &win->fract_var;
	v->x.mouse_pos = get_complex(v->x, v->zoom, x);
	v->y.mouse_pos = get_complex(v->y, v->zoom, y);
	fract_window(win);
	return (0);
}

int	mouse_color(int x, int y, void *in)
{
	static int			slower = 0;
	t_color_attr		*v;
	t_window			*win;

	win = (t_window *)in;
	v = &win->fract_var.c;
	if (win->frozen || win->help_displayed || slower++ % 7)
		return (1);
	v->range[0] = (int)((100 * ((float)x / (float)WIN_W))
			+ 100 * ((float)(WIN_H - y) / (float)WIN_H));
	v->range[1] = (int)(100 * ((float)x / (float)WIN_W)
			+ 100 * ((float)y / (float)WIN_H));
	v->range[2] = (int)(100 * ((float)y / (float)WIN_H)
			+ 100 * ((float)(WIN_H - y) / (float)WIN_H)
			+ 100 * ((float)(WIN_W - x) / (float)WIN_W));
	update_fractal(win);
	return (0);
}

void	init_events(t_window *cur)
{
	mlx_hook(cur->p, 4, 4, scrollwheel, (void *)cur);
	mlx_hook(cur->p, 2, 3, key_events, (void *)cur);
	if (cur->type == JULIA)
		mlx_hook(cur->p, 6, (1L << 6), julia_c, (void *)cur);
	else
		mlx_hook(cur->p, 6, (1L << 6), mouse_color, (void *)cur);
}
