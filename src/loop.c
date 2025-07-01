/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:34:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/01 17:26:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

int	mlx_loop_hook(t_mlx *mlx, int (*fn)(void *), void *param)
{
	mlx->loop_hook = fn;
	mlx->loop_param = param;
	return (0);
}

int	__mlx_set_win_event_mask(t_mlx *mlx)
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
	return (0);
}

int win_count(t_mlx *mlx)
{
	int i = 0;
	t_window *win = mlx->win_list;
	while (win) { win = win->next; i++; }
	return i;
}

int	mlx_loop(t_mlx *mlx)
{
	XEvent		ev;
	t_window	*win;

	__mlx_set_win_event_mask(mlx);
	mlx->running = 1;
	while (win_count(mlx) && mlx->running)
	{
		while (mlx->running && XPending(mlx->dpy))
		{
			XNextEvent(mlx->dpy, &ev);
			win = mlx->win_list;
			while (win->next && (win->next->xwin != ev.xany.window))
				win = win->next;
			if (win && ev.type == ClientMessage
				&& ev.xclient.message_type == mlx->wm_protocols
				&& ev.xclient.data.l[0] == mlx->wm_delete
				&& win->hooks[DestroyNotify].hook)
				win->hooks[DestroyNotify].hook(win->hooks[DestroyNotify].param);
		}
		XSync(mlx->dpy, False);
		if (mlx->loop_hook)
			mlx->loop_hook(mlx->loop_param);
		// do this for every window
		glXSwapBuffers(mlx->dpy, mlx->win_list->xwin);
	}
	return (0);
}
