/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:35 by lkallio           #+#    #+#             */
/*   Updated: 2021/05/02 20:33:15 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color_attr	init_color_attr(void)
{
	return ((t_color_attr){
		.freq = {0.06, 0.06, 0.06},
		.min = {10, 10, 10},
		.phsr = {0.01, 0.01, 0.01},
		.range = {245, 245, 245}
	});
}

t_fract	init_bs(void)
{
	return ((t_fract){
		.x = {
			.min = -2.5,
			.max = 1.5
		},
		.y = {
			.min = -2.0,
			.max = 1.0
		},
		.c = init_color_attr(),
		.zoom = 1.0,
		.max_it = DEFAULT_MAX_BS,
		.iteration = bs_iteration,
		.iteration_init = mandelbrot_it_init
	});
}

t_fract	init_julia(void)
{
	return ((t_fract){
		.x = {
			.min = -1.5,
			.max = 1.5,
			.mouse_pos = -0.7
		},
		.y = {
			.min = -1.0,
			.max = 1.0,
			.mouse_pos = 0.27015
		},
		.c = init_color_attr(),
		.zoom = 1.0,
		.max_it = DEFAULT_MAX_JULIA,
		.iteration = julia_iteration,
		.iteration_init = julia_it_init
	});
}

t_fract	init_mandelbrot(void)
{
	return ((t_fract){
		.x = {
			.min = -2.0,
			.max = 1.0
		},
		.y = {
			.min = -1.0,
			.max = 1.0
		},
		.c = init_color_attr(),
		.zoom = 1.0,
		.max_it = DEFAULT_MAX_MANDELBROT,
		.iteration = mandelbrot_iteration,
		.iteration_init = mandelbrot_it_init
	});
}

t_fract	init_type(t_fract_type type)
{
	t_fract		ret;

	if (type == MANDELBROT)
		ret = init_mandelbrot();
	else if (type == JULIA)
		ret = init_julia();
	else
		ret = init_bs();
	ret.x.dim = WIN_W;
	ret.y.dim = WIN_H;
	return (ret);
}
