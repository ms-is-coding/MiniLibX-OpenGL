/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:54:10 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/20 15:02:02 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_TYPES_H
# define MLX_TYPES_H

# define MLX_MAX_EVENT 36

# include <stdbool.h>

# include <GL/glx.h>
# include <X11/Xlib.h>

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
	GLsync				fences[2];
	int					*pbo_ptrs[2];
	GLuint				texture_id;
	GLuint				pbo_ids[2];
	int					pbo_index;
	int					width;
	int					height;
	t_hook				hooks[MLX_MAX_EVENT];
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
	XFontStruct				*font;
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

#endif // MLX_TYPES_H
