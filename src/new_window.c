/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:02:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 07:10:40 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

void	*mlx_new_window(t_mlx *mlx, int width, int height, const char *title)
{
	XGCValues	xgcv;
	t_window	*win;

	xgcv = (XGCValues){};
	win = calloc(1, sizeof(t_window));
	win->next = mlx->win_list;
	mlx->win_list = win;
	mlx->cmap = XCreateColormap(mlx->dpy, RootWindow(mlx->dpy, mlx->scr_id),
			mlx->vi->visual, AllocNone);
	mlx->swa.border_pixel = BlackPixel(mlx->dpy, mlx->scr_id);
	mlx->swa.background_pixel = WhitePixel(mlx->dpy, mlx->scr_id);
	mlx->swa.override_redirect = True;
	mlx->swa.colormap = mlx->cmap;
	mlx->swa.event_mask = 0xFFFFFF;
	win->xwin = XCreateWindow(mlx->dpy, RootWindow(mlx->dpy, mlx->scr_id), 0, 0,
			width, height, 0, mlx->vi->depth, InputOutput,
			mlx->vi->visual, CWBackPixel | CWColormap | CWBorderPixel
			| CWEventMask, &mlx->swa);
	__mlx_prevent_resize(mlx, win, width, height);
	mlx->glc = glXCreateContext(mlx->dpy, mlx->vi, NULL, GL_TRUE);
	xgcv.foreground = -1;
	xgcv.function = GXcopy;
	xgcv.plane_mask = AllPlanes;
	mlx->gc = XCreateGC(mlx->dpy, win->xwin,
			GCFunction | GCPlaneMask | GCForeground, &xgcv);
	XStoreName(mlx->dpy, win->xwin, title);
	XSetWMProtocols(mlx->dpy, win->xwin, &(mlx->wm_delete), 1);
	glXMakeCurrent(mlx->dpy, win->xwin, mlx->glc);
	XClearWindow(mlx->dpy, win->xwin);
	XMapRaised(mlx->dpy, win->xwin);
	return (win);
}
