/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:17:44 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/30 17:40:29 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	image_init(t_window *new)
{
	new->i.buf = mlx_get_data_addr(new->i.p, &new->i.bpp,
			&new->i.size_line, &new->i.end);
	if (new->i.end)
	{
		new->i.indexes[0] = 3;
		new->i.indexes[1] = 2;
		new->i.indexes[2] = 1;
		new->i.indexes[3] = 0;
	}
	else
	{
		new->i.indexes[0] = 0;
		new->i.indexes[1] = 1;
		new->i.indexes[2] = 2;
		new->i.indexes[3] = 3;
	}
}

void	new_window(t_master *master, t_fract_type type, char *type_name)
{
	t_window	*earlier;
	t_window	*new;

	earlier = master->cur;
	new = (t_window *)malloc(sizeof(t_window));
	if (!new)
		fractol_error();
	if (!earlier)
		master->w = new;
	else
		earlier->next = new;
	new->type = type;
	new->name = type_name;
	new->fract_var = init_type(type);
	new->p = mlx_new_window(master->m, WIN_W, WIN_H, type_name);
	new->i.p = mlx_new_image(master->m, WIN_W, WIN_H);
	image_init(new);
	new->next = 0;
	new->i.its = (double *)malloc(sizeof(double) * WIN_W * WIN_H);
	if (!new->i.its)
		fractol_error();
	fract_window(new);
	init_events(new);
	master->windows_active++;
}

void	check_args(int ac, char **av)
{
	t_master	*master;
	void		*m;

	master = get_master();
	m = mlx_init();
	master->m = m;
	while (ac--)
	{
		if (ft_strequ(*av, "mandelbrot"))
			new_window(master, MANDELBROT, *av);
		else if (ft_strequ(*av, "julia"))
			new_window(master, JULIA, *av);
		else if (ft_strequ(*av, "burning_ship"))
			new_window(master, BURNING_SHIP, *av);
		else
			fractol_usage();
		av++;
	}
	if (!master->w)
		fractol_usage();
	mlx_loop(m);
}

int	main(int ac, char **av)
{
	check_args(ac - 1, av + 1);
	fract_loop();
}
