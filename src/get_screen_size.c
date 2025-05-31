/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:49:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/31 19:52:05 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <X11/Xlib.h>

int	mlx_get_screen_size(t_mlx *mlx, int *width, int *height)
{
	XWindowAttributes	attr;

	XGetWindowAttributes(mlx->dpy, mlx->root, &attr);
	*width = attr.width;
	*height = attr.height;
	return (0);
}
