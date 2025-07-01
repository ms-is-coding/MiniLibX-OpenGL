/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:46:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/01 16:17:40 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <GL/glx.h>

int	mlx_destroy_window(t_mlx *mlx, t_window *win)
{
	(void)win;
	XDestroyWindow(mlx->dpy, win->xwin);
	glXDestroyContext(mlx->dpy, mlx->glc);
	return (0);
}
