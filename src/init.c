/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:41:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/10 18:25:30 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
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
	mlx->running = 1;
	return (mlx);
}
