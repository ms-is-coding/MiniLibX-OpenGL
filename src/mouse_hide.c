/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:30:30 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/25 14:24:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <X11/X.h>
#include <X11/Xlib.h>

int	mlx_mouse_hide(t_mlx *mlx, void *win)
{
	const char	data[1] = {0};
	Cursor		cursor;
	Pixmap		blank;
	XColor		dummy;

	(void)win;
	blank = XCreateBitmapFromData(mlx->dpy, mlx->win, data, 1, 1);
	cursor = XCreatePixmapCursor(mlx->dpy, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(mlx->dpy, mlx->win, cursor);
	XFreePixmap(mlx->dpy, blank);
	XFreeCursor(mlx->dpy, cursor);
	return (0);
}
