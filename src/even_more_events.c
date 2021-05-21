#include "fractol.h"

void	move_fractal(int key, t_fract *fract)
{
	if (key == XK_S)
		fract->y.r_off += 20;
	else if (key == XK_W)
		fract->y.r_off -= 20;
	else if (key == XK_A)
		fract->x.r_off -= 20;
	else if (key == XK_D)
		fract->x.r_off += 20;
}

void	escape_event(void)
{
	t_master	*m;

	m = get_master();
	mlx_destroy_window(m->m, m->cur->p);
	if (!--m->windows_active)
		exit(0);
}