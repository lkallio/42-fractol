#include "fractol.h"

static void	do_stuff(char *buf, FILE *fp, png_structp png, png_infop info)
{
	static png_byte	**png_rows;
	int			y;

	if (!png_rows)
	{
		png_rows = png_malloc(png, WIN_H * sizeof(png_byte *));
		y = -1;
		while (++y < WIN_H)
			png_rows[y] = png_malloc(png, WIN_W * 4);
	}
	y = -1;
	while (++y < WIN_H)
		memmove(png_rows[y], buf + y * WIN_W * 4, WIN_W * 4);
	png_init_io(png, fp);
	png_set_rows(png, info, png_rows);
	png_write_png(png, info, PNG_TRANSFORM_BGR, NULL);
}

static void	save_img_to_file(char *buf, char *path)
{
	FILE		*fp;
	png_structp	png;
	png_infop	info;

	fp = fopen(path, "w");
	png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info = png_create_info_struct (png);
	png_set_IHDR (png, info, WIN_W, WIN_H, 8,
		PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	do_stuff(buf, fp, png, info);
	png_destroy_write_struct(&png, &info);
}

static char	*get_dir(void)
{
	static int	dir_made;
	static char	*dir_name = "captures";

	if (!dir_made && ++dir_made)
		mkdir(dir_name, 0700);
	return (dir_name);
}

void	make_image(t_window *win)
{
	char		file_path[1024];

	ft_sprintf(file_path, "%s/%s_%d.png", get_dir(),
		win->name, (int)time(NULL) % 10000);
	save_img_to_file(win->i.buf, file_path);
}

void	record(t_window *win)
{
	static char	*dir_name[3];
	char		file_path[1024];

	if (win->new_dir && win->new_dir--)
	{
		win->images_created = 0;
		ft_sprintf(file_path, "%s/%s_recording_%d", get_dir(),
			win->name, (int)time(NULL) % 10000);
		dir_name[win->type] = ft_strdup(file_path);
		mkdir(file_path, 0700);
	}
	ft_sprintf(file_path, "%s/%03d.png", dir_name[win->type],
		win->images_created++);
	save_img_to_file(win->i.buf, file_path);
}
