/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:46:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 06:57:59 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_destroy_window(t_mlx *mlx, t_window *win)
{
	(void)win;
	XDestroyWindow(mlx->dpy, win->xwin);
	glXDestroyContext(mlx->dpy, mlx->glc);
	return (0);
}
