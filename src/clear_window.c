/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:26 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/14 17:27:23 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <X11/Xlib.h>

int	mlx_clear_window(t_mlx *mlx, void *win)
{
	(void)win;
	XClearWindow(mlx->dpy, mlx->win);
	return (0);
}
