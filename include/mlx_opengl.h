/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_opengl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:37:24 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/10 20:48:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_OPENGL_H
# define MLX_OPENGL_H

# include <stdlib.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <GL/gl.h>
# include <GL/glx.h>

typedef struct s_mlx
{
	Window					root;
	Window					win;
	Colormap				cmap;
	XSetWindowAttributes	swa;
	XWindowAttributes		gwa;
	GLXContext				glc;
	int						scr_id;
	int						running;
	Display					*dpy;
	Screen					*scr;
	XVisualInfo				*vi;
	int						(*loop_hook)(void *);
	void					*loop_param;
}	t_mlx;

t_mlx	*mlx_init(void);
void	*mlx_new_window(t_mlx *mlx, int width, int height, const char *title);

int		mlx_pixel_put(t_mlx *mlx, void *win, int x, int y, uint32_t color);

int		mlx_loop_hook(t_mlx *mlx, int (*fn)(void *), void *param);
int		mlx_loop(t_mlx *mlx);

int		mlx_destroy_window(t_mlx *mlx, void *win);
int		mlx_destroy_display(t_mlx *mlx);

int		__mlx_init_display(t_mlx *mlx);
int		__mlx_glx_check_version(t_mlx *mlx);
int		__mlx_init_opengl(t_mlx *mlx);
int		__mlx_get_visual(t_mlx *mlx);
void	__mlx_prevent_resize(t_mlx *mlx, int width, int height);

#endif
