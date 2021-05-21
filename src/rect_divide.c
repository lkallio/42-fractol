/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_divide.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:56 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/30 12:16:28 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_rect(int x_left, int x_right, int y_top, int y_bot)
{
	t_img	*i;
	int		x;
	int		y;
	int		col;
	double	it;

	i = get_img();
	col = ((int *)i->buf)[x_left + y_top * WIN_W];
	it = i->its[x_left + y_top * WIN_W];
	y = y_top - 1;
	while (++y <= y_bot)
	{
		x = x_left - 1;
		while (++x <= x_right)
		{
			i->its[x + y * WIN_W] = it;
			set_pix(x, y, col);
		}
	}
}

void	*fract_rect(void *param)
{
	int			*v;

	v = (int *)param;
	if (v[1] - v[0] < 2 || v[3] - v[2] < 2)
		return (NULL);
	if (check_rect(v[0], v[1], v[2], v[3]))
		div_rect((t_bounds){v[0], v[1], v[2], v[3]});
	else
		fill_rect(v[0], v[1], v[2], v[3]);
	return (NULL);
}

int	check_rect(int x_left, int x_right, int y_top, int y_bot)
{
	double			*its;
	double			it;
	int				x_i;
	int				y_i;

	its = get_img()->its;
	it = its[x_left + y_top * WIN_W];
	x_i = x_left - 1;
	y_i = y_top - 1;
	while (++x_i <= x_right)
	{
		if (its[x_i + y_top * WIN_W] != it
			|| its[x_i + y_bot * WIN_W] != it)
			return (1);
	}
	while (++y_i <= y_bot)
	{
		if (its[x_left + y_i * WIN_W] != it
			|| its[x_right + y_i * WIN_W] != it)
			return (1);
	}
	return (0);
}

void	run_threads(t_bounds v, int x_mid, int y_mid)
{
	static pthread_attr_t	attrs;
	static int				is_set;
	pthread_t				w[4];

	if (!is_set && ++is_set)
	{
		pthread_attr_init(&attrs);
		pthread_attr_setstacksize(&attrs, THREAD_STACK);
	}
	if (pthread_create(&w[0], &attrs, fract_rect,
			(void *)(int [4]){v.x_left, x_mid, v.y_top, y_mid})
		|| pthread_create(&w[1], &attrs, fract_rect,
		(void *)(int [4]){x_mid, v.x_right, v.y_top, y_mid})
		|| pthread_create(&w[2], &attrs, fract_rect,
		(void *)(int [4]){v.x_left, x_mid, y_mid, v.y_bot})
		|| pthread_create(&w[3], &attrs, fract_rect,
		(void *)(int [4]){x_mid, v.x_right, y_mid, v.y_bot}))
		fractol_error();
	get_master()->threads_active += 4;
	pthread_join(w[0], NULL);
	pthread_join(w[1], NULL);
	pthread_join(w[2], NULL);
	pthread_join(w[3], NULL);
	get_master()->threads_active -= 4;
}

void	*div_rect(t_bounds v)
{
	int			x_mid;
	int			y_mid;

	x_mid = (int)(0.5 * (double)(v.x_left + v.x_right));
	y_mid = (int)(0.5 * (double)(v.y_top + v.y_bot));
	fract_line(get_cur(),
		&(t_bounds){v.x_left + 1, v.x_right - 1, y_mid, y_mid});
	fract_line(get_cur(),
		&(t_bounds){x_mid, x_mid, v.y_top + 1, v.y_bot - 1});
	if (get_cur()->slow_render)
		usleep(100);
	if (get_master()->threads_active < MAX_THREADS)
		run_threads(v, x_mid, y_mid);
	else
	{
		fract_rect((void *)(int [4]){v.x_left, x_mid, v.y_top, y_mid});
		fract_rect((void *)(int [4]){x_mid, v.x_right, v.y_top, y_mid});
		fract_rect((void *)(int [4]){v.x_left, x_mid, y_mid, v.y_bot});
		fract_rect((void *)(int [4]){x_mid, v.x_right, y_mid, v.y_bot});
	}
	return (NULL);
}
