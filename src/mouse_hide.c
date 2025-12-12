/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:30:30 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 07:10:26 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_mouse_hide(t_mlx *mlx, t_window *win)
{
	const char	data[1] = {0};
	Cursor		cursor;
	Pixmap		blank;
	XColor		dummy;

	(void)win;
	blank = XCreateBitmapFromData(mlx->dpy, win->xwin, data, 1, 1);
	cursor = XCreatePixmapCursor(mlx->dpy, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(mlx->dpy, win->xwin, cursor);
	XFreePixmap(mlx->dpy, blank);
	XFreeCursor(mlx->dpy, cursor);
	return (0);
}
