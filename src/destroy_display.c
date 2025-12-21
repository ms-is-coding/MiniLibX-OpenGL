/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:16:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/21 12:17:19 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

__attribute__((always_inline))
static inline void	clear_x_resources(t_mlx *mlx)
{
	if (mlx->gc)
	{
		XFreeGC(mlx->dpy, mlx->gc);
		mlx->gc = NULL;
	}
	if (mlx->vi)
	{
		XFree(mlx->vi);
		mlx->vi = NULL;
	}
	if (mlx->font)
	{
		XFreeFont(mlx->dpy, mlx->font);
		mlx->font = NULL;
	}
}

int	mlx_destroy_display(t_mlx *mlx)
{
	clear_x_resources(mlx);
	if (mlx->glc)
	{
		glXDestroyContext(mlx->dpy, mlx->glc);
		mlx->glc = NULL;
	}
	if (mlx->dpy)
	{
		XCloseDisplay(mlx->dpy);
		mlx->dpy = NULL;
	}
	return (0);
}
