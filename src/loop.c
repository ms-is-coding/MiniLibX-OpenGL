/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:34:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/14 22:38:31 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "mlx.h"

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

static void	render_frame(t_mlx *mlx, t_window *win)
{
	const int		curr_id = win->pbo_index;
	const int		next_id = (win->pbo_index + 1) % 2;
	const size_t	size = win->width * win->height * 4;

	memcpy(win->pbo_ptrs[curr_id], win->pixel_buffer, size);
	glXMakeCurrent(mlx->dpy, win->xwin, mlx->glc);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, win->pbo_ids[curr_id]);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, win->texture_id);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, win->width, win->height,
		GL_BGRA, GL_UNSIGNED_BYTE, 0);
	if (win->fences[curr_id])
		glDeleteSync(win->fences[curr_id]);
	win->fences[curr_id] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	win->pbo_index = next_id;
	if (win->fences[next_id])
	{
		glClientWaitSync(win->fences[next_id],
			GL_SYNC_FLUSH_COMMANDS_BIT, 1000000000);
	}
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
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
	KeySym		keysym;
	int			(*hook_fn)(int, void *);

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
			else if (win && ev.type == KeyPress && win->hooks[KeyPress].hook)
			{
				keysym = XLookupKeysym(&ev.xkey, 0);
				hook_fn = (void *)win->hooks[KeyPress].hook;
				hook_fn((int)keysym, win->hooks[KeyPress].param);
			}
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
