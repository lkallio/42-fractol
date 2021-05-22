/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:30:00 by lkallio           #+#    #+#             */
/*   Updated: 2021/05/22 13:38:02 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_text_cont(t_master *master)
{
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 140, 0xffccdd,
		"[w][a][s][d]: move fractal");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 160, 0xffccdd,
		"[v]: toggle multithreading");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 180, 0xffccdd,
		"[b]: render one frame slowly");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 200, 0xffccdd,
		"[n]: save frame to images");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 220, 0xffccdd,
		"[m]: save each frame to images (record image sequence)");
	if (!master->cur->record)
		return ;
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 240, 0xff0000,
		"recording is on");
}

static void	print_text(t_master *master)
{
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4, 0xffccdd, "fractol");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 40, 0xffccdd, "[esc]: exit");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 60, 0xffccdd, "[z]: freeze image");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 80, 0xffccdd,
		"[x]: switch between mouse modes (julia)");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 100, 0xffccdd,
		"[c]: toggle smooth coloring on/off");
	mlx_string_put(master->m, master->cur->p,
		WIN_W / 2 - 100, WIN_H / 4 + 120, 0xffccdd,
		"[f][g]: increase/decrease color frequency parameter");
	print_text_cont(master);
}

void	toggle_help(void)
{
	static t_master	*master;

	if (!master)
		master = get_master();
	if (!master->cur->help_displayed)
	{
		mlx_clear_window(master->m, master->cur->p);
		print_text(master);
		master->cur->help_displayed = 1;
	}
	else
	{
		mlx_put_image_to_window(master->m,
			master->cur->p, master->cur->i.p, 0, 0);
		master->cur->help_displayed = 0;
	}
}

static int	key_events_cont(int key, t_window *win)
{
	if (key == XK_X)
		win->julia_color_mode = !win->julia_color_mode;
	else if (key == XK_V)
		win->default_threads_active = !win->default_threads_active * 16;
	else if (key == XK_B)
		fract_window_slow(win);
	else if (key == XK_N)
		make_image(win);
	else if (key == XK_C || key == XK_W || key == XK_S
		|| key == XK_A || key == XK_D || key == XK_F
		|| key == XK_G)
	{
		if (key == XK_C)
			win->no_smooth_coloring = !win->no_smooth_coloring;
		else if (key == XK_F)
			mul_double3(win->fract_var.c.freq, 1.1);
		else if (key == XK_G)
			mul_double3(win->fract_var.c.freq, 0.9);
		else
			move_fractal(key, &win->fract_var);
		fract_window(win);
	}
	return (0);
}

int	key_events(int key, void *in)
{
	t_window	*win;

	win = (t_window *)in;
	get_master()->cur = win;
	if (key == XK_ESCAPE)
		escape_event();
	else if (key == XK_H)
		toggle_help();
	else if (key == XK_M)
	{
		win->record = !win->record;
		win->new_dir = 1;
		win->help_displayed = !win->help_displayed;
		toggle_help();
	}
	else if (win->help_displayed)
		return (0);
	else if (key == XK_Z)
		win->frozen = !win->frozen;
	else
		key_events_cont(key, win);
	return (0);
}
