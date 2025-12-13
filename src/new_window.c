/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:02:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/13 20:27:36 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"
#include "mlx_internal.h"

static void	disable_vsync(Display *dpy, Window drawable)
{
	PFNGLXSWAPINTERVALEXTPROC	interval_ext;

	interval_ext = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress(
			(const GLubyte*)"glXSwapIntervalEXT");
	if (interval_ext)
		interval_ext(dpy, drawable, 0);
	else
	{
		printf("Warning: Could not load glXSwapIntervalEXT");
		printf("VSync might remain active.\n");
	}
}

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
	if (window->pixel_buffer)
	{
		free(window->pixel_buffer);
		window->pixel_buffer = NULL;
	}
	free(window);
	return (NULL);
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
	window->pixel_buffer = calloc(w * h, sizeof(int));
	if (!window->pixel_buffer)
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
	disable_vsync(mlx->dpy, window->xwin);
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
	if (!create_x11_window(mlx, window, width, height))
		return (cleanup_window(mlx, window));
	if (!setup_graphic_context(mlx, window))
		return (cleanup_window(mlx, window));
	XStoreName(mlx->dpy, window->xwin, title);
	XSetWMProtocols(mlx->dpy, window->xwin, &(mlx->wm_delete), 1);
	XClearWindow(mlx->dpy, window->xwin);
	XMapRaised(mlx->dpy, window->xwin);
	window->next = mlx->win_list;
	mlx->win_list = window;
	return (window);
}
