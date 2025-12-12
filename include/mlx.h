/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:37:24 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 17:41:07 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# define MLX_OPENGL

// ReSharper disable CppUnusedIncludeDirective
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# include <GL/gl.h>
# include <GL/glx.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>

typedef struct s_img
{
	int	*buffer;
	int	width;
	int	height;
	int	bpp;
	int	line_len;
	int	endian;
	int	padding;
}	t_img;

typedef struct s_hook
{
	int		(*hook)(void *);
	void	*param;
	int		mask;
	int		padding;
}	t_hook;

typedef struct s_window
{
	struct s_window		*next;
	Window				xwin;
	int					*pixel_buffer;
	GLuint				texture_id;
	int					width;
	int					height;
	int					padding;
	t_hook				hooks[LASTEvent];
}	t_window;

typedef struct s_mlx
{
	Display					*dpy;
	Window					root;
	Screen					*scr;
	t_window				*win_list;
	int						(*loop_hook)(void *);
	void					*loop_param;
	XVisualInfo				*vi;
	Colormap				cmap;
	GLXContext				glc;
	GC						gc;
	Atom					wm_delete;
	Atom					wm_protocols;
	XSetWindowAttributes	swa;
	XWindowAttributes		gwa;
	int						scr_id;
	bool					running;
	char					padding[3];
}	t_mlx;

t_mlx	*mlx_init(void);
void	*mlx_new_window(t_mlx *mlx, int width, int height, const char *title);
int		mlx_clear_window(t_mlx *mlx, t_window *win);
int		mlx_pixel_put(t_mlx *mlx, t_window *win, int x, int y, int color);
void	*mlx_new_image(t_mlx *mlx, int width, int height);
char	*mlx_get_data_addr(void *img_ptr, int *bpp, int *line_len, int *endian);
int		mlx_put_image_to_window(t_mlx *mlx, void *win_ptr, void *img_ptr,
			int x, int y);
int		mlx_get_color_value(t_mlx *mlx, int color);
int		mlx_mouse_hook(t_window *win, int (*fn)(), void *param);
int		mlx_key_hook(t_window *win, int (*fn)(), void *param);
int		mlx_expose_hook(t_window *win, int (*fn)(), void *param);
int		mlx_loop_hook(t_mlx *mlx, int (*fn)(void *), void *param);
int		mlx_loop(t_mlx *mlx);
int		mlx_loop_end(t_mlx *mlx);
int		mlx_string_put(t_mlx *mlx, t_window *win, int x, int y, int color,
			const char *string);
int		mlx_set_font(t_mlx *mlx, t_window *win, const char *name);
void	*mlx_xpm_to_image(t_mlx *mlx, char **xpm_data, int *width, int *height);
void	*mlx_xpm_file_to_image(t_mlx *mlx, char *filename, int *width,
			int *height);
int		mlx_destroy_window(t_mlx *mlx, t_window *win);
int		mlx_destroy_image(t_mlx *mlx, void *img_ptr);
int		mlx_destroy_display(t_mlx *mlx);
int		mlx_hook(t_window *win, int x_event, int x_mask, int (*fn)(),
			void *param);
int		mlx_do_key_autorepeaton(t_mlx *mlx);
int		mlx_do_key_autorepeatoff(t_mlx *mlx);
int		mlx_do_sync(t_mlx *mlx);
int		mlx_mouse_get_pos(t_mlx *mlx, t_window *win, int *x_ptr, int *y_ptr);
int		mlx_mouse_move(t_mlx *mlx, t_window *win, int x, int y);
int		mlx_mouse_hide(t_mlx *mlx, t_window *win);
int		mlx_mouse_show(t_mlx *mlx, t_window *win);
int		mlx_get_screen_size(t_mlx *mlx, int *width, int *height);

int		__mlx_init_display(t_mlx *mlx);
int		__mlx_glx_check_version(t_mlx *mlx);
int		__mlx_init_opengl(t_mlx *mlx);
int		__mlx_get_visual(t_mlx *mlx);
void	__mlx_prevent_resize(t_mlx *mlx, t_window *win, int width, int height);

#endif // MLX_H
