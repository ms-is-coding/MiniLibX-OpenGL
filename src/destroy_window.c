/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:46:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/11 11:20:38 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <GL/glx.h>

int	mlx_destroy_window(t_mlx *mlx, void *win)
{
	(void)win;
	XDestroyWindow(mlx->dpy, mlx->win);
	glXDestroyContext(mlx->dpy, mlx->glc);
	return (0);
}
