/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:00:42 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/01 16:19:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_mouse_show(t_mlx *mlx, t_window *win)
{
	(void)win;
	XUndefineCursor(mlx->dpy, win->xwin);
	return (0);
}
