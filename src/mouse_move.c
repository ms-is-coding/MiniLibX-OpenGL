/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:02:13 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 07:10:31 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_mouse_move(t_mlx *mlx, t_window *win, int x, int y)
{
	(void)win;
	XWarpPointer(mlx->dpy, None, win->xwin, 0, 0, 0, 0, x, y);
	return (0);
}
