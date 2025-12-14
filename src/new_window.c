/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:02:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/14 22:07:09 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "mlx.h"
#include "mlx_internal.h"

static void	*cleanup_window(t_mlx *mlx, t_window *window)
{
	if (mlx->gc)
	{
		XFreeGC(mlx->dpy, mlx->gc);
		mlx->gc = NULL;
	}
	if (mlx->glc)
	{
		glXDestroyContext(mlx->dpy, mlx->glc);
		mlx->glc = NULL;
	}
	if (window->xwin)
		XDestroyWindow(mlx->dpy, window->xwin);
	if (window->pbo_ids[0])
		glDeleteBuffers(2, window->pbo_ids);
	if (window->pixel_buffer)
		free(window->pixel_buffer);
	free(window);
	return (NULL);
}

static bool	init_persistent_pbos(t_window *win)
{
	const size_t	size = win->width * win->height * 4;
	GLbitfield		flags;

	flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
	glGenBuffers(2, win->pbo_ids);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, win->pbo_ids[0]);
	glBufferStorage(GL_PIXEL_UNPACK_BUFFER, size, NULL, flags
		| GL_DYNAMIC_STORAGE_BIT);
	win->pbo_ptrs[0] = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, size, flags);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, win->pbo_ids[1]);
	glBufferStorage(GL_PIXEL_UNPACK_BUFFER, size, NULL, flags
		| GL_DYNAMIC_STORAGE_BIT);
	win->pbo_ptrs[1] = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, size, flags);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	win->pbo_index = 0;
	win->fences[0] = 0;
	win->fences[1] = 0;
	if (!win->pbo_ptrs[0] || !win->pbo_ptrs[1])
		return (false);
	return (true);
}

static bool	create_x11_window(t_mlx *mlx, t_window *window, const int w,
				const int h)
{
	XSetWindowAttributes	swa;

	mlx->cmap = XCreateColormap(mlx->dpy, RootWindow(mlx->dpy, mlx->scr_id),
			mlx->vi->visual, AllocNone);
	swa.border_pixel = BlackPixel(mlx->dpy, mlx->scr_id);
	swa.background_pixel = WhitePixel(mlx->dpy, mlx->scr_id);
	swa.override_redirect = True;
	swa.colormap = mlx->cmap;
	swa.event_mask = 0xFFFFFF;
	window->xwin = XCreateWindow(mlx->dpy, RootWindow(mlx->dpy, mlx->scr_id),
			0, 0, w, h, 0,
			mlx->vi->depth, InputOutput,
			mlx->vi->visual,
			CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
			&swa);
	mlx->swa = swa;
	if (!window->xwin)
		return (false);
	window->width = w;
	window->height = h;
	__mlx_prevent_resize(mlx, window, w, h);
	return (true);
}

static bool	setup_graphic_context(t_mlx *mlx, t_window *window)
{
	XGCValues	xgcv;

	mlx->glc = glXCreateContext(mlx->dpy, mlx->vi, NULL, GL_TRUE);
	if (!mlx->glc)
		return (false);
	xgcv.foreground = -1;
	xgcv.function = GXcopy;
	xgcv.plane_mask = AllPlanes;
	mlx->gc = XCreateGC(mlx->dpy, window->xwin,
			GCFunction | GCPlaneMask | GCForeground, &xgcv);
	if (!mlx->gc)
		return (false);
	if (!glXMakeCurrent(mlx->dpy, window->xwin, mlx->glc))
		return (false);
	glGenTextures(1, &window->texture_id);
	glBindTexture(GL_TEXTURE_2D, window->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, window->width, window->height, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (true);
}

void	*mlx_new_window(t_mlx *mlx, const int width, const int height,
			const char *title)
{
	t_window	*window;

	if (!mlx || width <= 0 || height <= 0 || !title)
		return (NULL);
	window = calloc(1, sizeof(t_window));
	if (!window)
		return (NULL);
	window->pixel_buffer = calloc(width * height, sizeof(int));
	if (!window->pixel_buffer)
		return (cleanup_window(mlx, window));
	if (!create_x11_window(mlx, window, width, height))
		return (cleanup_window(mlx, window));
	if (!setup_graphic_context(mlx, window))
		return (cleanup_window(mlx, window));
	if (!init_persistent_pbos(window))
		return (cleanup_window(mlx, window));
	XStoreName(mlx->dpy, window->xwin, title);
	XSetWMProtocols(mlx->dpy, window->xwin, &(mlx->wm_delete), 1);
	XClearWindow(mlx->dpy, window->xwin);
	XMapRaised(mlx->dpy, window->xwin);
	window->next = mlx->win_list;
	mlx->win_list = window;
	return (window);
}
