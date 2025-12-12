/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:34:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 14:59:40 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_loop_hook(t_mlx *mlx, int (*fn)(void *), void *param)
{
	mlx->loop_hook = fn;
	mlx->loop_param = param;
	return (0);
}

static void	mlx_set_win_event_mask(t_mlx *mlx)
{
	t_window				*win;
	int						i;
	XSetWindowAttributes	xswa;

	win = mlx->win_list;
	while (win)
	{
		xswa.event_mask = 0;
		i = LASTEvent;
		while (i--)
			xswa.event_mask |= win->hooks[i].mask;
		XChangeWindowAttributes(mlx->dpy, win->xwin, CWEventMask, &xswa);
		win = win->next;
	}
}

static int	win_count(t_mlx *mlx)
{
	int			i;
	t_window	*win;

	i = 0;
	win = mlx->win_list;
	while (win)
	{
		win = win->next;
		i++;
	}
	return (i);
}

static void	render_frame(t_mlx *mlx, t_window *window)
{
	glXMakeCurrent(mlx->dpy, window->xwin, mlx->glc);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, window->texture_id);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, window->width, window->height,
		GL_BGRA, GL_UNSIGNED_BYTE, window->pixel_buffer);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

int	mlx_loop(t_mlx *mlx)
{
	XEvent		ev;
	t_window	*win;

	mlx_set_win_event_mask(mlx);
	mlx->running = true;
	while (win_count(mlx) && mlx->running)
	{
		while (mlx->running && XPending(mlx->dpy))
		{
			XNextEvent(mlx->dpy, &ev);
			win = mlx->win_list;
			while (win && (win->xwin != ev.xany.window))
				win = win->next;
			if (win && ev.type == ClientMessage
				&& ev.xclient.message_type == mlx->wm_protocols
				&& (unsigned long)ev.xclient.data.l[0] == mlx->wm_delete
				&& win->hooks[DestroyNotify].hook)
				win->hooks[DestroyNotify].hook(win->hooks[DestroyNotify].param);
			else if (win && win->hooks[ev.type].hook)
				win->hooks[ev.type].hook(win->hooks[ev.type].param);
		}
		if (mlx->loop_hook)
			mlx->loop_hook(mlx->loop_param);
		win = mlx->win_list;
		while (win)
		{
			if (win->pixel_buffer)
			{
				render_frame(mlx, win);
				glXSwapBuffers(mlx->dpy, win->xwin);
			}
			win = win->next;
		}
	}
	return (0);
}
