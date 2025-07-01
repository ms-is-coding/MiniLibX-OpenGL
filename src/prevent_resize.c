/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prevent_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:32:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/01 16:16:42 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <string.h>

void	__mlx_prevent_resize(t_mlx *mlx, t_window *win, int width, int height)
{
	XSizeHints	hints;
	long		dummy;

	memset(&hints, 0, sizeof(XSizeHints));
	XGetWMNormalHints(mlx->dpy, win->xwin, &hints, &dummy);
	hints.width = width;
	hints.height = height;
	hints.min_width = width;
	hints.min_height = height;
	hints.max_width = width;
	hints.max_height = height;
	hints.flags = PPosition | PSize | PMinSize | PMaxSize;
	XSetWMNormalHints(mlx->dpy, win->xwin, &hints);
}
