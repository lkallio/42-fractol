/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:27 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/30 15:12:05 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fract_iterate(t_window *cur, t_xypair in)
{
	static int			max_it;
	int					it;
	double				smooth_it;
	double				x[3];
	double				y[3];

	if (max_it != cur->fract_var.max_it)
		max_it = cur->fract_var.max_it;
	cur->fract_var.iteration_init(&cur->fract_var, x, y, in);
	it = -1;
	while (x[2] + y[2] < 4 && ++it < max_it)
	{
		if (cur->fract_var.iteration(x, y))
		{
			it = max_it;
			break ;
		}
	}
	if (!cur->no_smooth_coloring && it < max_it)
		smooth_it = smooth_iteration(x[2], y[2], it);
	else
		smooth_it = it;
	cur->i.its[in.x + in.y * WIN_W] = smooth_it;
	set_pix(in.x, in.y, pick_col(smooth_it));
}

void	fract_line(t_window *cur, t_bounds *v)
{
	if (v->x_left == v->x_right)
		while (v->y_top <= v->y_bot)
			fract_iterate(cur, (t_xypair){v->x_left, v->y_top++});
	else
		while (v->x_left <= v->x_right)
			fract_iterate(cur, (t_xypair){v->x_left++, v->y_top});
}

void	fract_window(t_window *cur)
{
	static t_master		*master;

	if (!master)
		master = get_master();
	master->cur = cur;
	fract_line(cur, &(t_bounds){0, WIN_W - 1, 0, 0});
	fract_line(cur, &(t_bounds){0, WIN_W - 1, WIN_H - 1, WIN_H - 1});
	fract_line(cur, &(t_bounds){0, 0, 0, WIN_H - 1});
	fract_line(cur, &(t_bounds){WIN_W - 1, WIN_W - 1, 0, WIN_H - 1});
	master->threads_active = cur->default_threads_active;
	div_rect((t_bounds){0, WIN_W - 1, 0, WIN_H - 1});
	put_image(cur);
}

void	*redraw_box(void *in)
{
	int		*v;
	t_img	*i;
	int		x;
	int		y;

	v = (int *)in;
	i = get_img();
	x = v[0];
	while (x <= v[1])
	{
		y = v[2];
		while (y <= v[3])
		{
			set_pix(x, y, pick_col(i->its[x + y * WIN_W]));
			y++;
		}
		x++;
	}
	return (NULL);
}

void	update_fractal(t_window *win)
{
	pthread_t	w[4];
	int			i;

	get_master()->cur = win;
	pthread_create(&w[0], NULL, redraw_box,
		(void *)(int [4]){0, WIN_W / 2, 0, WIN_H / 2});
	pthread_create(&w[1], NULL, redraw_box,
		(void *)(int [4]){WIN_W / 2 + 1, WIN_W - 1, 0, WIN_H / 2});
	pthread_create(&w[2], NULL, redraw_box,
		(void *)(int [4]){0, WIN_W / 2, WIN_H / 2 + 1, WIN_H - 1});
	pthread_create(&w[3], NULL, redraw_box,
		(void *)(int [4]){WIN_W / 2 + 1, WIN_W - 1,
		WIN_H / 2 + 1, WIN_H - 1});
	i = -1;
	while (++i < 4)
		pthread_join(w[i], NULL);
	put_image(win);
}
