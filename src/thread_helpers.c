/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:19:47 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/30 15:41:57 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*div_rect_thread(void *in)
{
	div_rect(*(t_bounds *)in);
	get_cur()->slow_render = 0;
	return (NULL);
}

void	fract_window_slow(t_window *cur)
{
	static t_master		*master;
	pthread_t			w;

	if (!master)
		master = get_master();
	master->cur = cur;
	ft_bzero(cur->i.buf, sizeof(int) * WIN_W * WIN_H);
	fract_line(cur, &(t_bounds){0, WIN_W - 1, 0, 0});
	fract_line(cur, &(t_bounds){0, WIN_W - 1, WIN_H - 1, WIN_H - 1});
	fract_line(cur, &(t_bounds){0, 0, 0, WIN_H - 1});
	fract_line(cur, &(t_bounds){WIN_W - 1, WIN_W - 1, 0, WIN_H - 1});
	master->threads_active = cur->default_threads_active;
	cur->slow_render = 1;
	pthread_create(&w, NULL, div_rect_thread,
		(void *)&(t_bounds){0, WIN_W - 1, 0, WIN_H - 1});
	while (cur->slow_render)
		put_image(cur);
	put_image(cur);
	pthread_join(w, NULL);
}
