/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:02:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/10 18:41:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

void	*mlx_new_window(t_mlx *mlx, int width, int height, const char *title)
{
	(void)title;
	mlx->cmap = XCreateColormap(mlx->dpy, RootWindow(mlx->dpy, mlx->scr_id),
			mlx->vi->visual, AllocNone);
	mlx->swa.border_pixel = BlackPixel(mlx->dpy, mlx->scr_id);
	mlx->swa.background_pixel = WhitePixel(mlx->dpy, mlx->scr_id);
	mlx->swa.override_redirect = True;
	mlx->swa.colormap = mlx->cmap;
	mlx->swa.event_mask = ExposureMask;
	mlx->win = XCreateWindow(mlx->dpy, RootWindow(mlx->dpy, mlx->scr_id), 0, 0,
			width, height, 0, mlx->vi->depth, InputOutput,
			mlx->vi->visual, CWBackPixel | CWColormap | CWBorderPixel
			| CWEventMask, &mlx->swa);
	mlx->glc = glXCreateContext(mlx->dpy, mlx->vi, NULL, GL_TRUE);
	XStoreName(mlx->dpy, mlx->win, title);
	glXMakeCurrent(mlx->dpy, mlx->win, mlx->glc);
	XClearWindow(mlx->dpy, mlx->win);
	XMapRaised(mlx->dpy, mlx->win);
	__mlx_prevent_resize(mlx, width, height);
	return ((void *)1);
}
