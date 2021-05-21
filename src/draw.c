/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:17 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/30 17:05:48 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	smooth_iteration(double x, double y, int it)
{
	return (it + 1 - log(log(sqrt(x + y))) / log(2));
}

void	set_pix(int x, int y, int color)
{
	int		*img;

	img = (int *)get_img()->buf;
	img[x + y * WIN_W] = color;
}

int	pick_col(double it)
{
	t_fract			cur;
	t_color_attr	a;
	t_color			c;
	int				*i;

	i = get_cur()->i.indexes;
	cur = get_cur()->fract_var;
	c.number = 0;
	c.channels[i[3]] = (unsigned char)0xff;
	if (it == cur.max_it)
		return (c.number);
	a = cur.c;
	c.channels[i[0]] = (unsigned char)(sin(a.freq[0]
				* it + a.phsr[0]) * (a.range[0] % 255) + (a. min[0] % 255));
	c.channels[i[1]] = (unsigned char)(sin(a.freq[1]
				* it + a.phsr[1]) * (a.range[1] % 255) + (a. min[1] % 255));
	c.channels[i[2]] = (unsigned char)(sin(a.freq[2]
				* it + a.phsr[2]) * (a.range[2] % 255) + (a. min[2] % 255));
	return (c.number);
}
