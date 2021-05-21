/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:31 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/29 18:06:48 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	get_complex(t_fvar k, double zoom, int x_y)
{
	return (
		(((double)(x_y + k.r_off) / k.dim)
		* zoom * (k.max - k.min))
		+ k.min + k.off
		);
}

t_master	*get_master(void)
{
	static t_master		*master;

	if (!master)
	{
		master = (t_master *)malloc(sizeof(t_master));
		if (!master)
			fractol_error();
		*master = (t_master){0};
	}
	return (master);
}

t_window	*get_cur(void)
{
	return (get_master()->cur);
}

t_img	*get_img(void)
{
	return (&get_cur()->i);
}
