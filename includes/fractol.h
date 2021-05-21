#ifndef FRACTOL_H
# define FRACTOL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include "libft.h"
# include <pthread.h>
# include <math.h>
# include <png.h>
# include <sys/stat.h>
# include <time.h>

# define WIN_W		1200
# define WIN_H		800

# define X_I		0
# define Y_I		1

# define DEFAULT_MAX_JULIA		32
# define DEFAULT_MAX_MANDELBROT	1000
# define DEFAULT_MAX_BS			50

# define MAX_THREADS			16
# define THREAD_STACK			0x1000
# define ZOOM_STEP				7

# define XK_S		0x0073
# define XK_W		0x0077
# define XK_A		0x0061
# define XK_B		0x0062
# define XK_D		0x0064
# define XK_ESCAPE	0xff1b
# define XK_H		0x0068
# define XK_Z		0x007a
# define XK_X		0x0078
# define XK_C		0x0063
# define XK_V		0x0076
# define XK_N		0x006e
# define XK_M		0x006d
# define XK_F		0x0066
# define XK_G		0x0067

typedef union u_color
{
	unsigned int	number;
	unsigned char	channels[4];
}	t_color;

typedef struct s_bounds
{
	int			x_left;
	int			x_right;
	int			y_top;
	int			y_bot;
}				t_bounds;

typedef struct s_xypair
{
	int			x;
	int			y;
}				t_xypair;

typedef enum e_fract_type {MANDELBROT, JULIA, BURNING_SHIP}	t_fract_type;

typedef struct s_color_attr
{
	double			freq[3];
	double			phsr[3];
	int				range[3];
	int				min[3];
}				t_color_attr;

typedef struct s_fvar
{
	double		min;
	double		max;
	double		off;
	int			r_off;
	double		mouse_pos;
	int			dim;
}				t_fvar;

typedef struct s_fract
{
	t_fvar			x;
	t_fvar			y;
	double			zoom;
	t_color_attr	c;
	int				max_it;
	int				(*iteration)(double *, double *);
	void			(*iteration_init)(struct s_fract *,
						double *, double *, t_xypair);
}				t_fract;

typedef struct s_img
{
	double		*its;
	void		*p;
	char		*buf;
	int			indexes[4];
	int			end;
	int			bpp;
	int			size_line;
}				t_img;

typedef struct s_window
{
	void			*p;
	t_img			i;
	t_fract_type	type;
	char			*name;
	t_fract			fract_var;
	struct s_window	*next;
	int				default_threads_active;
	int				images_created;
	unsigned frozen : 1;
	unsigned help_displayed : 1;
	unsigned julia_color_mode : 1;
	unsigned no_smooth_coloring : 1;
	unsigned slow_render : 1;
	unsigned record : 1;
	unsigned new_dir : 1;
}				t_window;

typedef struct s_master
{
	void			*m;
	t_window		*w;
	t_window		*cur;
	int				threads_active;
	int				windows_active;
}				t_master;

int			bs_iteration(double *x, double *y);

void		set_pix(int x, int y, int color);
int			pick_col(double it);
double		smooth_iteration(double x, double y, int it);

double		get_complex(t_fvar k, double zoom, int x_y);
void		fract_iterate(t_window *cur, t_xypair in);
void		fract_line(t_window *cur, t_bounds *v);
void		fract_window(t_window *cur);

t_master	*get_master(void);
t_window	*get_cur(void);
t_img		*get_img(void);

t_fract		init_bs(void);
t_fract		init_julia(void);
t_fract		init_mandelbrot(void);
t_fract		init_type(t_fract_type type);

int			julia_iteration(double x[3], double y[3]);
void		julia_it_init(t_fract *v, double *x, double *y, t_xypair in);

void		new_window(t_master *master, t_fract_type type, char *type_name);
void		check_args(int ac, char **av);
int			main(int ac, char **av);

int			mandelbrot_iteration(double *x, double *y);
void		mandelbrot_it_init(t_fract *v, double *x, double *y, t_xypair in);

void		fractol_error(void);
void		fractol_usage(void);

void		fill_rect(int x_left, int x_right, int y_top, int y_bot);
void		*fract_rect(void *param);
int			check_rect(int x_left, int x_right, int y_top, int y_bot);
void		run_threads(t_bounds v, int x_mid, int y_mid);
void		*div_rect(t_bounds v);
void		update_fractal(t_window *win);

void		fract_loop(void);

int			scrollwheel(int b, int x, int y, void *win);
void		fract_zoom(t_fract *v, int x, int y, double zoom);
void		init_events(t_window *cur);
int			julia_c(int x, int y, void *win);
int			mouse_color(int x, int y, void *win);

int			key_events(int key, void *win);
void		key_events_stupid_norminette(int key, void *in);

void		fract_window_slow(t_window *cur);
void		move_fractal(int key, t_fract *fract);

void		make_image(t_window *win);
void		put_image(t_window *win);
void		record(t_window *win);
void		toggle_help(void);
void		escape_event(void);
void		mul_double3(double *v, double muller);

#endif
