/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opengl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:24:38 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/13 20:08:02 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "mlx_internal.h"

int	__mlx_init_opengl(t_mlx *mlx)
{
	static GLint	glx_attr[] = {
		GLX_RGBA, GLX_DOUBLEBUFFER,
		GLX_DEPTH_SIZE, 24,
		GLX_STENCIL_SIZE, 8,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_SAMPLE_BUFFERS, 0,
		GLX_SAMPLES, 0,
		None
	};

	if (__mlx_glx_check_version(mlx))
		return (1);
	mlx->vi = glXChooseVisual(mlx->dpy, mlx->scr_id, glx_attr);
	if (!mlx->vi)
	{
		printf("Could not create visual window.\n");
		XCloseDisplay(mlx->dpy);
		free(mlx);
		return (1);
	}
	return (0);
}
