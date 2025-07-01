/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:41:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/01 17:24:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

t_mlx	*mlx_init(void)
{
	t_mlx	*mlx;

	mlx = calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	if (__mlx_init_display(mlx))
		return (NULL);
	if (__mlx_init_opengl(mlx))
		return (NULL);
	mlx->wm_delete = XInternAtom(mlx->dpy, "WM_DELETE_WINDOW", False);
	mlx->wm_protocols = XInternAtom(mlx->dpy, "WM_PROTOCOLS", False);
	return (mlx);
}
