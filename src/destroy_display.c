/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:16:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/20 15:09:17 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_destroy_display(t_mlx *mlx)
{
	if (mlx->font)
	{
		XFreeFont(mlx->dpy, mlx->font);
		mlx->font = NULL;
	}
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
