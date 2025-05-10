/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:16:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/10 20:17:05 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"

int	mlx_destroy_display(t_mlx *mlx)
{
	XCloseDisplay(mlx->dpy);
	return (0);
}
