/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:00:42 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/25 14:01:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"

int	mlx_mouse_show(t_mlx *mlx, void *win)
{
	(void)win;
	XUndefineCursor(mlx->dpy, mlx->win);
	return (0);
}
