/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:34:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/10 20:49:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

int	mlx_loop_hook(t_mlx *mlx, int (*fn)(void *), void *param)
{
	mlx->loop_hook = fn;
	mlx->loop_param = param;
	return (0);
}

int	mlx_loop(t_mlx *mlx)
{
	XEvent	ev;

	while (mlx->running)
	{
		while (mlx->running && XPending(mlx->dpy))
		{
			XNextEvent(mlx->dpy, &ev);
			if (ev.type == ClientMessage)
				mlx->running = 0;
		}
		XSync(mlx->dpy, False);
		if (mlx->loop_hook)
			mlx->loop_hook(mlx->loop_param);
		glXSwapBuffers(mlx->dpy, mlx->win);
	}
	return (0);
}
