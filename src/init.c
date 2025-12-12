/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:41:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 06:59:19 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

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
