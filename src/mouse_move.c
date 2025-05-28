/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:02:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/25 14:24:25 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <X11/Xlib.h>

int	mlx_mouse_move(t_mlx *mlx, void *win, int x, int y)
{
	(void)win;
	XWarpPointer(mlx->dpy, None, mlx->win, 0, 0, 0, 0, x, y);
	return (0);
}
